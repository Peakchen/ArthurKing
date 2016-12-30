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

	void LoadPersonLocationInfoData(std::string filename);
		
	/************************************************************************/
	/* 
	@func:		SavePersonLocationInfoData
	@param:		no
	@return:	void
	@Desc:		save all player info , about socre, location point and so on...
	*/
	/************************************************************************/

	void SavePersonLocationInfoData();

	/************************************************************************/
	/*
	@func:		LoadPersonRulePropInfoData
	@param:		string filename
	@return:	void
	@Desc:		load all player rule prop
	*/
	/************************************************************************/

	void LoadPersonRulePropInfoData(std::string filename);

	/************************************************************************/
	/*
	@func:		SavePersonRulePropInfoData
	@param:		no
	@return:	void
	@Desc:		save all player Rule prop
	*/
	/************************************************************************/

	void SavePersonRulePropInfoData();

	/************************************************************************/
	/*
	@func:		LoadPersonPropInfoData
	@param:		string filename
	@return:	void
	@Desc:		load all player rule prop
	*/
	/************************************************************************/

	void LoadPersonPropInfoData(std::string filename);

	/************************************************************************/
	/*
	@func:		SavePersonPropInfoData
	@param:		no
	@return:	void
	@Desc:		save all player prop
	*/
	/************************************************************************/

	void SavePersonPropInfoData();

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

	bool CheckActionSplit(Vec2 opint, CActorBase* pActor, bool bCallback = false, TTileLayerGridProperty** pTileGrid = nullptr);

	/************************************************************************/
	/* 
	@func:		RemoveActorInstace
	@param:		__int8 PDBID
	@return:	void
	Desc:		remove person Instance
	*/
	/************************************************************************/
	void	RemoveActorInstace(int PDBID);

	// 获取当前角色所在的地图规则信息
	TActorTileLayerInfoMap *GetActorPathInfo(){ return &m_mapActorTileLayerInfo; }

	// 获取当前 角色所在位置信息
	TPersonInfoMap		   *GetActorLocInfo(){ return &m_mapPersonLocation; }

	// 设置当前角色 位置信息
	void		SetActorLocInfo(TPersonInfo *pLocInfo, int PDBID);
	
	// 记录当前最后一步的角色
	void			SetFinallyStepPerson(CActorBase *);
	CActorBase*		GetFinallyStepPerson();
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
	
	/************************************************************************/
	/* 
	@func:		__GetTileContextByName
	@param:		const char* szName
	@param:		TTileLayerGridProperty *pTileContext
	@param:		ValueMap mapObject
	@return:	no
	Desc:		get  tile  data context 
	*/
	/************************************************************************/

	void __GetTileContextByName(string szName, TTileLayerGridProperty *pTileContext, ValueMap mapObject);

private:

	CActorBase*		m_pActorBase;
	CAIPlayer		m_oAiPlayer;
	CArthurKing		m_oArthur;

	TPersonInfoMap  m_mapPersonLocation;
	 
	// save all actor instance

	TActorTileLayerInfoMap m_mapActorTileLayerInfo;

	// 记录当前最后一步的角色
	CActorBase*		m_pCurrentActor;
};

extern CPlayerManager g_PalyerManager;

#endif