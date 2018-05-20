#include "list.h"

List::List() {
	first = 0;
	last = 0;
}

List::~List() {
	while (first != 0) {
		ListNode *old = first;
		first = first->next;
		delete old;
	}
	first = 0;
	last = 0;
}

void List::add(Event *event) {
	ListNode *newNode = new ListNode();

	newNode->event = event;
	newNode->next = 0;
	if (first == 0) {
		first = newNode;
	}
	else {
		last->next = newNode;
	}
	last = newNode;
}

void List::remove(Event *event) {
	ListNode *curr = first;
	ListNode *prev = 0;

	while (curr != 0 && curr->event != event) {
		prev = curr;
		curr = curr->next;
	}
	if (prev) {
		prev->next = curr->next;
	}
	else {
		first = curr->next;
	}
	if (!first) {
		last = 0;
	}
}