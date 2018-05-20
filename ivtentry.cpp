#include "ivtentry.h"
#include "list.h"

IVTEntry::IVTEntry(IVTNo n, unsigned int newISRSeg, unsigned int newISROff, callOld) {
	LOCK_INTR
	this->n = n;
	this->callOld = callOld;
	oldISR = getvect(n);
	unsigned int ISRSeg = newISRSeg;
	unsigned int ISROff = newISROff;
	asm {
		push es
		push ax
		push bx
		mov ax, 0
		mov es, ax
		mov bx, word ptr n
		shl bx, 2
		mov ax, word ptr ISROff
		mov word ptr es:bx, ax
		add bx, 2
		mov ax, word ptr ISRSeg
		mov word ptr es:bx, ax
		pop bx
		pop ax
		pop es
	}
	entries[n] = this;
	head = new List();
	UNLOCK_INTR
}

IVTEntry::~IVTEntry() {
	delete list;
	setvect(n, oldISR);
}

void IVTEntry::signalAll() {
	LOCK_INTR
	if (callOld) {
		oldISR();
	}
	ListNode *curr = head->first;
	while (curr != 0) {
		curr->event->signal();
		curr = curr->next;
	}
	Kernel::dispatch();
	UNLOCK_INTR
}

void IVTEntry::addEvent(Event *event) {
	LOCK_INTR
	head->add(event);
	UNLOCK_INTR
}

void IVTEntry::removeEvent(Event *event) {
	LOCK_INTR
	head->remove(event);
	UNLOCK_INTR
}

IVTEntry* IVTEntry::getEntry(IVTNo ivtNo) {
	return entries[ivtNo];
}