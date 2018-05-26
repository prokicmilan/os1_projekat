#ifndef _IVTENTRY_H_
#define _IVTENTRY_H_

#include <dos.h>
#include "def.h"
#include "list.h"

/*
* Makro PREPAREENTRY kreira prekidnu rutinu za odgovarajuci ulaz, kao i 
* objekat koji enkapsulira sve radnje vezane za prekid, sto podrazumeva
* pozivanje stare prekidne rutine ukoliko je to potrebno, kao i signalizaciju
* da se dogadjaj desio svim nitima koje isti i ocekuju
*/
#define PREPAREENTRY(N,CALLOLD) void interrupt intr_##N(...);\
								IVTEntry entry##N(N, FP_SEG(intr_##N), FP_OFF(intr_##N), CALLOLD);\
								void interrupt intr_##N(...) {\
									entries[N]->signalAll();\
								 }

class IVTEntry;
class Event;

extern IVTEntry *entries[256];

class IVTEntry {
public:
	IVTEntry(IVTNo n, unsigned int newISRSeg, unsigned int newISROff, unsigned int callOld);
	~IVTEntry();
	void signalAll();
	void addEvent(Event *event);
	void removeEvent(Event *event);
	static IVTEntry* getEntry(IVTNo ivtNo);
private:
	unsigned int callOld;
	IVTNo n;
	pInterrupt oldISR;
	List *head;
};

#endif