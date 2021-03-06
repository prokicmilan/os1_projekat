#include "kernel.h"
#include <iostream.h>

extern int userMain(int argc, char *argv[]);

int main(int argc, char *argv[]) {
	Kernel *kernel = Kernel::getInstance();
	int returnVal = userMain(argc, argv);
	delete kernel;
	return returnVal;
}