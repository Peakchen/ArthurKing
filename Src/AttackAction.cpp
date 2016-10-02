#include "AttackAction.h"
#include "extensions/cocos-ext.h"
#include "MacroDefine.h"

USING_NS_CC;
USING_NS_CC_EXT;

CAttackAction::CAttackAction()
{
}


CAttackAction::~CAttackAction()
{
}

bool CAttackAction::CreateAttackButton(const char* strName_Png, unsigned int unFontOpacity, const char* strButton_Title /*= "0"*/)
{
	Scale9Sprite* pBtn = Scale9Sprite::create(Attack_Button);
	if (!pBtn)
	{
		return false;
	}
	
	int nPngH = static_cast<int>(pBtn->getContentSize().height);
	int nPngW = static_cast<int>(pBtn->getContentSize().width);
	
	CC_SAFE_DELETE(pBtn);

	CCRect oRect = CCRectMake(0, 0, nPngW, nPngH);
	CCRect oReSetRect = CCRectMake(1, 1, 1, 1);

	CCLabelTTF* pLabelTitle = CCLabelTTF::create(strButton_Title, "Mark Felt", nPngH - 10);
	if (!pLabelTitle)
	{
		return false;
	}
	pLabelTitle->setOpacity(unFontOpacity);
	
	Scale9Sprite* pNormalSprite = Scale9Sprite::create(strName_Png, oRect, oReSetRect);
	if (!pNormalSprite)
	{
		return false;
	}

	m_pSprite = Sprite::create(strName_Png);
	this->addChild(m_pSprite);

	// °ó¶¨ÊÂ¼þ
	BindButtonEvent();
	m_pSprite = Sprite::create();
}

void CAttackAction::TouchDownAction(cocos2d::CCObject* pSender, cocos2d::CCEvent oEven)
{

}

void CAttackAction::BindButtonEvent()
{

}
