#include "pcb.h"
#include "kernel.h"
#include "queue.h"
#include "schedule.h"
#include <dos.h>

ID PCB::prevID = 0;

void PCB::wrapper() {
	Kernel::running->myThread->run();
	LOCK_INTR
	Kernel::running->setStatus(FINISHED);
	Kernel::idQueue->removeById(Kernel::running->getId());
	PCB *pcb = Kernel::running->waitingQueue->get();
	while (pcb != 0) {
		pcb->setStatus(READY);
		Scheduler::put(pcb);
	}
	dispatch();
	UNLOCK_INTR
}

PCB::PCB(Thread *myT, StackSize stackSize, Time timeSlice) {
	LOCK_INTR
	id = ++prevID;
	status = NEW;
	myThread = myT;
	this->stackSize = stackSize;
	this->timeSlice = timeSlice;
	stack = 0;
	waitingQueue = new Queue();
	UNLOCK_INTR
}

PCB::~PCB() {
	LOCK_INTR
	delete stack;
	delete waitingQueue;
	UNLOCK_INTR
}

ID PCB::getId() const {
	return id;
}

Status PCB::getStatus() const {
	return status;
}

void PCB::setStatus(Status st) {
	status = st;
}

void PCB::createStack() {
	LOCK_INTR
	this->stack = new unsigned[stackSize];
	this->stack[stackSize - 1] = 0x200;
	this->stack[stackSize - 2] = FP_SEG(PCB::wrapper);
	this->stack[stackSize - 3] = FP_OFF(PCB::wrapper);
	this->sp = FP_OFF(stack + stackSize - 12);
	this->ss = FP_SEG(stack + stackSize - 12);
	this->bp = FP_OFF(stack + stackSize - 12);
	UNLOCK_INTR
}