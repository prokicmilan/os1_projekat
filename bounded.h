#ifndef _BOUNDED_H_
#define _BOUNDED_H_

#include "semaphore.h"

class Bounded {
public:
	Bounded(int size);
	~Bounded();
	int getSize() const;
	int getNum() const;
	void put(int num);
	int get();

private:
	int size;
	int head;
	int tail;
	int *storage;
	Semaphore mutex;
	Semaphore spaceAvailable;
	Semaphore itemAvailable;
};

#endif