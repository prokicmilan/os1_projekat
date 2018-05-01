/**
* Pomocna klasa za iteriranje kroz fifo red. Na korisniku je da
* pazi da ne pristupi null pokazivacu, klasa je opremljena metodom
* koja govori da li je moguc pristup i prelazak na sledeci
**/

#ifndef _QITER_H_
#define _QITER_H_

#include "queue.h"
#include "pcb.h"

struct Node;

class QueueIterator {
public:
	QueueIterator(Queue *queue);
	void toStart();
	void toEnd();
	PCB* next();
	unsigned isDone();

private:
	Queue *queue;
	Node *curr;
};

#endif