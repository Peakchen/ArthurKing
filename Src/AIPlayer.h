
#ifndef _CAI_PLAYER_
#define _CAI_PLAYER_

#pragma once

#include "cocos2d.h"
#include "ActorBase.h"

class CArthurKingControl;

USING_NS_CC;

class CAIPlayer :
	public CActorBase
{
public:
	CAIPlayer ( );
	~CAIPlayer ( );

	/************************************************************************/
	/*
	CActorBase:

	OnEnter()
	*/
	/************************************************************************/
	virtual void OnEnter ( );

	/************************************************************************/
	/*
	CActorBase:

	OnLeave()
	*/
	/************************************************************************/
	virtual void OnLeave ( );

	/************************************************************************/
	/*
	func: request ctrl action
	return: void

	*/
	/************************************************************************/
	virtual void RequestActorCtrl();

	/************************************************************************/
	/*
	func: player start go
	return: void
	*/
	/************************************************************************/
	virtual void PlayStartGo();

	/***************************
	* func: Create ai
	* param: strName is picture' name
	* return: void
	*************************/
	static CAIPlayer* CreateAIPlayer ( SpriteFrame* pFrame );

	virtual void UpdateScoreItem(int addScore);

private:
	DWORD m_ActorScore;

	CArthurKingControl* m_pCtrl;
};

#endif