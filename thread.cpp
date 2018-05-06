#include "thread.h"
#include "schedule.h"
#include "pcb.h"
#include "kernel.h"
#include "queue.h"
#include "def.h"

Thread::Thread(StackSize stackSize, Time timeSlice) {
	LOCK_INTR;
	myPCB = new PCB(this, stackSize, timeSlice);
	UNLOCK_INTR;
}

Thread::~Thread() {
	waitToComplete();
	delete myPCB;
}

//uspavljuje tekucu nit na odredjeno vreme, predaje procesor nekoj drugoj niti
void Thread::sleep(Time timeToSleep) {
	LOCK_INTR
	if (Kernel::running == 0) {
		UNLOCK_INTR
		return;
	}
	Kernel::running->sleepTime = timeToSleep;
	Kernel::running->status = BLOCKED;
	Kernel::sleepingQueue->put(Kernel::running);
	dispatch();
	UNLOCK_INTR
}

void Thread::start() {
	LOCK_INTR
	if (myPCB->getStatus() == NEW) {
		myPCB->createStack();
		myPCB->setStatus(READY);
		Kernel::idQueue->put(myPCB);
		Scheduler::put(myPCB);
	}
	UNLOCK_INTR
}

void Thread::waitToComplete() {
	LOCK_INTR
	//ne ceka samu sebe, idle, main, zavrsenu i novu nit
	if (myPCB == Kernel::running || this == Kernel::idle 
								 || this == Kernel::mainThread
							  	 || myPCB->status == FINISHED 
							     || myPCB->status == NEW) {
		UNLOCK_INTR
		return;
	}
	//menja status, dodaje je u niz niti koje su blokirane i predaje procesor
	Kernel::running->status = BLOCKED;
	myPCB->waitingQueue->put(Kernel::running);
	dispatch();
	UNLOCK_INTR
}

void dispatch() {
	LOCK_INTR
	Kernel::dispatch();
	UNLOCK_INTR
}