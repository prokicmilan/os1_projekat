#include "krnlsem.h"
#include "kernel.h"
#include "schedule.h"

#include <conio.h>

KernelSem::KernelSem(int init) {
	cprintf("init = %d\r\n", init);
	val = init;
	blocked = new Queue();
}

KernelSem::~KernelSem() {
	delete blocked;
}

int KernelSem::getVal() const {
	return val;
}

int KernelSem::wait(int toBlock) {
	if (toBlock == 0) {
		if (val <= 0) {
			return -1;
		}
		else {
			val--;
			return 0;
		}
	}
	else {
		cprintf("val = %d\r\n", val);
		if (--val < 0) {
			cprintf("blocking\r\n");
			Kernel::running->status = BLOCKED;
			blocked->put(Kernel::running);
			Kernel::dispatch();
			return 1;
		}
		else {
			return 0;
		}
	}
}

void KernelSem::signal() {
	if (val++ < 0) {
		PCB *pcb = blocked->get();
		pcb->status = READY;
		Scheduler::put(pcb);
	}
}