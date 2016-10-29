/************************************************************************/
/* 
@arthor:	StefanChen
@date:		20161029
@version:	1.0
@brief:		IArthurActionSpiltHandler  动作分流处理机制
*/
/************************************************************************/
#ifndef __ACTION_SPLITHANDLER__
#define __ACTION_SPLITHANDLER__

#include "stdafx.h"
#include "ActorBase.h"


struct IArthurActionSpiltHandler
{
	virtual char* GetActionName() = 0;

	virtual void  CheckCurrentAction(const char*  szName, const char* szType, CActorBase* pActor) = 0;
};

typedef map<char*, IArthurActionSpiltHandler*> TSPLITHANDLERMAP;

#endif