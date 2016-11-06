#include "ExchangeSeaBarPopup.h"
#include "ConstUtil.h"

CExchangeSeaBarPopup::CExchangeSeaBarPopup() : m_pPopPlayer(NULL)
{

}

CExchangeSeaBarPopup::~CExchangeSeaBarPopup()
{
	
}

void CExchangeSeaBarPopup::OnEnter()
{
	CSeaBarPopBase::OnEnter();
	CCLOG("%s is start, file is %s, %d", __FUNCTION__, __FILE__, __LINE__);

	// Create seabar exchange popplayer module
	CreatePopupModule();

	//
	setPopContext("么么哒~", "你确定要置换这栋海洋馆吗？");
	if (m_pPopPlayer)
		addChild(m_pPopPlayer);
}

void CExchangeSeaBarPopup::onExit()
{
	Layer::onExit();

	CCLOG("%s is start, file is %s, %d", __FUNCTION__, __FILE__);
}

void CExchangeSeaBarPopup::setPopContext(const char * szTitle, const char* szContext)
{
	CCLOG("%s is start, file is %s, %d", __FUNCTION__, __FILE__);
	auto pLabelContext = LabelTTF::create(szContext, EFontType_MarkerFelt, 20.0f);
	pLabelContext->setFontFillColor(Color3B::RED);

	if (pLabelContext == NULL)
	{
		return;
	}

	auto pMenuItemContext = MenuItemLabel::create(pLabelContext);
	Point dstPoint = this->getChildByTag(EBackGround)->getContentSize();
	pMenuItemContext->setPosition(ccp(dstPoint.x / 2, dstPoint.y / 2));



	m_pPopPlayer = Menu::create(pMenuItemContext, NULL);

	auto pLabelTitle = LabelTTF::create(szTitle, EFontType_MarkerFelt, 15.0f);
	if (pLabelTitle == NULL)
	{
		return;
	}

	pLabelTitle->setFontFillColor(Color3B::BLACK);
	pLabelTitle->setPosition(dstPoint.x / 2, dstPoint.y);
	this->getChildByTag(EBackGround)->addChild(pLabelTitle);
}

CExchangeSeaBarPopup* CExchangeSeaBarPopup::CreateExchangeSeaBarPopup()
{
	CExchangeSeaBarPopup* pExchangeInstance = new CExchangeSeaBarPopup();
	if (pExchangeInstance == nullptr)
	{
		CC_SAFE_DELETE(pExchangeInstance);
		return nullptr;
	}

	pExchangeInstance->OnEnter();

	pExchangeInstance->autorelease();
	return pExchangeInstance;
}

void CExchangeSeaBarPopup::OnEixtSettingMenuCallBack(Object* pSender, Control::EventType event)
{
	CCLOG("%s is start, file is %s", __FUNCTION__, __FILE__);
	this->removeFromParent();
}
