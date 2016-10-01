#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

const int Btn_Width = 222;
const int Btn_Height = 50;
const int Btn_FontSize = 20;
const int Quit_Dialog_Size_Width = 400;
const int Quit_Dialog_Size_Height = 220;
//const int Btn_Padding = 60;
const int Btn_Single_Game_TAG = 10001;
const int Btn_Save_Game_TAG = 10002;
const int Btn_Music_TAG = 10003;
const int Btn_Quit_Game_TAG = 10004;
const int Btn_Quit_OK_TAG = 10005;
const int Btn_Quit_Cancel_TAG = 10006;

class CGameMenuScene :
	public LayerColor
{
public:

	static Scene* createMenuScene();

	virtual bool init();

	void initScreenLayout();

	void AddBackground();

	void AddMenuButton();

	void GameStartTouchDown(Object* pSender, Control::EventType event);
	CREATE_FUNC(CGameMenuScene);
private:
	Size visibleSize;
	
};

