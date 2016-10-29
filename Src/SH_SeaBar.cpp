#include "SH_SeaBar.h"
#include "SeaBarFacade.h"
#include "ExchangeSeaBarPopup.h"

CSH_SeaBar::CSH_SeaBar()
{

}

CSH_SeaBar::~CSH_SeaBar()
{
}

char* CSH_SeaBar::GetActionName()
{
	return "sea";
}

void CSH_SeaBar::CheckCurrentAction(const TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pActor, TActorInstanceMap* pOtherActors)
{
	CCLOG("%s in %s is start --------- ", __FUNCTION__, __FILE__);

	ESeaBarAttach iflag = ESeaBar_None;
	bool bCanBuy = g_SeaBarFacade.GetBuySeaBarInstance()->CheckCanExchangeSeaBar(pTileLayerPeperty->iSeaBarIndex, iflag, pActor);
	if (ESeaBar_Error == iflag)
	{ 
		CCLOG("%s has a %s function is failed.... ", __FILE__, __FUNCTION__);
		return;
	}
	else if (ESeaBar_None == iflag)
	{
		// no owner, then pop up 
		if (CExchangeSeaBarPopup::CreateExchangeSeaBarPopup() == nullptr)
		{
			CCLOG("exchange seabar is failed....");
		}

	}
	else if (ESeaBar_other == iflag)
	{
		// has owner, then give tip

	}
	else if (ESeaBar_self == iflag)
	{
		// the owner of seabar is myself, do nothing 
		return;
	}

}
