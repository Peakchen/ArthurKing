#ifndef _PLAYER_MANAGER_
#define _PLAYER_MANAGER_

#include "ActorBase.h"
#include "ArthurKing.h"
#include "AIPlayer.h"

#pragma once
#include "MacroDefine.h"

class CPlayerManager
{
public:
	CPlayerManager ( );
	~CPlayerManager ( );

	void initMangaer ( );

	void Release ( );

	void DoChangeState ( EPLAYER_ACTION nState);

private:

	CActorBase*		m_pActorBase;
	CAIPlayer*		m_pAiPlayer;
	CArthurKing*	m_pArthur;

};

#endif