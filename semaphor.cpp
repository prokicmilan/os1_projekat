#include "semaphor.h"
#include "def.h"

Semaphore::Semaphore(int init) {
	LOCK_INTR
	myImpl = new KernelSem(init);
	UNLOCK_INTR
}

Semaphore::~Semaphore() {
	delete myImpl;
}

int Semaphore::wait(int toBlock) {
	return 0;
}

void Sempahore::signal() {
	return;
}

int Semaphore::val() const {
	return myImpl->getVal();
}