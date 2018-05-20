#include "kernelev.h"

KernelEv::KernelEv(IVTNo ivtNo) : KernelSem(0) {
	this->ivtNo = ivtNo;
	this->myPCB = Kernel::running;
}

IVTNo KernelEv::getIVTNo() const {
	return ivtNo;
}