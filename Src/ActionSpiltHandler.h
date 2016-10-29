/************************************************************************/
/* 
@arthor:	StefanChen
@date:		20161029
@version:	1.0
@brief:		IArthurActionSpiltHandler  ���������������
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
	@param:		const TTileLayerGridProperty *pTileLayerPeperty			Ϊ��Ч�ʸߣ�ʡȥ������ظ�
	@param:		CActorBase* pSelfActor									��ǰ��ɫ
	@param:		TActorInstanceMap* pOtherActors							������ɫ����ǰ���˱����⣬ֻ��һ����Ϊ�Ժ���չ���������ϣ�����
	@return:	no
	@brief:		override, sub drivers achive self todo something
	*/
	/************************************************************************/
	virtual void  CheckCurrentAction(const TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorInstanceMap* pOtherActors) = 0;
};

typedef map<char*, IArthurActionSpiltHandler*> TSPLITHANDLERMAP;

#endif