#include "threadA.h"
#include <iostream.h>

void tick() {}

int userMain(int argc, char *argv[]) {
	ThreadA *a = new ThreadA(50, 1024, 10);
	ThreadA *b = new ThreadA(20, 1024, 20);

	a->start();
	b->start();
	/*for (int i = 0; i < 0; i++) {
		cout << "main: i = " << i << endl;
		for (int j = 0; j < 30000; j++)
			for (int k = 0; k < 30000; k++);
	}*/
	cout << "delete a" << endl;
	delete a;
	cout << "delete b" << endl;
	delete b;
	cout << "Happy end!" << endl;

	return 0;
}