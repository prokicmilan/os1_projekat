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
	ID getId() const;

	static ID getRunningId();
	static Thread* getThreadById(ID id);
	static void sleep(Time timeToSleep);

protected:
	friend class PCB;
	friend class IdleThread; //zbog drugacijeg starta za IdleThread, moze li elegantnije?
	friend class Kernel;
	Thread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run() {}

private:
	PCB *myPCB;
};

void dispatch();

#endif