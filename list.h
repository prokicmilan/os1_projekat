#ifndef _LIST_H_
#define _LIST_H_

#include "def.h"

class IVTEntry;
class Event;

struct ListNode {
	Event *event;
	ListNode *next;
};

class List {
public:
	List();
	~List();
	void add(Event *event);
	void remove(Event *event);
	
protected:
	friend class IVTEntry;

private:
	ListNode *first;
	ListNode *last;
	List(const List&) {}
	List& operator=(const List&) { return *this; }
};

#endif