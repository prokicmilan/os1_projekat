#include "threadA.h"
#include "bounded.h"
#include "consumer.h"
#include "producer.h"
#include <iostream.h>

void tick() {}

int userMain(int argc, char *argv[]) {
	/*ThreadA *a = new ThreadA(50, 1024, 10);
	ThreadA *b = new ThreadA(20, 1024, 20);
	ThreadA *c = new ThreadA(30, 1024, 40);

	a->start();
	b->start();
	c->start();
	cout << "delete a" << endl;
	delete a;
	cout << "delete b" << endl;
	delete b;
	cout << "delete c" << endl;
	delete c;
	cout << "Sleep" << endl;
	Thread::sleep(100);*/
	Bounded *b = new Bounded(3);
	//Consumer *c = new Consumer(b);
	Producer *p = new Producer(b);
	p->start();
	//c->start();
	//delete c;
	delete p;
	delete b;
	cout << "Happy end!" << endl;

	return 0;
}