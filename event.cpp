#include "event.h"
#include "ivtentry.h"
#include "kernelev.h"

Event::Event(IVTNo ivtNo) {
	LOCK_INTR
	IVTEntry *entry = IVTEntry::getEntry(ivtNo);
	if (entry == 0) return; //exception
	entry->addEvent(this);
	myImpl = new KernelEv(ivtNo);
	UNLOCK_INTR
}

Event::~Event() {
	LOCK_INTR
	IVTEntry *entry = IVTEntry::getEntry(myImpl->getIVTNo());
	if (entry == 0) return; //exception
	entry->removeEvent(this);
	delete myImpl;
	UNLOCK_INTR
}

void Event::wait() {
	myImpl->wait(1);
}

void Event::signal() {
	myImpl->signal();
}