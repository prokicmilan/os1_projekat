#ifndef _KERNELEV_H_
#define _KERNELEV_H_

#include "def.h"
#include "krnlsem.h"
#include "pcb.h"
#include "kernel.h"

class KernelEv : public KernelSem {
public:
	KernelEv(IVTNo ivtNo);
	IVTNo getIVTNo() const;

private:
	IVTNo ivtNo;
	PCB *myPCB;
};

#endif