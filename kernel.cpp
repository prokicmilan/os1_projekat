#include "kernel.h"
#include "idleth.h"
#include "queue.h"
#include "schedule.h"
#include <dos.h>

Kernel* Kernel::kernelInstance = 0;
PCB* Kernel::running = 0;
Thread* Kernel::idle = 0;
Thread* Kernel::mainThread = 0;
Queue* Kernel::idQueue = 0;
volatile Time Kernel::cntr = 20;
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
	mainThread = new Thread();
	mainThread->myPCB->setStatus(READY);
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
		cntr--;
	}
	if (!explicitDispatch) {
		asm int 60h
		tick();
	}
	//TODO: zabrana preuzimanja bez zabrane prekida
	//TODO: preci na implementaciju u kojoj nit zna koliko se dugo izvrsavala
	if (cntr == 0 || explicitDispatch) {
		static unsigned tsp, tss, tbp;
		asm {
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}
		running->sp = tsp;
		running->ss = tss;
		running->bp = tbp;
		if (mainThread->getId() != running->getId() && //ako nije glavna nit
		   idle->getId() != running->getId() && //ni idle nit
		   running->getStatus() != FINISHED) { //ni gotova nit
			Scheduler::put(running);
		}
		running = Scheduler::get();
		if (running == 0) {
			if (idQueue->isEmpty()) {
				running = mainThread->myPCB;
			}
			else {
				running = idle->myPCB;
			}
		}
		cntr = running->timeSlice;
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