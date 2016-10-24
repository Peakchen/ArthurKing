#include "SettingMenu.h"
#include "stdafx.h"
#include "ConstUtil.h"


CSettingMenu::CSettingMenu()
{
}


CSettingMenu::~CSettingMenu()
{
}

void CSettingMenu::InitSettingMenu( Point point /*= Point::ZERO*/)
{
	Size oSize = Director::getInstance()->getVisibleSize();

	Size oWinSize = Size::ZERO;

	if (getChildByTag(EBackGround) == NULL)
	{
		Size srcWinSize = Director::getInstance()->getWinSize();
		oWinSize = Size(srcWinSize.width / 2, srcWinSize.height / 2);
	}
	else
		oWinSize = getChildByTag(EBackGround)->getContentSize();

	MenuItemLabel* pMenuItem = nullptr;
	cocos2d::ccMenuCallback pCallBack = CC_CALLBACK_0(CSettingMenu::OnCancleSettingMenuAction, this);
	CreateMenuItemByfontCallback("Exit",
								 pCallBack,
								 20,
								 EFontType_MarkerFelt,
								 &pMenuItem
								/* Point(oWinSize.width, oWinSize.height - 50),
								 Size::ZERO*/
								 );

	if (pMenuItem == nullptr)
		return;

	m_vecMenuItem.pushBack(pMenuItem);

	// this a game exit button
	MenuItemImage* pMenuCloseBtn = nullptr;
	cocos2d::ccMenuCallback pCloseCallBack = CC_CALLBACK_0(CSettingMenu::OnEixtGameCallBack, this);
	CreatMenuItemByeImageCallback(SETTINGMENU_EXIT_NORMAL, 
								  SETTINGMENU_EXIT_SELECTED, 
								  SETTINGMENU_EXIT_SELECTED,
								  pCloseCallBack,
								  &pMenuCloseBtn
								  //Point(point.x / 2 - 20, point.y/2 - 20)
								  //Size::ZERO
								  );

	
	if (pMenuCloseBtn == nullptr)
		return;

	pMenuCloseBtn->setPosition(ccp(point.x / 2 - 100, point.y / 2 - 120));

	m_vecMenuItem.pushBack(pMenuCloseBtn);


	// add a music play button
	MenuItemImage* pMenuMusicPlayBtn = nullptr;
	cocos2d::ccMenuCallback pMusicPlayCallBack = CC_CALLBACK_0(CSettingMenu::OnPlayGameBgMusicCallBack, this);
	CreatMenuItemByeImageCallback(SETTINGMENU_MUSCI_NORMAL,
								  "",
								  SETTINGMENU_MUSIC_SELECTED,
								  pMusicPlayCallBack,
								  &pMenuMusicPlayBtn
								  //Point(point.x/2 - 50, point.y/2 - 50)
								 /*Size::ZERO*/
								  );


	
	if (pMenuMusicPlayBtn == nullptr)
		return;

	pMenuMusicPlayBtn->setPosition(ccp(point.x / 2 - 150, point.y / 2 - 150));
	m_vecMenuItem.pushBack(pMenuMusicPlayBtn);

	//////////////////////////////////////////////////////////////////////////////
	if (m_vecMenuItem.empty()){
		return;
	}

	for (int i = 0 ; i < m_vecMenuItem.size(); ++i)
	{
		//m_vecMenuItem.at(i)->setPosition(point.x / 2 - i * 5, point.y / 2 - i * 5);
	}

	m_pMainMenu = Menu::createWithArray(m_vecMenuItem);
	//m_pMainMenu = Menu::create(pMenuMusicPlayBtn, pMenuCloseBtn);
	m_pMainMenu->alignItemsVertically();

	int index = 0;
	//for( const auto &child : m_pMainMenu->getChildren() )
	//{
	//	auto dstPostion = child->getPosition();
	//	float dtoffset = oWinSize.width/3 - 5*index;
	//	/*if (index % 2 == 0)
	//		ioffset = -ioffset;*/

	//	child->setPosition(Vec2(dstPostion.x + dtoffset, dstPostion.y));
	//	++index;
	//}

	//m_pMainMenu->addChild(Sprite::create(SETTING_MENU_BG));
	m_pMainMenu->setPosition(point);
	m_pMainMenu->setScale(1.2f);
	m_pMainMenu->setOnEnterCallback(CC_CALLBACK_0(CSettingMenu::OnEnterSettingMenuCallBack, this));
	m_pMainMenu->setOnExitCallback(CC_CALLBACK_0(CSettingMenu::OnCancleSettingMenuAction, this));

	
}

