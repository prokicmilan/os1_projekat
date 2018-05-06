#ifndef _PRODUCER_H_
#define _PRODUCER_H_

#include "bounded.h"
#include "thread.h"

class Producer : public Thread {
public:
	Producer(Bounded *b, StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice) : Thread(stackSize, timeSlice) {
		buffer = b;
	}

	virtual ~Producer() {
		waitToComplete();
	}

	virtual void run();

private:
	Bounded *buffer;
};

#endif