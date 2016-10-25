#include "PopupBase.h"
#include "ConstUtil.h"


CPopupBase::CPopupBase()
{
}


CPopupBase::~CPopupBase()
{
}

void CPopupBase::CreateMenuItemByfontCallback(const char* szBtnName, ccMenuCallback callback, int oFontSize, const char* szFontName, MenuItemLabel** pMenuItem, Point oPoint /*= Point::ZERO*/, Size oSize /*= Size::ZERO */)
{
	MenuItemFont*	pFontMenuItem = MenuItemFont::create(szBtnName, callback);
	assert(pFontMenuItem != nullptr);

	pFontMenuItem->setPosition(oPoint);
	pFontMenuItem->setFontSizeObj(oFontSize);
	pFontMenuItem->setFontName(szFontName);
	//pFontMenuItem->setContentSize(oSize);
	*pMenuItem = pFontMenuItem;
}

void CPopupBase::CreateMenuItemByLabelCallBack(const char* szBtnName, const char* szFontType, ccMenuCallback callback, MenuItem** pMenuItem, Point point /*= Point::ZERO*/, Size oSize /*= Size::ZERO */)
{
	auto	pLabel = Label::createWithBMFont(szFontType, szBtnName);
	assert(pLabel != nullptr);

	auto	pLabelMenuItem = MenuItemLabel::create(pLabel, callback);
	assert(pLabelMenuItem != nullptr);

	pLabelMenuItem->setPosition(point);
	pLabelMenuItem->setOpacity(Opacity_Normal);
	//pLabelMenuItem->setContentSize(oSize);
	*pMenuItem = pLabelMenuItem;
}

void CPopupBase::CreatMenuItemByeImageCallback(const char* szNormalpic, const char* szSelectpic, const char* szDisablepic, ccMenuCallback callback, MenuItemImage** pMenuItem, Point point /*= Point::ZERO*/, Size oSize /*= Size::ZERO*/)
{
	auto	pMenuImage = MenuItemImage::create(szNormalpic, szSelectpic, szDisablepic, callback);
	assert(pMenuImage != nullptr);

	pMenuImage->setPosition(point);
	pMenuImage->setOpacity(Opacity_Normal);
	//pMenuImage->setContentSize(oSize);
	*pMenuItem = pMenuImage;
}

void CPopupBase::CreateMenuItemBySpriteCallBack(const char* szNormalpic, const char* szSelectpic, const char* szdisablepic, ccMenuCallback callback, MenuItem** pMenuItem, Point point /*= Point::ZERO*/, Size oSize /*= Size::ZERO*/)
{
	auto	pNormalImage = Sprite::create(szNormalpic, Rect(0, 23 * 2, 115, 23));
	assert(pNormalImage != nullptr);
	auto	pSelectImage = Sprite::create(szSelectpic, Rect(0, 23 * 1, 115, 23));
	assert(pSelectImage != nullptr);
	auto	pDisableImage = Sprite::create(szdisablepic, Rect(0, 23 * 0, 115, 23));
	assert(pDisableImage != nullptr);
	auto	pSpriteMenu = MenuItemSprite::create(pNormalImage, pSelectImage, pDisableImage, callback);
	assert(pSpriteMenu != nullptr);

	pSpriteMenu->setPosition(point);
	//pSpriteMenu->setContentSize(oSize);
	*pMenuItem = pSpriteMenu;
}

void CPopupBase::OnEixtSettingMenuCallBack(Object* pSender, Control::EventType event)
{
	this->removeFromParent();
}

void CPopupBase::CreatePopupModule()
{
	auto pBg = Sprite::create(POPPLAYER_BG);
	if (pBg == NULL)
	{
		return;
	}

	Point dstPoint = Director::getInstance()->getWinSize();
	pBg->setPosition(Vec2(dstPoint.x / 2, dstPoint.y / 2));


	float dtCloseLoc_x = pBg->getContentSize().width - 10.0f;
	float dtCloseLoc_y = pBg->getContentSize().height - 10.0f;

	// close button
	auto pCloseSprite = Scale9Sprite::create(POPPLAYER_CLOSE);
	if (pCloseSprite == NULL)
	{
		return;
	}
	auto pCloseBtn = ControlButton::create(pCloseSprite);
	pCloseBtn->addTargetWithActionForControlEvents(this,
												   cccontrol_selector(CPopupBase::OnEixtSettingMenuCallBack),
												   Control::EventType::TOUCH_DOWN
												   );

	pCloseBtn->setPosition(ccp(dtCloseLoc_x - 10.0f, dtCloseLoc_y));
	pBg->setTag(EBackGround);
	pBg->addChild(pCloseBtn);
	pBg->setContentSize(Size(362.0f, 147.0f));
	this->addChild(pBg);
}
