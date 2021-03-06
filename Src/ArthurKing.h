#ifndef __ARTHUR_KING__
#define __ARTHUR_KING__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#pragma once
#include "ActorBase.h"
#include "common.h"
#include "IActorBase.h"

class CArthurKingControl;

class CArthurKing :
	public CActorBase
{
public:
	CArthurKing();
	explicit CArthurKing(__int8 PDBID);
	~CArthurKing();

	// Create Arthur King 
	/***************************
	* func: Create Arthur King actor 
	* param: strArthurKingName is picture' name
	* return: void
	*************************/
	static CArthurKing* CreateArthurKing(SpriteFrame* pFrame, __int8 PDBID);

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

	/************************************************************************/
	/*
	@func:		AddScore()
	@param:		GWORD iaddScore
	@return:	no
	@desc:		add some score to owner score
	*/
	/************************************************************************/
	virtual void AddScore(GWORD iaddScore);

	/************************************************************************/
	/*
	@func:		SubScore()
	@param:		GWORD iSubScore
	@return:	no
	@desc:		sub some score from owner score
	*/
	/************************************************************************/
	virtual void SubScore(GWORD iSubScore);

	/////////////////////////////////four Sprite Frame////////////////////////////////////////////////////////
	inline virtual void setvecAnim_Left(Vector<SpriteFrame*> pSpriteFrame){ m_vecAnim_Left = pSpriteFrame; }
	inline virtual Vector<SpriteFrame*> getvecAnim_Left(){ return m_vecAnim_Left; }

	inline virtual void setvecAnim_Right(Vector<SpriteFrame*> pSpriteFrame){ m_vecAnim_Right = pSpriteFrame; }
	inline virtual Vector<SpriteFrame*> getvecAnim_Right(){ return m_vecAnim_Right; }

	inline virtual void setvecAnim_down(Vector<SpriteFrame*> pSpriteFrame){ m_vecAnim_Down = pSpriteFrame; }
	inline virtual Vector<SpriteFrame*> getvecAnim_down(){ return m_vecAnim_Down; }

	inline virtual void setvecAnim_up(Vector<SpriteFrame*> pSpriteFrame){ m_vecAnim_Up = pSpriteFrame; }
	inline virtual Vector<SpriteFrame*> getvecAnim_up(){ return m_vecAnim_Up; }

	//////////////////////////////////Property/////////////////
	//设置属性值
	virtual void	SetActorProp(int tyPropID, int iPropValue);
	//获得属性值
	virtual int		GetActorProp(int tyPropID);

	//////////////////////////////IEntity/////////////////////////////////
	/************************************************************************/
	/*
	//取得实体 dbid
	*/
	/************************************************************************/
	virtual int		GetEntityPDBID();

	/************************************************************************/
	/*
	// 通过 规则属性ID获取实体属性值
	*/
	/************************************************************************/
	virtual int		GetEntityRuleProp(int iRulePropID);

	///////////////////////////////////////////////////

	virtual int		GetNextStepEventID();

	virtual std::string		GetNextStepEventDesc();

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

	GWORD m_ActorScore;
	__int8 m_PDBID;

	CArthurKingControl* m_pCtrl;

	Vector<SpriteFrame*> m_vecAnim_Left;
	Vector<SpriteFrame*> m_vecAnim_Right;
	Vector<SpriteFrame*> m_vecAnim_Up;
	Vector<SpriteFrame*> m_vecAnim_Down;

	////////////////////Prop///////////////////////////
	TActorPropMap m_PropMap;
	TActorRulePropMap m_stRulePropMap;
};

#endif



