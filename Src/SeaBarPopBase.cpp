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

	// build pop
	//CreatePopupModule();

	// build context

	//setPopContext("", "");
	// build ...
}

void CSeaBarPopBase::onExit()
{
	CPopupBase::onExit();

	CCLOG("%s is start, file is %s", __FUNCTION__, __FILE__);
}
