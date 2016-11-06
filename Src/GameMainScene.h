#pragma once

#include "cocos2d.h"
#include "ArthurKing.h"
#include "cocos-ext.h"
#include "MapReader.h"
#include "AIPlayer.h"
#include "PersonMessageEventHandle.h"
#include "common/common.h"
#include "TileBase.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CResCreator;

enum EMainMenuItemTag
{
	ESTART_SETTINGMENU = 2001, 
	ECARD_TEST,
	EFADESPRITE_TEST,
	ESTART_Go,
	ESTART_EXCHANGE,
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

	virtual void  OnExecMessageHandle(GWORD nMsgID, LPCSTR szDesc);

	CREATE_FUNC(CGameMainScene);

	void onClick_StartControl(Object* pSender, Control::EventType event);

	/************************************************************************/
	/* 
	@func:		onClick_StartShowSettingMenu
	@param:		Object* pSender
	@param:		Control::EventType event
	@return:	void
	@brief:		if this Buttun Event is hinted, then create Menu UI 
	*/
	/************************************************************************/
	void onClick_StartShowSettingMenu(Object* pSender, Control::EventType event);

	/** Callback function for touch began.
	*
	* @param touch Touch information.
	* @param unused_event Event information.
	* @return if return false, onTouchMoved, onTouchEnded, onTouchCancelled will never called.
	* @js NA
	*/
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	/** Callback function for touch moved.
	*
	* @param touch Touch information.
	* @param unused_event Event information.
	* @js NA
	*/
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	/** Callback function for touch ended.
	*
	* @param touch Touch information.
	* @param unused_event Event information.
	* @js NA
	*/
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	/** Callback function for touch cancelled.
	*
	* @param touch Touch information.
	* @param unused_event Event information.
	* @js NA
	*/
	virtual void onTouchCancelled(Touch *touch, Event *unused_event);

	/************************************************************************/
	/* 
	func: 
	*/
	/************************************************************************/

	void	OnEvent_DealWithSpiltActionCallBack();

	/************************************************************************/
	/*
	@func:		CheckActionSplit
	@param:		CActorBase* pActor
	@param:		Vec2 oPoint
	@return:	bool
	Desc:		check action split
	*/
	/************************************************************************/

	//bool CheckActionSplit(Vec2 opint, CActorBase* pActor);

private:
	void AddSceneMap();

	void AddSetItem();

	// for test 
	void  AddButton_SettingMenu();
	void  AddFadeSprite_Test();

	void InitPlayerAnimation();

	void addPlayer();
	void addAI();

	void GetAnimateVec(int iMin, int iMax, TVecSpriteFrame &vecPlayer_director, EPlayer iState);
	
	void AfterOpenCard();

	void BeginFloatHead();

	void BeginActorGo();

	void TurnToGoAction();

	/************************************************************************/
	/*	
	@func:		AddButton_StartGoAction
	@param:		no
	@return:	no
	@brief:		player start go
	*/
	/************************************************************************/
	void AddButton_StartGoAction();

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
	
	bool GetTheLastStepPoint(Vec2 **point);

	void CreateSequenceAboutOpenCardAction();

	void CreateThreadChechPopupCloseAction();

private:

	//friend class CArthurKingControl;

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
	GWORD m_CurPalyer_Socre;

	CallFunc* pCallFunc_CreateCard;

	//ai auto open card state
	bool m_bAiAutoOpen;

	/////////////////////////////

	TTileLayerGridProperty* m_pstTileGridProperty;

	// dialog close flag
	bool m_bDialog_close;

	std::mutex m_MainPopMutex;
};

