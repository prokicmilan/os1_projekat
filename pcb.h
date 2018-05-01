#ifndef _PCB_H_
#define _PCB_H_

#include "def.h"
#include "thread.h"

class Queue;
class Kernel;

class PCB {
public:
	PCB(Thread *myT, StackSize stackSize, Time timeSlice);
	~PCB();
	ID getId() const;
	Status getStatus() const;
	void setStatus(Status st);
	void createStack();

protected:
	friend class Thread;
	friend class Kernel;

private:
	ID id;
	StackSize stackSize;
	Time timeSlice;
	volatile Time passedTime;
	Time sleepTime;

	unsigned sp;
	unsigned ss;
	unsigned bp;
	unsigned *stack;

	Thread *myThread;
	Queue *waitingQueue;
	Status status;

	static ID prevID;	

	static void wrapper();
	inline void run();
};

#endif