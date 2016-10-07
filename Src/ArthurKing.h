#ifndef __ARTHUR_KING__
#define __ARTHUR_KING__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#pragma once
#include "ActorBase.h"
#include "PersonMessageEventHandle.h"

class CArthurKingControl;

class CArthurKing :
	public CActorBase,
	public IAIPersonMessageSink
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

	void RequestActorCtrl();

	void PlayStartGo();

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
	IAIPersonMessageSink
	*/
	/************************************************************************/

	virtual void  OnExecMessageHandle ( DWORD nMsgID, LPCSTR szDesc );

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

	struct TMovePathData
	{
		int iCurCol;
		int iCurRow;
		int iNextCol;
		int iNextRow;
		
		int iStepCount;
	};

	TMovePathData stPlayerMovePath;

	CallFunc* pCallFunc_MoveEnd;

	DWORD m_ActorScore;

	CArthurKingControl* m_pCtrl;
};

#endif