CSettingMenu* CSettingMenu::create(const char* szTitle)
{
	CSettingMenu* pSettingMenu = CSettingMenu::create();
	if (!pSettingMenu->init())
	{
		CC_SAFE_DELETE(pSettingMenu);
		return NULL;
	}
	pSettingMenu->autorelease();
	return pSettingMenu;
}

void CSettingMenu::OnEnterSettingMenuCallBack()
{
	Trace_In("%s is start...", __FUNCTION__);
}

void CSettingMenu::OnEixtSettingMenuCallBack(Object* pSender, Control::EventType event)
{
	Trace_In("%s is start...", __FUNCTION__);
	this->removeFromParent();
}

void CSettingMenu::OnCancleSettingMenuAction()
{
	Trace_In("%s is start...", __FUNCTION__);
}

bool CSettingMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	m_isPlayMusic = true;
	return true;
}

void CSettingMenu::onEnter()
{
	Layer::onEnter();

	auto pBg = Sprite::create(POPPLAYER_BG);
	if (pBg == NULL)
	{
		return;
	}

	Point dstPoint = Director::getInstance()->getWinSize();
	pBg->setPosition(Vec2(dstPoint.x/2, dstPoint.y/2));
	

	float dtCloseLoc_x = pBg->getContentSize().width-10.0f;
	float dtCloseLoc_y = pBg->getContentSize().height-10.0f;

	// close button
	auto pCloseSprite = Scale9Sprite::create(POPPLAYER_CLOSE);
	if (pCloseSprite == NULL)
	{
		return;
	}
	auto pCloseBtn = ControlButton::create(pCloseSprite);
	pCloseBtn->addTargetWithActionForControlEvents(this, 
												   cccontrol_selector(CSettingMenu::OnEixtSettingMenuCallBack), 
												   Control::EventType::TOUCH_DOWN
												   );

	pCloseBtn->setPosition(ccp(dtCloseLoc_x, dtCloseLoc_y));
	
	pBg->addChild(pCloseBtn);
	pBg->setTag(EBackGround);
	//addChild(pBg);

	// touch event
	this->setTouchEnabled(true);

	EventDispatcher* pEventDispatcher = Director::getInstance()->getEventDispatcher();
	if (pEventDispatcher != NULL)
	{
		auto pTouchOneByOne = EventListenerTouchOneByOne::create();
		if (pTouchOneByOne)
		{
			pTouchOneByOne->onTouchBegan = CC_CALLBACK_2(CSettingMenu::onTouchBegan, this);
			pTouchOneByOne->onTouchMoved = CC_CALLBACK_2(CSettingMenu::onTouchMoved, this);
			pTouchOneByOne->onTouchEnded = CC_CALLBACK_2(CSettingMenu::onTouchEnded, this);
			pTouchOneByOne->onTouchCancelled = CC_CALLBACK_2(CSettingMenu::onTouchCancelled, this);
			pEventDispatcher->addEventListenerWithSceneGraphPriority(pTouchOneByOne, this);
			pTouchOneByOne->setSwallowTouches(true);
		}
	}

	// finally todo... build main setting menu
	Size oSize = Director::getInstance()->getVisibleSize();
	InitSettingMenu(Point(oSize.height / 2, oSize.width / 2));

	addChild(pBg);
	addChild(m_pMainMenu);

}

void CSettingMenu::onExit()
{
	Layer::onExit();
	Trace_In("%s is Exit...", __FUNCTION__);
}

bool CSettingMenu::onTouchBegan(Touch *touch, Event *unused_event)
{
	CCLOG("%s is start...", __FUNCTION__);

	CCLOG("Paddle::onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);

	return true;
}

void CSettingMenu::onTouchMoved(Touch *touch, Event *unused_event)
{
	Trace_In("%s is starting -------------------------", __FUNCTION__);
}

void CSettingMenu::onTouchEnded(Touch *touch, Event *unused_event)
{
	Trace_In("%s is starting -------------------------", __FUNCTION__);
}

void CSettingMenu::onTouchCancelled(Touch *touch, Event *unused_event)
{
	Trace_In("%s is starting -------------------------", __FUNCTION__);
}

void CSettingMenu::OnEixtGameCallBack()
{
	//exit sence
	Director::getInstance()->end();
}

void CSettingMenu::OnPlayGameBgMusicCallBack()
{
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		CCLOG("bg musci is playing. --------------------------------");
	}

	if (m_isPlayMusic)
	{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		m_isPlayMusic = false;
	}
	else
	{
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		m_isPlayMusic = true;
	}
}
