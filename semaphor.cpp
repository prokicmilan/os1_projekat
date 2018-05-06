#include "semaphor.h"
#include "krnlsem.h"
#include "def.h"

Semaphore::Semaphore(int init) {
	LOCK_INTR
	myImpl = new KernelSem(init);
	UNLOCK_INTR
}

Semaphore::~Semaphore() {
	LOCK_INTR
	delete myImpl;
	UNLOCK_INTR
}

int Semaphore::wait(int toBlock) {
	LOCK_INTR
	int ret = myImpl->wait(toBlock);
	UNLOCK_INTR
	return ret;
}

void Semaphore::signal() {
	LOCK_INTR
	myImpl->signal();
	UNLOCK_INTR
}

int Semaphore::val() const {
	return myImpl->getVal();
}