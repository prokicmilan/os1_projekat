/**
* Kernel, vrsi inicijalizaciju prekidnih rutina prilikom instanciranja,
* vraca stare prekidne rutine pri izvrsavanju destruktora
* implementiran kao singleton - postoji samo jedan kernel u sistemu
**/

#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "idleth.h"
#include "def.h"

class Thread;
class PCB;
class Queue;

extern void tick();

class Kernel {
public:
	static Kernel* getInstance();
	static void dispatch();
	~Kernel();

protected:
	friend class Thread;
	friend class PCB;

private:
	static Kernel *kernelInstance;
	static PCB *running;
	static IdleThread *idle;
	static Thread *mainThread;
	static Queue *idQueue;
	static Queue *sleepingQueue;

	Kernel();
	static void initialize();
	static void restore();
	static void interrupt timerISR(...);
	static pInterrupt oldTmr;
	static int explicitDispatch;
};

#endif