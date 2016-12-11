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
	/************************************************************************/
	/* 
	@func:		GetActionName
	@param:		no
	@return:	char*
	@brief:		each Handler have only Name
	*/
	/************************************************************************/
	virtual char* GetActionName() = 0;

	/************************************************************************/
	/* 
	@func:		CheckCurrentAction
	@param:		const TTileLayerGridProperty *pTileLayerPeperty			为了效率高，省去过多的重复
	@param:		CActorBase* pSelfActor									当前角色
	@param:		TActorTileLayerInfoMap* pOtherActors							其他角色，当前除了本尊外，只有一个，为以后扩展俩个人以上，方便
	@return:	no
	@brief:		override, sub drivers achive self todo something
	*/
	/************************************************************************/
	virtual void  CheckCurrentAction( TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors) = 0;
};

struct IEntityRulePropHandler
{
	/************************************************************************/
	/* 
	// 规则属性值变化 事件
	*/
	/************************************************************************/
	virtual		void	OnEntityRulePropChange(int PDBID, int iRulePropID, int nRulePropValue) = 0;
};

#endif