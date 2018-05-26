#include "idleth.h"
#include "pcb.h"
#include "def.h"

IdleThread::IdleThread() : Thread() {}

void IdleThread::run() {
	while(1);
}

/*
* start metoda idle niti se razlikuje od start metode obicne
* niti jer se pri startu niti odmah kreira njen stek i postavlja status
* READY, ali se nikada ne ubacuje u rasporedjivac niti
*/
void IdleThread::start() {
	LOCK_INTR
	myPCB->setStatus(READY);
	myPCB->createStack();
	UNLOCK_INTR
}