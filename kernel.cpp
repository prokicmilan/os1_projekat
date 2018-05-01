#include "kernel.h"
#include "idleth.h"
#include "queue.h"
#include "qiter.h"
#include "schedule.h"
#include <dos.h>

#include <conio.h>

Kernel* Kernel::kernelInstance = 0;
PCB* Kernel::running = 0;
IdleThread* Kernel::idle = 0;
Thread* Kernel::mainThread = 0;
Queue* Kernel::idQueue = 0;
Queue* Kernel::sleepingQueue = 0;
int Kernel::explicitDispatch = 0;
pInterrupt Kernel::oldTmr = 0;

Kernel::Kernel() {
	initialize();
}

Kernel::~Kernel() {
	restore();
}

Kernel* Kernel::getInstance() {
	if (kernelInstance == 0) {
		kernelInstance = new Kernel();
	}
	return kernelInstance;
}

void Kernel::dispatch() {
	LOCK_INTR
	explicitDispatch = 1;
	timerISR();
	UNLOCK_INTR
}

void Kernel::initialize() {
	LOCK_INTR
	oldTmr = getvect(0x08);
	setvect(0x08, timerISR);
	setvect(0x60, oldTmr);
	idle = new IdleThread();
	idle->start();
	mainThread = new Thread(4096, 200);
	mainThread->myPCB->status = READY;
	mainThread->myPCB->createStack();
	idQueue = new Queue();
	running = mainThread->myPCB;
	UNLOCK_INTR
}

void Kernel::restore() {
	LOCK_INTR
	setvect(8, oldTmr);
	UNLOCK_INTR
}

void interrupt Kernel::timerISR(...) {
	if (!explicitDispatch) {
		asm int 60h
		tick();
		static QueueIterator qi(sleepingQueue);
		/* Prolazi kroz ceo niz uspavanih niti i osvezava im proteklo vreme.
		* Ukoliko je nekoj niti isteklo vreme spavanja, odblokira je i 
		* vraca je u Scheduler ali samo ako nije main ili idle nit
		*/	
		while (!qi.isDone()) {
			PCB *pcb = qi.next();
			if (++pcb->passedTime == pcb->sleepTime) {
				pcb->status = READY;
				if (pcb == Kernel::mainThread->myPCB) {
					cprintf("main\r\n");
				}
				if (pcb != Kernel::mainThread->myPCB) {
					Scheduler::put(pcb);
				}
			}
		}
		//delete qi;
	}
	if (running->timeSlice != 0) {
		running->passedTime++;
	}
	//TODO: zabrana preuzimanja bez zabrane prekida
	if (running->passedTime == running->timeSlice || explicitDispatch) {
		static unsigned tsp, tss, tbp;
		asm {
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}
		running->sp = tsp;
		running->ss = tss;
		running->bp = tbp;
		if (running != mainThread->myPCB && //ako nije glavna nit
		   running != idle->myPCB && //ni idle nit
		   running->status != BLOCKED && //ni blokirana nit
		   running->status != FINISHED) { //ni gotova nit
			Scheduler::put(running);
		}
		running = Scheduler::get();
		if (running == 0) {
			if (idQueue->isEmpty() && mainThread->myPCB->status != BLOCKED) {
				running = mainThread->myPCB;
			}
			else {
				running = idle->myPCB;
			}
		}
		running->passedTime = 0;
		tsp = running->sp;
		tss = running->ss;
		tbp = running->bp;
		asm {
			mov sp, tsp
			mov ss, tss
			mov bp, tbp
		}
	}
	explicitDispatch = 0;
}