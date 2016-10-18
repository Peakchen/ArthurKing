
#ifndef _CAI_PLAYER_
#define _CAI_PLAYER_

#pragma once

#include "cocos2d.h"
#include "ActorBase.h"
#include "common.h"

class CArthurKingControl;

USING_NS_CC;

class CAIPlayer :
	public CActorBase
{
public:
	CAIPlayer();
	CAIPlayer(__int8 PDBID);
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
	static CAIPlayer* CreateAIPlayer ( SpriteFrame* pFrame , __int8 PDBID);

	virtual void UpdateScoreItem(int addScore);

	/************************************************************************/
	/*
	@func:		GetOwnerSelfScore()
	@param:		GWORD score
	@return:	no
	@desc:		get own score
	*/
	/************************************************************************/
	virtual void GetOwnerSelfScore(GWORD& score);

	/************************************************************************/
	/*
	@func:		SetOwnerSelfScore()
	@param:		GWORD score
	@return:	no
	@desc:		set own score
	*/
	/************************************************************************/
	virtual void SetOwnerSelfScore(GWORD score);

	/************************************************************************/
	/*
	@func:		GetPDBID()
	@param:		no
	@return:	__int8 PDBID
	*/
	/************************************************************************/
	virtual __int8 GetPDBID();

	/////////////////////////////////four Sprite Frame////////////////////////////////////////////////////////
	inline virtual void setvecAnim_Left(Vector<SpriteFrame*> pSpriteFrame){ m_vecAnim_Left = pSpriteFrame; }
	inline virtual Vector<SpriteFrame*> getvecAnim_Left(){ return m_vecAnim_Left; }

	inline virtual void setvecAnim_Right(Vector<SpriteFrame*> pSpriteFrame){ m_vecAnim_Right = pSpriteFrame; }
	inline virtual Vector<SpriteFrame*> getvecAnim_Right(){ return m_vecAnim_Right; }

	inline virtual void setvecAnim_down(Vector<SpriteFrame*> pSpriteFrame){ m_vecAnim_Down = pSpriteFrame; }
	inline virtual Vector<SpriteFrame*> getvecAnim_down(){ return m_vecAnim_Down; }

	inline virtual void setvecAnim_up(Vector<SpriteFrame*> pSpriteFrame){ m_vecAnim_Up = pSpriteFrame; }
	inline virtual Vector<SpriteFrame*> getvecAnim_up(){ return m_vecAnim_Up; }

private:
	GWORD m_ActorScore;

	__int8 m_PDBID;

	CArthurKingControl* m_pCtrl;

	Vector<SpriteFrame*> m_vecAnim_Left;
	Vector<SpriteFrame*> m_vecAnim_Right;
	Vector<SpriteFrame*> m_vecAnim_Up;
	Vector<SpriteFrame*> m_vecAnim_Down;
};

#endif