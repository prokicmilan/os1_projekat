#include "threadA.h"
#include "def.h"
#include <iostream.h>

void ThreadA::run() {
	for (int i = 0; i < 30; i++) {
		LOCK_INTR
		cout << "a = " << a << " i = " << i << endl;
		UNLOCK_INTR
		for (int j = 0; j < 10000; j++) {
			for (int k = 0; k < 10000; k++);
		}
	}
}