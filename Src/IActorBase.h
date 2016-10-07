
#ifndef _IACTOR_BASE_
#define _IACTOR_BASE_

struct IActorBase
{
	virtual void GetPlayerGoPath(int iStepCount, int** arrCanGoGrid) = 0;
};

#endif