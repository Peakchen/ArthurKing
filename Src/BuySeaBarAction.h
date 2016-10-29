#include "common.h"
#include "ActorBase.h"
/************************************************************************/
/* 
author:		StefanChen
mail:		chenfeng1790291543@163.com
date:		20161017
version:	1.0
*/
/************************************************************************/

#ifndef _BUY_SEABAR_ACTION_
#define _BUY_SEABAR_ACTION_


class CBuySeaBarAction
{
	public:
		/************************************************************************/
		/*
		@func:		CheckCanExchangeSeaBar
		@param:		int iSeaBarIndex
		@param:		ESeaBarAttach attchFlag
		@param:		CActorBase* pActor
		@return:	bool
		@Desc:		check you can exchange this sea, where you go finally.
		
		************************************************************************/
		bool CheckCanExchangeSeaBar(int iSeaBarIndex,  ESeaBarAttach& attchFlag, CActorBase* pActor);

		/************************************************************************/
		/* 
		@func:		DoExchangeSeaBar
		@param:		int iSeaBarIndex
		@param:		CActorBase* pActor
		@return:	bool
		@Desc:		a position where there is a seabar, you can exchange it with socre if you have enough score.
		*/
		/************************************************************************/
		void DoExchangeSeaBar(int iSeaBarIndex, CActorBase* pActor);

	protected:
		
	private:

};

#endif