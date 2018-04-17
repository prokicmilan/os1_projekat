/**
* Standardni FIFO red, jedina razlika je u zabranjivanju prekida pri 
* izvrsavanju odredjenih kriticnih operacija
**/

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "pcb.h"
#include "def.h"

struct Node {
	PCB *pcb;
	Node *next;
};

class Queue {
public:
	Queue();
	~Queue();
	void put(PCB *pcb);
	unsigned isEmpty() const;
	PCB* get();
	PCB* findById(ID id);
	void removeById(ID id);
private:
	Node *first;
	Node *last;
	Queue(const Queue&) {}
	Queue& operator=(const Queue&) { return *this; }
};

#endif