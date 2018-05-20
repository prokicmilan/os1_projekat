#ifndef _EVENT_H_
#define _EVENT_H_

#include "def.h"
#include "ivtentry.h"

class KernelEv;
class IVTEntry;

class Event {
public:
	Event(IVTNo ivtNo);
	~Event();

	void wait();

protected:
	friend class KernelEv;
	friend class IVTEntry;
	void signal();

private:
	KernelEv *myImpl;
};

#endif