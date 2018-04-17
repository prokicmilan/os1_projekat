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

ID Thread::getId() const {
	return myPCB->getId();
}

ID Thread::getRunningId() {
	LOCK_INTR
	if (Kernel::running != 0) {
		UNLOCK_INTR
		return Kernel::running->getId();
	}
	else {
		UNLOCK_INTR
		return -1;
	}
}

Thread* Thread::getThreadById(ID id) {
	return 0;
}

void Thread::sleep(Time timeToSleep) {
	return;
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
	//multiline potencijal za problem (BCC)
	if (myPCB == Kernel::running || this == Kernel::idle 
								 || this == Kernel::mainThread
							  	 || Kernel::running->getStatus() == FINISHED 
							     || Kernel::running->getStatus() == NEW) {
		UNLOCK_INTR
		return;
	}
	//menja status, dodaje je u niz niti koje su blokirane i predaje procesor
	Kernel::running->setStatus(BLOCKED);
	myPCB->waitingQueue->put(Kernel::running);
	dispatch();
	UNLOCK_INTR
}

void dispatch() {
	LOCK_INTR
	Kernel::dispatch();
	UNLOCK_INTR
}