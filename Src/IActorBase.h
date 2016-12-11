

#ifndef _IACTOR_BASE_
#define _IACTOR_BASE_

#include "common.h"

struct IActorBase
{
	virtual void GetPlayerGoPath(int iStepCount, int** arrCanGoGrid) = 0;
};

// 角色属性map
typedef map<int, int> TActorPropMap;
// 规则属性map
typedef map<int, int> TActorRulePropMap;

#endif