#include "threadA.h"
#include <iostream.h>

void tick() {}

int userMain(int argc, char *argv[]) {
	ThreadA *a = new ThreadA(50, 1024, 40);
	ThreadA *b = new ThreadA(20, 1024, 20);

	a->start();
	b->start();
	delete a;
	delete b;
	cout << "Happy end!" << endl;

	return 0;
}