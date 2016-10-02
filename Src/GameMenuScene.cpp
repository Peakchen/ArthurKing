#include "GameMenuScene.h"
#include "ConstUtil.h"
#include "GameMainScene.h"

USING_NS_CC;

bool CGameMenuScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	initScreenLayout();

	return true;
}

void CGameMenuScene::initScreenLayout()
{
	// ��ʼ�� ����
	AddBackground();
	// ��ʼ����ť
	AddMenuButton();
}

void CGameMenuScene::AddBackground()
{
	Sprite* pALi = Sprite::create(ALI);
	if (pALi != NULL)
	{
		pALi->setPosition(ccp(visibleSize.width - 30, visibleSize.height - 30));
		pALi->setAnchorPoint(ccp(1, 1));
		pALi->setScale(0.5f);
		addChild(pALi);
	}

	Sprite* pRainBow = Sprite::create(RAINBOW);
	if (pRainBow != NULL)
	{
		pRainBow->setPosition(ccp(5, visibleSize.height - 20));
		pRainBow->setAnchorPoint(ccp(0, 1));
		pRainBow->setScale(0.6f);
		addChild(pRainBow);
	}

	Sprite* pMenuLogo = Sprite::create(MENU_LOGO);
	if (pMenuLogo != NULL)
	{
		pMenuLogo->setPosition(ccp(visibleSize.width / 2, visibleSize.height));
		pMenuLogo->setAnchorPoint(ccp(0.5, 1));
		pMenuLogo->setScale(0.6f);
		addChild(pMenuLogo);
	}

	MoveBy* pAli_Move = MoveBy::create(1, ccp(8, 0));
	MoveBy* pAli_MoveReverse = pAli_Move->reverse();
	Sequence* pAliSequence = Sequence::create(pAli_Move, pAli_MoveReverse, NULL);
	pALi->runAction(RepeatForever::create(pAliSequence));

	MoveBy* pRainBow_Move = MoveBy::create(1, ccp(8, 0));
	MoveBy* pRainBow_MoveReverse = pRainBow_Move->reverse();
	Sequence* pRainBowSequence = Sequence::create(pRainBow_Move, pRainBow_MoveReverse, NULL);
	pRainBow->runAction(RepeatForever::create(pRainBowSequence));
}

