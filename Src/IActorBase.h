

#ifndef _IACTOR_BASE_
#define _IACTOR_BASE_

#include "common.h"

struct IActorBase
{
	virtual void GetPlayerGoPath(int iStepCount, int** arrCanGoGrid) = 0;
};

typedef map<int, int> TActorPropMap;

#endif