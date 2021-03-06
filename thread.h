#ifndef _THREAD_H_
#define _THREAD_H_

#include "def.h"

class PCB;
class IdleThread;
class Kernel;

class Thread {
public:
	void start();
	void waitToComplete();
	virtual ~Thread();

	static void sleep(Time timeToSleep);

protected:
	friend class PCB;
	friend class IdleThread;
	friend class Kernel;
	Thread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run() {}

private:
	PCB *myPCB;
};

void dispatch();

#endif