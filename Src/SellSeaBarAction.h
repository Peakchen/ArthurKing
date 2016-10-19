/************************************************************************/
/* 
author:		StefanChen
mail:		chenfeng1790291543@163.com
date:		20161019
version:	1.0
*/
/************************************************************************/

#ifndef _SELL_SEABAR_ACTION_
#define _SELL_SEABAR_ACTION_


#pragma once
#include "ActorBase.h"
class CSellSeaBarAction
{
public:
	CSellSeaBarAction();
	~CSellSeaBarAction();

	/************************************************************************/
	/* 
	@func:		CheckCanSellSeaBar
	@param:		int iSeaBar_Index
	@param:		CActorBase* pOwner
	@return:	void
	@Desc:		check seabar owner if he/she can sell this seabar.
	*/
	/************************************************************************/

	bool CheckCanSellSeaBar(int iSeaBar_Index, CActorBase* pOwner);

	/************************************************************************/
	/*
	@func:		DoSellSeaBarAction
	@param:		int iSeaBar_Index
	@param:		CActorBase* pOwner
	@return:	void
	@Desc:		todo sell this seabar.
	*/
	/************************************************************************/

	bool DoSellSeaBarAction(int iSeaBar_Index, CActorBase* pOwner);
};


#endif