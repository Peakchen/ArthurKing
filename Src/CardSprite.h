#pragma once
/************************************************************************/
/* author: cqf
   date: 2016/09/17
   version: 1.0
   desc: Open Card
*/
/************************************************************************/

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ArthurKing.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum EMyCardAngle
{
	ECardAngleIn	=	270,			//In Card at Z 
	ECardAngleDelta	=	90,				//

	ECardAngleOut	=	0,				//
	ECardAngleOutDelta = 90,			//
};

enum ECardTag
{
	EInCard = 1,
	EOutCard,
};

const int Btn_Single_Game_TAG = 1001;

class CCardSprite :
	public Sprite
{
public:
	CCardSprite();
	~CCardSprite();

	virtual bool init(const char* strInCard, const char* strOutCard, float fDuration, bool bAiAutoOpen);

	static	CCardSprite* create(const char* strInCard, const char* strOutCard, float fDuration, bool bAiAutoOpen);
	void  DoOpenCard();

	void GameChangeTouchDown(Object* pSender, Control::EventType event);

private:
	bool m_isOpen;
	CCSpawn* m_pAnimInOpen;
	CCSpawn* m_pAnimOutOpen;

	Size visibleSize;

	CArthurKing* m_pArthur;
	int m_RandNum;

	CallFunc* pCallFunc_AfterOpen;

private:
	void initCardData(const char* strInCard, const char* strOutCard, float fDuration, bool bAiAutoOpen);

	bool __CheckCardSpriteLoad();

	void AfterOpenCard();

	void OnAfterOpenCard_FireEvent();
};

