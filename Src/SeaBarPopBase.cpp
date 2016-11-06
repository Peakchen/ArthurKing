#include "SeaBarPopBase.h"
#include "ConstUtil.h"


CSeaBarPopBase::CSeaBarPopBase()
{
}


CSeaBarPopBase::~CSeaBarPopBase()
{
}

void CSeaBarPopBase::setPopContext(const char * szTitle, const char* szContext)
{
	CCLOG("%s is start, file is %s", __FUNCTION__, __FILE__);
}

void CSeaBarPopBase::OnEnter()
{
	CPopupBase::onEnter();

	CCLOG("%s is start, file is %s", __FUNCTION__, __FILE__);

	// touch event
	this->setTouchEnabled(true);

	EventDispatcher* pEventDispatcher = Director::getInstance()->getEventDispatcher();
	if (pEventDispatcher != NULL)
	{
		auto pTouchOneByOne = EventListenerTouchOneByOne::create();
		if (pTouchOneByOne)
		{
			pTouchOneByOne->onTouchBegan = CC_CALLBACK_2(CSeaBarPopBase::onTouchBegan, this);
			pTouchOneByOne->onTouchMoved = CC_CALLBACK_2(CSeaBarPopBase::onTouchMoved, this);
			pTouchOneByOne->onTouchEnded = CC_CALLBACK_2(CSeaBarPopBase::onTouchEnded, this);
			pTouchOneByOne->onTouchCancelled = CC_CALLBACK_2(CSeaBarPopBase::onTouchCancelled, this);
			pEventDispatcher->addEventListenerWithSceneGraphPriority(pTouchOneByOne, this);

			pTouchOneByOne->setSwallowTouches(true);
		}
	}

	// build pop
	//CreatePopupModule();

	// build context

	//setPopContext("", "");
	// build ...
}

void CSeaBarPopBase::onExit()
{
	//CPopupBase::onExit();

	//this->removeFromParent();

	CCLOG("%s is start, file is %s", __FUNCTION__, __FILE__);
}

bool CSeaBarPopBase::onTouchBegan(Touch *touch, Event *unused_event)
{
	CCLOG("%s is start, file is %s", __FUNCTION__, __FILE__);
	return true;
}

void CSeaBarPopBase::onTouchMoved(Touch *touch, Event *unused_event)
{
	CCLOG("%s is start, file is %s", __FUNCTION__, __FILE__);
}

void CSeaBarPopBase::onTouchEnded(Touch *touch, Event *unused_event)
{
	CCLOG("%s is start, file is %s", __FUNCTION__, __FILE__);
}

void CSeaBarPopBase::onTouchCancelled(Touch *touch, Event *unused_event)
{
	CCLOG("%s is start, file is %s", __FUNCTION__, __FILE__);
}

void CSeaBarPopBase::OnEixtSettingMenuCallBack(Object* pSender, Control::EventType event)
{
	CCLOG("%s is start, file is %s", __FUNCTION__, __FILE__);
}
