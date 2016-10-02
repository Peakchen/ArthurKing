#pragma once

#include "cocos2d.h"
#include "RockerAction.h"
#include "ArthurKing.h"
#include "cocos-ext.h"
#include "MapReader.h"

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
};

class CGameMainScene :
	public Layer
{
	typedef Vector<SpriteFrame*> TVecSpriteFrame;
public:

	virtual bool init();
	static Scene* createMainScene();
	
	void initMainLayout();

	// update frame node 
	virtual void update(float delta);

	CREATE_FUNC(CGameMainScene);

	void onClick_StartControl(Object* pSender, Control::EventType event);

private:
	void AddSceneMap();

	void AddSetItem();

	// for test 
	void  AddButton_Test();
	void  AddFadeSprite_Test();

	int GetRandomNum(int Randsize);

	void InitPlayerAnimation();

	void addPlayer();

	void GetAnimateVec(int iMin, int iMax, TVecSpriteFrame &vecPlayer_director, EPlayer iState);
	
	void AfterOpenCard();

	void BeginFloatHead();

	void BeginActorGo();

private:
	Size visibleSize;

	CRockerAction* m_pRockerAction;
	CArthurKing* m_pArthurKing;

	SpriteFrameCache* m_pPlayer_1_FrameCache;
	SpriteFrameCache* m_pPlayer_2_FrameCache;

	Animate *m_Pplayer_animate_down;
	Animate *m_Pplayer_animate_up;
	Animate *m_Pplayer_animate_left;
	Animate *m_Pplayer_animate_right;

	TVecSpriteFrame m_vecPlayer_down;
	TVecSpriteFrame m_vecPlayer_left;
	TVecSpriteFrame m_vecPlayer_right;
	TVecSpriteFrame m_vecPlayer_up;

	CallFunc* pCallFunc_AfterOpen;

	int m_CurRandNum;
	DWORD m_CurPalyer_1_Socre;
};

