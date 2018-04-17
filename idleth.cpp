#include "idleth.h"
#include "pcb.h"
#include "def.h"

IdleThread::IdleThread() : Thread() {}

void IdleThread::run() {
	while(1);
}

void IdleThread::start() {
	LOCK_INTR
	myPCB->setStatus(READY);
	myPCB->createStack();
	UNLOCK_INTR
}