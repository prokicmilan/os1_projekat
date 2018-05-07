#include "bounded.h"
#include <conio.h>

Bounded::Bounded(int size) : mutex(1), spaceAvailable(size), itemAvailable(0) {
	this->size = size;
	head = 0;
	tail = 0;
	storage = new int[size];
}

Bounded::~Bounded() {
	delete storage;
}

int Bounded::getSize() const {
	return size;
}

int Bounded::getNum() const {
	return tail - head;
}

void Bounded::put(int num) {
	spaceAvailable.wait(1);
	mutex.wait(1);
	storage[tail] = num;
	tail = (tail + 1) % size;
	mutex.signal();
	itemAvailable.signal();
}

int Bounded::get() {
	itemAvailable.wait(1);
	mutex.wait(1);
	int num = storage[head];
	head = (head + 1) % size;
	mutex.signal();
	spaceAvailable.signal();
	return num;
}