#include "producer.h"
#include <iostream.h>

void Producer::run() {
	for (int i = 0; i < 10; i++) {
		buffer->put(i);
		cout << "Stavio " << i << endl;
		sleep(30);
	}
}