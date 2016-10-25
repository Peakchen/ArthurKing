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

	//m_vecMenuItem.pushBack(pMenuItem);

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

	pMenuCloseBtn->setPosition(ccp(80, 80));
	pMenuCloseBtn->setTag(EBG_EXIT);

	// add a music play button
	MenuItemImage* pMenuMusicPlayBtn = nullptr;
	cocos2d::ccMenuCallback pMusicPlayCallBack = CC_CALLBACK_0(CSettingMenu::OnPlayGameBgMusicCallBack, this);
	CreatMenuItemByeImageCallback(SETTINGMENU_MUSCI_NORMAL,
								  SETTINGMENU_MUSIC_SELECTED,
								  SETTINGMENU_MUSIC_SELECTED,
								  pMusicPlayCallBack,
								  &pMenuMusicPlayBtn
								  //Point(point.x/2 - 50, point.y/2 - 50)
								 /*Size::ZERO*/
								  );


	
	if (pMenuMusicPlayBtn == nullptr)
		return;

	pMenuMusicPlayBtn->setPosition(ccp(100,100));
	pMenuMusicPlayBtn->setTag(EBG_Music);

	// music up
	m_vecMenuItem.pushBack(pMenuMusicPlayBtn);
	m_vecMenuItem.pushBack(pMenuCloseBtn);

	//////////////////////////////////////////////////////////////////////////////
	if (m_vecMenuItem.empty()){
		return;
	}

	for (int i = 0 ; i < m_vecMenuItem.size(); ++i)
	{
		//m_vecMenuItem.at(i)->setPosition(point.x / 2 - i * 5, point.y / 2 - i * 5);
	}

	m_pMainMenu = Menu::createWithArray(m_vecMenuItem);
	m_pMainMenu->alignItemsVertically();

	int index = 0;
	for( const auto &child : m_pMainMenu->getChildren() )
	{
		auto dstPostion = child->getPosition();
		float dtoffset = oWinSize.width/3;

		child->setPosition(Vec2(dstPostion.x + dtoffset, dstPostion.y - 50));
		++index;
	}

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

	CreatePopupModule();
	//auto pBg = Sprite::create(POPPLAYER_BG);
	//if (pBg == NULL)
	//{
	//	return;
	//}

	//Point dstPoint = Director::getInstance()->getWinSize();
	//pBg->setPosition(Vec2(dstPoint.x/2, dstPoint.y/2));
	//

	//float dtCloseLoc_x = pBg->getContentSize().width-10.0f;
	//float dtCloseLoc_y = pBg->getContentSize().height-10.0f;

	//// close button
	//auto pCloseSprite = Scale9Sprite::create(POPPLAYER_CLOSE);
	//if (pCloseSprite == NULL)
	//{
	//	return;
	//}
	//auto pCloseBtn = ControlButton::create(pCloseSprite);
	//pCloseBtn->addTargetWithActionForControlEvents(this, 
	//											   cccontrol_selector(CSettingMenu::OnEixtSettingMenuCallBack), 
	//											   Control::EventType::TOUCH_DOWN
	//											   );

	//pCloseBtn->setPosition(ccp(dtCloseLoc_x, dtCloseLoc_y));
	//
	//pBg->addChild(pCloseBtn);
	//pBg->setTag(EBackGround);
	//pBg->setContentSize(Size(362.0f, 147.0f));
	//this->addChild(pBg);

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

	this->setContentSize(Size(362.0f, 187.0f));
	
	m_pMainMenu->setContentSize(Size(362.0f, 147.0f));
	
	this->addChild(m_pMainMenu);

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
	m_VecOldPoint = Director::getInstance()->convertToGL(touch->getLocationInView());

	return true;
}

void CSettingMenu::onTouchMoved(Touch *touch, Event *unused_event)
{
	Trace_In("%s is starting -------------------------", __FUNCTION__);
	//auto  vecOldPoint = touch->getPreviousLocationInView();
	auto  vecNewPoint = Director::getInstance()->convertToGL(touch->getLocationInView());

	setPosition(vecNewPoint.x - m_VecOldPoint.x, vecNewPoint.y - m_VecOldPoint.y);
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

		Node* pSelectedNode = Sprite::create(SETTINGMENU_MUSIC_SELECTED);
		if (pSelectedNode == NULL)
		{
			return;
		}

		( static_cast<MenuItemImage*>( m_pMainMenu->getChildByTag(EBG_Music) ) )->setSelectedImage(pSelectedNode);
	}
	else
	{
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		m_isPlayMusic = true;

		Node* pNormalNode = Sprite::create(SETTINGMENU_MUSCI_NORMAL);
		if (pNormalNode == NULL)
		{
			return;
		}

		( static_cast< MenuItemImage* >( m_pMainMenu->getChildByTag(EBG_Music) ) )->setSelectedImage(pNormalNode);
	}
}
