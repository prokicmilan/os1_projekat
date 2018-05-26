#include "ivtentry.h"
#include "kernel.h"
#include "event.h"

IVTEntry *entries[256];

/*
* Pri pozivu konstruktora pamti se stara prekidna rutina, a na njeno mesto se upisuje
* nova, data parametrima newISRSeg i newISROff. Na odgovarajuce mesto u nizu
* svih objekata vezanih za ulaze se upisuje trenutno kreirani
*/
IVTEntry::IVTEntry(IVTNo n, unsigned int newISRSeg, unsigned int newISROff, unsigned int callOld) {
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
		shl bx, 1
		shl bx, 1
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

/*
* Pri unistenju objekta potrebno je upisati staru prekidnu rutinu u odgovarajuci ulaz,
* kao i obrisati sve dogadjaje vezane za tekuci objekat, ukoliko vec nisu (destruktor ne
* bi trebalo da se pozove pre nego sto se svi dogadjaji odjave - uniste)
*/
IVTEntry::~IVTEntry() {
	LOCK_INTR
	delete head;
	setvect(n, oldISR);
	UNLOCK_INTR
}

/*
* Dogadjaj se desio, poziva se stara prekidna rutina ako je tako specificirano,
* i svim prijavljenim dogadjajima se salje signal
*/
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

/*
* Prijavljivanje dogadjaja na ulaz (da bi vise dogadjaja moglo da ceka prekid sa istog ulaza)
*/
void IVTEntry::addEvent(Event *event) {
	LOCK_INTR
	head->add(event);
	UNLOCK_INTR
}

/*
* Odjavljivanje dogadjaja sa ulaza
*/
void IVTEntry::removeEvent(Event *event) {
	LOCK_INTR
	head->remove(event);
	UNLOCK_INTR
}

/*
* Dohvatanje objekta pridruzenom odgovarajucem ulazu (moze vratiti NULL)
*/
IVTEntry* IVTEntry::getEntry(IVTNo ivtNo) {
	return entries[ivtNo];
}