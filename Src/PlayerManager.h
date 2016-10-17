#ifndef _PLAYER_MANAGER_
#define _PLAYER_MANAGER_

#include "ActorBase.h"
#include "ArthurKing.h"
#include "AIPlayer.h"

#pragma once
#include "MacroDefine.h"
#include "common.h"

#include "jsoncpp/include/json/json.h"

using namespace Json;

class CPlayerManager
{

private:
	struct TCurrentPlayerInfo
	{
		// old player action
		EPLAYER_ACTION iCurrentAction;

		// the next action
		EPLAYER_ACTION iNextAction;
	};

public:
	CPlayerManager();
	~CPlayerManager();

	void Create(CActorBase* pActor);

	void Release();

	void DoChangeState ( EPLAYER_ACTION nState);

	CC_SYNTHESIZE(EPLAYER_ACTION, m_CurPlayerAction, RecordCurPlayerAction);
	CC_SYNTHESIZE(EPLAYER_ACTION, m_NextPlayerAction, RecordNextPlayerAction);

	CActorBase* GetCurentAction(){ return m_pActorBase; }

	/************************************************************************/
	/* 
	@func:		LoadPersonInfoData
	@param:		string filename
	@return:	void
	@Desc:		load all player info , about socre, location point and so on...
	*/
	/************************************************************************/

	void LoadPersonInfoData(std::string filename);
		
	/************************************************************************/
	/* 
	@func:		LoadPersonInfoData
	@param:		string filename
	@return:	void
	@Desc:		load all player info , about socre, location point and so on...
	*/
	/************************************************************************/

	void SavePersonInfoData();

	/************************************************************************/
	/* 
	@func:		GetPersonInfo
	@param:		__int8 PDBID
	@return:	void
	Desc:		get person infomation by PDBID
	*/
	/************************************************************************/
	TPersonInfo* GetPersonInfo(__int8 PDBID);

private:

	CActorBase*		m_pActorBase;
	CAIPlayer		m_oAiPlayer;
	CArthurKing		m_oArthur;

	TPersonInfoMap  m_mapPersonLocation;
};

extern CPlayerManager g_PalyerManager;

#endif