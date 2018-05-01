#include "threadA.h"
#include "def.h"

#include <conio.h>

void ThreadA::run() {
	for (int i = 0; i < 10; i++) {
		cprintf("a = %d i = %d\r\n",a, i);
		for (int j = 0; j < 30000; j++) {
			for (int k = 0; k < 30000; k++);
		}
	}
}