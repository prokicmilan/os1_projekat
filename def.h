#ifndef _DEF_H_
#define _DEF_H_

/*
* Sve potrebne definicije tipova i makroa
*/

typedef enum {NEW, READY, BLOCKED, FINISHED} Status;
typedef unsigned long StackSize;
typedef unsigned int Time;
typedef int ID;
typedef	void interrupt (*pInterrupt)(...);
typedef unsigned int IVTNo;

const StackSize defaultStackSize = 4096;
const Time defaultTimeSlice = 2;

#define LOCK_INTR asm{\
	pushf;\
	cli;\
};

#define UNLOCK_INTR asm popf;

#endif