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

const float CoordinateDiff = 3.0f;

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

	/************************************************************************/
	/* 
	@func:		GetActorInstace
	@param:		__int8 PDBID
	@return:	void
	Desc:		get person Instance by PDBID
	*/
	/************************************************************************/
	CActorBase*	GetActorInstace(__int8 PDBID);

	/************************************************************************/
	/* 
	@func:		AddActorInstace
	@param:		CActorBase* pActor
	@return:	void
	Desc:		add person Instance
	*/
	/************************************************************************/
	void AddActorInstace(CActorBase* pActor);

	/************************************************************************/
	/* 
	@func:		CheckCanTakeAddSocre
	@param:		GWORD &iScore
	@param:		Vec2 oPoint
	@return:	bool
	Desc:		check if add score
	*/
	/************************************************************************/
	
	bool CheckCanTakeAddSocre(GWORD &iScore, Vec2 oPoint);

	/************************************************************************/
	/* 
	@func:		CheckActionSplit
	@param:		CActorBase* pActor
	@param:		Vec2 oPoint
	@return:	bool
	Desc:		check action split
	*/
	/************************************************************************/

	bool CheckActionSplit(Vec2 opint, CActorBase* pActor);

private:

	/************************************************************************/
	/*
	@func:		CheckCanTakeAddSocre
	@param:		GWORD &iScore
	@param:		Vec2 oPoint
	@return:	bool
	Desc:		check if add score
	*/
	/************************************************************************/
	bool DoParseScore(ValueMap mapObject, GWORD &dwScore);

private:

	CActorBase*		m_pActorBase;
	CAIPlayer		m_oAiPlayer;
	CArthurKing		m_oArthur;

	TPersonInfoMap  m_mapPersonLocation;
	 
	// save all actor instance
	typedef map<__int8, CActorBase*> TActorInstanceMap;

	TActorInstanceMap m_mapActorInstanceMap;
};

extern CPlayerManager g_PalyerManager;

#endif