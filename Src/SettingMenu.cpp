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

	auto pMenuItem = nullptr;
	CreateMenuItemByfontCallback("Exit", 
								CC_CALLBACK_1(CSettingMenu::OnCancleSettingMenuAction, this), 
								20, 
								EFontType_MarkerFelt, 
								pMenuItem
								);

	assert(pMenuItem != nullptr);
	m_vecMenuItem.pushBack(pMenuItem);


	//////////////////////////////////////////////////////////////////////////////
	assert(m_vecMenuItem.empty());

	m_pMainMenu = Menu::createWithArray(m_vecMenuItem);

	for each ( const auto &child in m_pMainMenu->getChildren() )
	{

	}
	m_pMainMenu->setPosition(point);
	m_pMainMenu->alignItemsVerticallyWithPadding(20.0f);

	m_pMainMenu->setOnEnterCallback(CSettingMenu::OnEnterSettingMenuCallBack);
	m_pMainMenu->setOnExitCallback(CSettingMenu::OnEixtSettingMenuCallBack);

}

void CSettingMenu::Create()
{
	//

	//
	Size oSize = Director::getInstance()->getVisibleSize();
	InitSettingMenu(Point(oSize.height/2, oSize.width/2));
}

void CSettingMenu::OnEnterSettingMenuCallBack()
{
	auto 
	Trace_In("%s is start...", __FUNCTION__);
}

void CSettingMenu::OnEixtSettingMenuCallBack()
{
	Trace_In("%s is start...", __FUNCTION__);
}

void CSettingMenu::OnCancleSettingMenuAction()
{
	Trace_In("%s is start...", __FUNCTION__);
}
