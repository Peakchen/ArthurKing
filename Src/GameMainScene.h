#pragma once

#include "cocos2d.h"
#include "ArthurKing.h"
#include "cocos-ext.h"
#include "MapReader.h"
#include "AIPlayer.h"
#include "PersonMessageEventHandle.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum EMainMenuItemTag
{
	ESTART_TEST = 2001, 
	ECARD_TEST,
	EFADESPRITE_TEST,
};

// ½ÇÉ« Ã¶¾Ù
enum EPlayer
{
	EFirstPlayer = 1,
	ESecondPlayer,
};

class CGameMainScene :
	public Layer,
	public IAIPersonMessageSink
{
	typedef Vector<SpriteFrame*> TVecSpriteFrame;
public:

	virtual bool init();
	static Scene* createMainScene();

	/************************************************************************/
	/*
	IAIPersonMessageSink
	*/
	/************************************************************************/

	virtual void  OnExecMessageHandle(DWORD nMsgID, LPCSTR szDesc);

	CREATE_FUNC(CGameMainScene);

	void onClick_StartControl(Object* pSender, Control::EventType event);

private:
	void AddSceneMap();

	void AddSetItem();

	// for test 
	void  AddButton_Test();
	void  AddFadeSprite_Test();

	void InitPlayerAnimation();

	void addPlayer();
	void addAI();

	void GetAnimateVec(int iMin, int iMax, TVecSpriteFrame &vecPlayer_director, EPlayer iState);
	
	void AfterOpenCard();

	void BeginFloatHead();

	void BeginActorGo();

	void TurnToGoAction();

private:
	Size visibleSize;

	CActorBase* m_pCurAction;

	/////////////////////ACTOR ////////////////////////
	CArthurKing* m_pArthurKing;

	SpriteFrameCache* m_pPlayer_1_FrameCache;

	Animate *m_Pplayer_animate_down;
	Animate *m_Pplayer_animate_up;
	Animate *m_Pplayer_animate_left;
	Animate *m_Pplayer_animate_right;

	TVecSpriteFrame m_vecPlayer_down;
	TVecSpriteFrame m_vecPlayer_left;
	TVecSpriteFrame m_vecPlayer_right;
	TVecSpriteFrame m_vecPlayer_up;

	/////////////////////AI ////////////////////////

	CAIPlayer* m_pAIplayer;
	SpriteFrameCache* m_pPlayer_2_FrameCache;

	Animate *m_PAI_animate_down;
	Animate *m_PAI_animate_up;
	Animate *m_PAI_animate_left;
	Animate *m_PAI_animate_right;

	TVecSpriteFrame m_vecPAI_down;
	TVecSpriteFrame m_vecPAI_left;
	TVecSpriteFrame m_vecPAI_right;
	TVecSpriteFrame m_vecPAI_up;

	//////////////////////////////////////////

	CallFunc* pCallFunc_AfterOpen;

	int m_CurRandNum;
	DWORD m_CurPalyer_Socre;

	CallFunc* pCallFunc_CreateCard;
};

