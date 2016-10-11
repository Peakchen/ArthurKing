#ifndef __ARTHUR_KING__
#define __ARTHUR_KING__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#pragma once
#include "ActorBase.h"

class CArthurKingControl;

class CArthurKing :
	public CActorBase
{
public:
	CArthurKing();
	~CArthurKing();

	// Create Arthur King 
	/***************************
	* func: Create Arthur King actor 
	* param: strArthurKingName is picture' name
	* return: void
	*************************/
	static CArthurKing* CreateArthurKing(SpriteFrame* pFrame);

	bool init();

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

	virtual void UpdateScoreItem ( int addScore );

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
	// to Check actor is runing?
	bool m_bCheckActorRuning;

	bool m_bActorRunDirector; //actor run director
	
	Sprite* m_pActorSprite; // sprite addr
	char* m_szSpriteName; // init picture name

	//四方向动画
	Animate* m_pActor_Left_Animate;
	Animate* m_pActor_Right_Animate;
	Animate* m_pActor_Up_Animate;
	Animate* m_pActor_Down_Animate;

	DWORD m_ActorScore;

	CArthurKingControl* m_pCtrl;

	Vector<SpriteFrame*> m_vecAnim_Left;
	Vector<SpriteFrame*> m_vecAnim_Right;
	Vector<SpriteFrame*> m_vecAnim_Up;
	Vector<SpriteFrame*> m_vecAnim_Down;
};

#endif



