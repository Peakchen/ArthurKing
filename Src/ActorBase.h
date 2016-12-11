
#ifndef _CACTOR_BASE_
#define _CACTOR_BASE_

#pragma once
#include "IActorBase.h"
#include "cocos2d.h"
#include "common.h"
#include "Entity\EntityServer.h"


USING_NS_CC;

class CActorBase : 
	public IActorBase,
	public Sprite,
	public IEntity
{
public:
	CActorBase();
	~CActorBase();

	virtual void setvecAnim_Left(Vector<SpriteFrame*> pSpriteFrame) = 0;
	virtual Vector<SpriteFrame*> getvecAnim_Left() = 0;

	virtual void setvecAnim_Right(Vector<SpriteFrame*> pSpriteFrame) = 0;
	virtual Vector<SpriteFrame*> getvecAnim_Right() = 0;

	virtual void setvecAnim_down(Vector<SpriteFrame*> pSpriteFrame) = 0;
	virtual Vector<SpriteFrame*> getvecAnim_down() = 0;

	virtual void setvecAnim_up(Vector<SpriteFrame*> pSpriteFrame) = 0;
	virtual Vector<SpriteFrame*> getvecAnim_up() = 0;

	/*CC_SYNTHESIZE(Vector<SpriteFrame*>, vecPlayer_anim_Left, vecAnim_Left);
	CC_SYNTHESIZE(Vector<SpriteFrame*>, vecPlayer_anim_right, vecAnim_Right);
	CC_SYNTHESIZE(Vector<SpriteFrame*>, vecPlayer_anim_down, vecAnim_down);
	CC_SYNTHESIZE(Vector<SpriteFrame*>, vecPlayer_anim_up, vecAnim_up);*/


	CC_SYNTHESIZE(std::vector<int>, m_passColPath, RecordPassColPath);
	CC_SYNTHESIZE(std::vector<int>, m_passRowPath, RecordPassRowPath);

	virtual void GetPlayerGoPath(int iStepCount, int** arrCanGoGrid);

	/************************************************************************/
	/* 
		func: update score
		return : void
	*/
	/************************************************************************/
	virtual void UpdateScoreItem ( int addScore ) ;

	/************************************************************************/
	/* 
		func: goto current state, to do current action
		return: void
		param: no
	*/
	/************************************************************************/
	virtual void OnEnter ( ) = 0;

	/************************************************************************/
	/*
	func: leave current state, to delete action
	return: void
	param: no
	*/
	/************************************************************************/
	virtual void OnLeave ( ) = 0;

	/************************************************************************/
	/* 
		func: request ctrl action
		return: void

	*/
	/************************************************************************/
	virtual void RequestActorCtrl() = 0;

	/************************************************************************/
	/* 
		func: player start go
		return: void
	*/
	/************************************************************************/
	virtual void PlayStartGo() = 0;

	/************************************************************************/
	/* 
		@func:		GetOwnerSelfScore()
		@param:		GWORD score
		@return:	no
		@desc:		get own score
	*/
	/************************************************************************/
	virtual void GetOwnerSelfScore(GWORD& score) = 0;

	/************************************************************************/
	/* 
	@func:		SetOwnerSelfScore()
	@param:		GWORD score
	@return:	no
	@desc:		set own score
	*/
	/************************************************************************/
	virtual void SetOwnerSelfScore(GWORD score) = 0;

	/************************************************************************/
	/* 
		@func:		GetPDBID()
		@param:		no
		@return:	__int8 PDBID
	*/
	/************************************************************************/
	virtual __int8 GetPDBID() = 0;

	/************************************************************************/
	/* 
	@func:		AddScore()
	@param:		GWORD iaddScore
	@return:	no
	@desc:		add some score to owner score
	*/
	/************************************************************************/
	virtual void AddScore(GWORD iaddScore) = 0;
	
	/************************************************************************/
	/*
	@func:		SubScore()
	@param:		GWORD iSubScore
	@return:	no
	@desc:		sub some score from owner score
	*/
	/************************************************************************/
	virtual void SubScore(GWORD iSubScore) = 0;

	//////////////////////////////IEntity/////////////////////////////////
	/************************************************************************/
	/*
	//通过实体 dbid
	*/
	/************************************************************************/
	virtual int		GetEntityPDBID();

	/************************************************************************/
	/*
	// 通过 规则属性ID获取实体属性值
	*/
	/************************************************************************/
	virtual int		GetEntityRuleProp(int iRulePropID);

	//设置属性值
	virtual void	SetActorProp(int tyPropID, int iPropValue) = 0;
	//获得属性值
	virtual int		GetActorProp(int tyPropID) = 0;

	// 获取当前翻牌事件 信息
	virtual int		GetNextStepEventID() = 0;
	virtual std::string		GetNextStepEventDesc() = 0;

private:
	void GetCanGoColRowData(int iRandnum, int iCol, int iRow, int& iNextCol, int &iNextRow);

private:
	GWORD m_dwScore;
};

#endif

