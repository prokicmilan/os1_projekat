/**
* Idle nit koja ne radi nista, predaje joj se CPU iskljucivo eksplicitno
* kad ne postoji druga nit koja moze da se izvrsava (sve niti su blokirane)
* ali nisu zavrsile
**/

#ifndef _IDLETH_H_
#define _IDLETH_H_

#include "thread.h"

class IdleThread : public Thread {
public:
	IdleThread();
	virtual void run();
	void start();
};

#endif