#ifndef _CONSUMER_H_
#define _CONSUMER_H_

#include "bounded.h"
#include "thread.h"

class Consumer : public Thread {
public:
	Consumer(Bounded *b, StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice) : Thread(stackSize, timeSlice) {
		buffer = b;
	}

	virtual ~Consumer() {
		waitToComplete();
	}

	virtual void run();

private:
	Bounded *buffer;
};

#endif