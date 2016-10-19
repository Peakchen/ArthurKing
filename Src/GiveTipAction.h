/************************************************************************/
/*
author:		StefanChen
mail:		chenfeng1790291543@163.com
date:		20161018
version:	1.0
*/
/************************************************************************/

#ifndef _GIVETIP_ACTION_
#define _GIVETIP_ACTION_

#pragma once
#include "common.h"
#include "ActorBase.h"


class CGiveTipAction
{
public:
	CGiveTipAction();
	~CGiveTipAction();

	/************************************************************************/
	/* 
	@func:		CheckCanGiveTipToOthers()
	@param:		int iSeaBar_Index
	@param:		CActorBase*
	@return:	bool
	@Desc:		some need to pay score for where you sit now. 
	*/
	/************************************************************************/
	
	bool CheckCanGiveTipToOthers(int iSeaBar_Index, CActorBase* pActor);

	/************************************************************************/
	/* 
	@func:		DoGiveTipToOther()
	@param:		int iSeaBar_Index
	@param:		CActorBase*
	@return:	void
	@Desc:		if you sit other seabar, now  you need to pay score for where you sit now.
	*/
	/************************************************************************/

	void DoGiveTipToOther(int iSeaBar_Index, CActorBase* pActor);
};

#endif