void CGameMenuScene::AddMenuButton()
{
	//��Ϸ��ʼ ��ť 
	Scale9Sprite* pBtn_NormalSprite = Scale9Sprite::create(NORMAL_MENU);
	Scale9Sprite* pBtn_PressSprite = Scale9Sprite::create(PRESS_MENU);
	if (pBtn_NormalSprite == NULL)
	{
		CCLOG(" pBtn_NormalSprite �Ƿ��Ź�����.");
		return;
	}

	if (pBtn_PressSprite == NULL)
	{
		CCLOG(" pBtn_PressSprite �Ƿ��Ź�����.");
		return;
	}

	LabelTTF* pbtn_LabelTTF = LabelTTF::create("Start", FONT_MENU, Btn_FontSize);
	if (pbtn_LabelTTF == NULL)
	{
		CCLOG(" pbtn_LabelTTF �Ƿ��Ź�����.");
		return;
	}

	ControlButton* pCtrl_Btn = ControlButton::create(pbtn_LabelTTF, pBtn_NormalSprite);
	if (pCtrl_Btn == NULL)
	{
		CCLOG(" pCtrl_Btn �Ƿ��Ź�����.");
		return;
	}
	pCtrl_Btn->setBackgroundSpriteForState(pBtn_PressSprite, Control::State::SELECTED);

	pCtrl_Btn->setPosition(ccp(visibleSize.width/2, visibleSize.height - 200));
	pCtrl_Btn->setPreferredSize(Size(Btn_Width, Btn_Height));
	pCtrl_Btn->addTargetWithActionForControlEvents(this, cccontrol_selector(CGameMenuScene::GameStartTouchDown), Control::EventType::TOUCH_DOWN);
	pCtrl_Btn->setTag(Btn_Single_Game_TAG);
	addChild(pCtrl_Btn);

	// ��Ϸ�浵
	Scale9Sprite* pSave_NormalSprite = Scale9Sprite::create(NORMAL_MENU);
	Scale9Sprite* pSave_PressSprite = Scale9Sprite::create(PRESS_MENU);
	if (pSave_NormalSprite == NULL)
	{
		CCLOG(" pSave_NormalSprite �Ƿ��Ź�����.");
		return;
	}
	if (pSave_PressSprite == NULL)
	{
		CCLOG(" pSave_PressSprite �Ƿ��Ź�����.");
		return;
	}
	LabelTTF* pSave_LabelTTF = LabelTTF::create("Save", FONT_MENU, Btn_FontSize);
	if (pSave_LabelTTF == NULL)
	{
		CCLOG(" pSave_LabelTTF �Ƿ��Ź�����.");
		return;
	}
	ControlButton* pCtrlBtn_Save = ControlButton::create(pSave_LabelTTF, pSave_NormalSprite);
	if (pCtrlBtn_Save == NULL)
	{
		CCLOG(" pCtrlBtn_Save �Ƿ��Ź�����.");
		return;
	}
	pCtrlBtn_Save->setBackgroundSpriteForState(pSave_PressSprite, Control::State::SELECTED);

	pCtrlBtn_Save->setPosition(ccp(visibleSize.width / 2, visibleSize.height - 260));
	pCtrlBtn_Save->setPreferredSize(Size(Btn_Width, Btn_Height));
	pCtrlBtn_Save->addTargetWithActionForControlEvents(this, cccontrol_selector(CGameMenuScene::GameStartTouchDown), Control::EventType::TOUCH_DOWN);
	pCtrlBtn_Save->setTag(Btn_Save_Game_TAG);
	addChild(pCtrlBtn_Save);
	
	// ��Ϸ����
	Scale9Sprite* pMusic_NormalSprite = Scale9Sprite::create(NORMAL_MENU);
	Scale9Sprite* pMusic_PressSprite = Scale9Sprite::create(PRESS_MENU);
	if (pMusic_NormalSprite == NULL || pMusic_PressSprite == NULL)
	{
		CCLOG("��Ϸ���� pMusic_NormalSprite or pMusic_PressSprite �Ƿ��Ź�����.");
		return;
	}

	LabelTTF* pMusic_LabelTTF = NULL;
	bool bMusic_On = UserDefault::getInstance()->getBoolForKey(MUSIC_ON, true);
	if (bMusic_On)
	{
		pMusic_LabelTTF = LabelTTF::create("On", FONT_MENU, Btn_FontSize);
	}
	else
	{
		pMusic_LabelTTF = LabelTTF::create("Off", FONT_MENU, Btn_FontSize);
	}
	
	if (pMusic_LabelTTF == NULL)
	{
		CCLOG(" pMusic_LabelTTF �Ƿ��Ź�����.");
		return;
	}
	ControlButton* pCtrlBtn_Music = ControlButton::create(pMusic_LabelTTF, pMusic_NormalSprite);
	if (pCtrlBtn_Music == NULL)
	{
		CCLOG(" pCtrlBtn_Music �Ƿ��Ź�����.");
		return;
	}
	pCtrlBtn_Music->setBackgroundSpriteForState(pMusic_PressSprite, Control::State::SELECTED);

	pCtrlBtn_Music->setPosition(ccp(visibleSize.width / 2, visibleSize.height - 320));
	pCtrlBtn_Music->setPreferredSize(Size(Btn_Width, Btn_Height));
	pCtrlBtn_Music->addTargetWithActionForControlEvents(this, cccontrol_selector(CGameMenuScene::GameStartTouchDown), Control::EventType::TOUCH_DOWN);
	pCtrlBtn_Music->setTag(Btn_Music_TAG);
	addChild(pCtrlBtn_Music);

	// �˳���Ϸ
	Scale9Sprite* pQuit_NormalSprite = Scale9Sprite::create(NORMAL_MENU);
	Scale9Sprite* pQuit_PressSprite = Scale9Sprite::create(PRESS_MENU);

	if (pQuit_NormalSprite == NULL || pQuit_PressSprite == NULL)
	{
		CCLOG("�˳���Ϸ pQuit_NormalSprite or pQuit_PressSprite �Ƿ��Ź�����.");
		return;
	}
	LabelTTF* pQuit_LabelTTF = LabelTTF::create(QUIT_GAME, FONT_MENU, Btn_FontSize);
	if (pQuit_LabelTTF == NULL)
	{
		CCLOG("�˳���Ϸ pQuit_LabelTTF�Ƿ��Ź�����.");
		return;
	}
	ControlButton* pCtrlBtn_Quit = ControlButton::create(pQuit_LabelTTF, pQuit_NormalSprite);
	if (pCtrlBtn_Quit == NULL)
	{
		CCLOG("�˳���Ϸ pCtrlBtn_Quit�Ƿ��Ź�����.");
		return;
	}
	pCtrlBtn_Quit->setBackgroundSpriteForState(pQuit_PressSprite, Control::State::SELECTED);

	pCtrlBtn_Quit->setPosition(ccp(visibleSize.width / 2, visibleSize.height - 380));
	pCtrlBtn_Quit->setPreferredSize(Size(Btn_Width, Btn_Height));
	pCtrlBtn_Quit->addTargetWithActionForControlEvents(this, cccontrol_selector(CGameMenuScene::GameStartTouchDown), Control::EventType::TOUCH_DOWN);
	pCtrlBtn_Quit->setTag(Btn_Quit_Game_TAG);
	addChild(pCtrlBtn_Quit);
}

void CGameMenuScene::GameStartTouchDown(Object* pSender, Control::EventType event)
{
	if (event != Control::EventType::TOUCH_DOWN)
	{
		CCLOG("����¼� ��Control::EventType::TOUCH_DOWN .");
		return;
	}
	ControlButton* pCtrlBtn = static_cast<ControlButton*>(pSender);
	if (pCtrlBtn == NULL)
	{
		CCLOG(" GameStartTouchDown �Ƿ���ť����.");
		return;
	}

	int iTag = pCtrlBtn->getTag();
	switch (iTag)
	{
		case Btn_Single_Game_TAG:
			{
				Scene* pMainScene = CGameMainScene::createMainScene();
				if (pMainScene == NULL)
				{
					CCLOG("error: %s ����������ʧ��...", __FUNCTION__);
					return;
				}
				Director::getInstance()->pushScene(pMainScene);
			}
			break;
		case Btn_Save_Game_TAG:
			{

			}
			break;
		case Btn_Music_TAG:
			{

			}
			break;
		case Btn_Quit_Game_TAG:
			{

			}
			break;
		default:
			CCLOG("error Tag...");
			return;
	}

}

Scene* CGameMenuScene::createMenuScene()
{
	auto scene = Scene::create();
	auto layer = CGameMenuScene::create();
	scene->addChild(layer);
	return scene;
}
