#include "queue.h"
#include "def.h"

Queue::Queue() {
	LOCK_INTR
	first = 0;
	last = 0;
	UNLOCK_INTR
}

Queue::~Queue() {
	LOCK_INTR
	while (first != 0) {
		Node *old = first;
		first = first->next;
		delete old;
	}
	last = 0;
	UNLOCK_INTR
}

unsigned Queue::isEmpty() const {
	return (first == 0 && last == 0);
}

void Queue::put(PCB *pcb) {
	LOCK_INTR
	Node *newNode = new Node();
	newNode->pcb = pcb;
	newNode->next = 0;
	if (first == 0) {
		first = last = newNode;
	}
	else {
		last->next = newNode;
		last = last->next;
	}
	UNLOCK_INTR
}

PCB* Queue::get() {
	LOCK_INTR
	if (first == 0) {
		UNLOCK_INTR
		return 0;
	}
	else {
		Node *old = first;
		first = first->next;
		last = first == 0 ? 0 : last;
		PCB *pcb = old->pcb;
		delete old;
		UNLOCK_INTR
		return pcb;
	}
}

PCB* Queue::findById(ID id) {
	LOCK_INTR
	Node *curr = first;
	while (curr != 0 && curr->pcb->getId() != id) {
		curr = curr->next;
	}
	UNLOCK_INTR
	return curr->pcb;
}

void Queue::removeById(ID id) {
	LOCK_INTR
	Node *curr = first;
	Node *prev = 0;
	while (curr != 0 && curr->pcb->getId() != id) {
		prev = curr;
		curr = curr->next;
	}
	if (curr == 0) { //nije pronadjen, greska
		UNLOCK_INTR
		return;
	}
	else {
		Node *old = curr;
		if (prev == 0) {
			first = curr->next;
		}
		else {
			if (last == curr) {
				last = prev;
			}
			prev->next = curr->next;
		}
		delete old;
	}
	if (first == 0) {
		last = 0;
	}
	UNLOCK_INTR
}