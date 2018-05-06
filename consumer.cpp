#include "consumer.h"
#include <iostream.h>

void Consumer::run() {
	int num;
	for (int i = 0; i < 10; i++) {
		num = buffer->get();
		cout << "Izvadio " << num << endl;
		//sleep(10);
	}
}