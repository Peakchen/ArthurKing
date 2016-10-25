#include "SellSeaBarPopup.h"
#include "ConstUtil.h"


CSellSeaBarPopup::CSellSeaBarPopup()
{
}


CSellSeaBarPopup::~CSellSeaBarPopup()
{
}

void CSellSeaBarPopup::OnEnter()
{
	CSeaBarPopBase::OnEnter();
	CCLOG("%s is start, file is %s, %d", __FUNCTION__, __FILE__, __LINE__);

	// Create seabar exchange popplayer module
	CreatePopupModule();

	//
	setPopContext("亲爱的，么么哒~", "你确定要出售这栋海洋馆吗？");
	if (m_pPopPlayer)
		addChild(m_pPopPlayer);
}

void CSellSeaBarPopup::onExit()
{
	CSeaBarPopBase::onExit();

	this->removeFromParent();
	CCLOG("%s is start, file is %s, %d", __FUNCTION__, __FILE__);
}

void CSellSeaBarPopup::setPopContext(const char * szTitle, const char* szContext)
{
	CCLOG("%s is start, file is %s, %d", __FUNCTION__, __FILE__);
	auto pLabelContext = LabelTTF::create(szContext, EFontType_MarkerFelt, 20.0f);
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

	pLabelTitle->setPosition(dstPoint.x / 2, dstPoint.y);
	this->getChildByTag(EBackGround)->addChild(pLabelTitle);
}
