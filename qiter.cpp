#include "qiter.h"
#include "pcb.h"
#include "def.h"

QueueIterator::QueueIterator(Queue *queue) {
	this->queue = queue;
	this->curr = queue->first;
}

void QueueIterator::toStart() {
	curr = queue->first;
}

void QueueIterator::toEnd() {
	curr = queue->last;
}

PCB* QueueIterator::next() {
	LOCK_INTR
	PCB *pcb = curr->pcb;
	curr = curr->next;
	UNLOCK_INTR
	return pcb;
}

unsigned QueueIterator::isDone() {
	return curr == 0 ? 1 : 0;
}