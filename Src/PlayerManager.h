#ifndef _PLAYER_MANAGER_
#define _PLAYER_MANAGER_

#include "ActorBase.h"
#include "ArthurKing.h"
#include "AIPlayer.h"

#pragma once
#include "MacroDefine.h"

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
	CPlayerManager ( );
	~CPlayerManager ( );

	void Create(CActorBase* pActor);

	void Release ( );

	void DoChangeState ( EPLAYER_ACTION nState);

	CC_SYNTHESIZE(EPLAYER_ACTION, m_CurPlayerAction, RecordCurPlayerAction);
	CC_SYNTHESIZE(EPLAYER_ACTION, m_NextPlayerAction, RecordNextPlayerAction);

	CActorBase* GetCurentAction(){ return m_pActorBase; }

private:

	CActorBase*		m_pActorBase;
	CAIPlayer		m_oAiPlayer;
	CArthurKing		m_oArthur;

};

extern CPlayerManager g_PalyerManager;

#endif