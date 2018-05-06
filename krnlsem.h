#ifndef _KRNLSEM_H_
#define _KRNLSEM_H_

#include "queue.h"

class KernelSem {
public:
	KernelSem(int init);
	~KernelSem();

	int getVal() const;

	int wait(int toBlock);
	void signal();

private:
	int val;
	Queue *blocked;
};

#endif