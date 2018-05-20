#ifndef _IVTENTRY_H_
#define _IVTENTRY_H_

#include <dos.h>

#define PREPAREENTRY(N, CALLOLD) void interrupt int_##N(...) {\
									entries[N]->signalAll();\
								 }\
								 IVTEntry entry##N(N, FP_SEG(int_##N), FP_OFF(int_##N), CALLOLD);

class IVTEntry;
class Event;

IVTEntry *entries[256];

class IVTEntry {
public:
	IVTEntry(IVTNo n, unsigned int newISRSeg, unsigned int newISROff, callOld);
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
}

#endif