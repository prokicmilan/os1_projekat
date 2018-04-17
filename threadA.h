#ifndef _THREADA_H_
#define _THREADA_H_

#include "thread.h"

class ThreadA : public Thread {
public:
	ThreadA(int a, StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice) : Thread(stackSize, timeSlice) {
		this->a = a;
	}
	virtual ~ThreadA() {
		waitToComplete();
	}

	virtual void run();

private:
	int a;
};

#endif