#ifndef _IVTENTRY_H_
#define _IVTENTRY_H_

#include <dos.h>
#include "def.h"
#include "list.h"

#define PREPAREENTRY(N,CALLOLD) void interrupt intr_##N(...);\
								IVTEntry entry##N(N, FP_SEG(int_##N), FP_OFF(int_##N), CALLOLD);\
								void interrupt intr_##N(...) {\
									entries[N]->signalAll();\
								 }\

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