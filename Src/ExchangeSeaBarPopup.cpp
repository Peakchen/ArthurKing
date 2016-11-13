#include "ExchangeSeaBarPopup.h"
#include "ConstUtil.h"
#include "AIPersonMessageMacro.h"
#include "ResCreator.h"

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
	setPopContext("Dear~", "Are you sure？"); 
	if (m_pPopPlayer)
		addChild(m_pPopPlayer);
}

void CExchangeSeaBarPopup::onExit()
{
	Layer::onExit();

	CCLOG("%s is start, file is %s, %d", __FUNCTION__, __FILE__);
	g_ResCreator.GetPersonMessageInstance()->FireMessage(DIALOG_CLOSE_ACTION, "Close dialog.");
}

void CExchangeSeaBarPopup::setPopContext(const char * szTitle, const char* szContext)
{
	CCLOG("%s is start, file is %s, %d", __FUNCTION__, __FILE__);
	auto pLabelContext = LabelTTF::create(szContext, EFontType_MarkerFelt, 15.0f);
	pLabelContext->setFontFillColor(Color3B::RED);

	if (pLabelContext == NULL)
	{
		return;
	}

	auto pMenuItemContext = MenuItemLabel::create(pLabelContext);
	Point dstPoint = this->getChildByTag(EBackGround)->getContentSize();
	pMenuItemContext->setPosition(ccp(dstPoint.x / 2 - 100, dstPoint.y / 2));

	MenuItemLabel* pMenuCancleItem = nullptr;
	cocos2d::ccMenuCallback pCancle_CallBack = CC_CALLBACK_0(CExchangeSeaBarPopup::OnCancleExchange_Cancle_Action, this);
	CreateMenuItemByfontCallback("No",
								 pCancle_CallBack,
								 15,
								 EFontType_MarkerFelt,
								 &pMenuCancleItem
								 /* Point(oWinSize.width, oWinSize.height - 50),
								 Size::ZERO*/
								 );

	MenuItemLabel* pMenuOkItem = nullptr;
	cocos2d::ccMenuCallback pOK_CallBack = CC_CALLBACK_0(CExchangeSeaBarPopup::OnCancleExchange_OK_Action, this);
	CreateMenuItemByfontCallback("OK",
								 pOK_CallBack,
								 15,
								 EFontType_MarkerFelt,
								 &pMenuOkItem
								 /* Point(oWinSize.width, oWinSize.height - 50),
								 Size::ZERO*/
								 );


	m_pPopPlayer = Menu::create(pMenuItemContext, pMenuCancleItem, pMenuOkItem, NULL);

	m_pPopPlayer->alignItemsVerticallyWithPadding(5.0f);
	Size oWinSize = this->getChildByTag(EBackGround)->getContentSize();
	int index = 0;
	for (const auto &child : m_pPopPlayer->getChildren())
	{
		auto dstPostion = child->getPosition();
		float dtoffset = oWinSize.width / 5;

		child->setPosition(Vec2(dstPoint.x + dtoffset, dstPoint.y - 10.0f));
		++index;
	}

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

void CExchangeSeaBarPopup::OnCancleExchange_Cancle_Action()
{
	CCLOG("%s is start, file is %s", __FUNCTION__, __FILE__);
	this->removeFromParent();
}

void CExchangeSeaBarPopup::OnCancleExchange_OK_Action()
{
	CCLOG("%s is start, file is %s --------------------- ok", __FUNCTION__, __FILE__);
	
	this->removeFromParent();
}
