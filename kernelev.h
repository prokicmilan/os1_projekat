#ifndef _KERNELEV_H_
#define _KERNELEV_H_

#include "def.h"
#include "semaphor.h"

class KernelEv : public Semaphore {
public:
	KernelEv(IVTNo ivtNo);
	IVTNo getIVTNo() const;

private:
	IVTNo ivtNo;
};

#endif