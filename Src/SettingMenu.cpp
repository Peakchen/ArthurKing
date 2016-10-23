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

	MenuItemLabel* pMenuItem = nullptr;
	cocos2d::ccMenuCallback pCallBack = CC_CALLBACK_0(CSettingMenu::OnCancleSettingMenuAction, this);
	CreateMenuItemByfontCallback("Exit",
								 pCallBack,
								 20,
								 EFontType_MarkerFelt,
								 &pMenuItem,
								 Point::ZERO,
								 Size::ZERO
								 );

	if (pMenuItem == nullptr)
		return;

	m_vecMenuItem.pushBack(pMenuItem);


	//////////////////////////////////////////////////////////////////////////////
	if (m_vecMenuItem.empty()){
		return;
	}

	m_pMainMenu = Menu::createWithArray(m_vecMenuItem);

	auto oWinSize = m_pMainMenu->getContentSize();
	int index = 0;
	for each ( const auto &child in m_pMainMenu->getChildren() )
	{
		auto dstPostion = child->getPosition();
		int ioffset = oWinSize.width/2 + 10;
		if (index % 2 == 0)
			ioffset = -ioffset;

		child->setPosition(Vec2(dstPostion.x + ioffset, dstPostion.y));
		++index;
	}

	//m_pMainMenu->addChild(Sprite::create(SETTING_MENU_BG));
	m_pMainMenu->setPosition(point);
	m_pMainMenu->alignItemsVerticallyWithPadding(20.0f);
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
	
	Size oSize = Director::getInstance()->getVisibleSize();
	InitSettingMenu(Point(oSize.height / 2, oSize.width / 2));
	addChild(m_pMainMenu);
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
	addChild(pBg);

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
