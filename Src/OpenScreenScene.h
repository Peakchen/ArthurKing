#pragma once

#include "cocos2d.h"
#include "2d\CCLayer.h"
#include "ConstUtil.h"

USING_NS_CC;

const  double MOVE_SPLEED = 0.5f;
const int ONE_SECOND = 1;

class COpenScreenScene :
	public Layer
{
public:

	static Scene* createOpenScreenScene();

	virtual bool init();

	void moveKeSpriteToLeft();
	void moveMaiSpriteToLeft();
	void initMoveSprite();
	void startMoveSprite(float dt);
	void gotoMenuScene();
	void spriteFadeOut();
	CREATE_FUNC(COpenScreenScene);

private:
	Sprite* pch_2_Sprite;
	Sprite* pch_3_Sprite;
	Sprite* pch_4_Sprite;
	Sprite* pch_1_Sprite;
	Size visibleSize;
	Size spriteSize;
};

