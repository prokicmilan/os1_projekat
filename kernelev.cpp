#include "kernelev.h"

KernelEv::KernelEv(IVTNo ivtNo) : Semaphore(0) {
	this->ivtNo = ivtNo;
}

IVTNo KernelEv::getIVTNo() const {
	return ivtNo;
}