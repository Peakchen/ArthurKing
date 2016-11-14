#include "SH_SeaBar.h"
#include "SeaBarFacade.h"
#include "ExchangeSeaBarPopup.h"
#include "ResCreator.h"

CSH_SeaBar::CSH_SeaBar()
{
	m_pActor = nullptr;

	__InitEventMsg();
}

CSH_SeaBar::~CSH_SeaBar()
{
}

char* CSH_SeaBar::GetActionName()
{
	return "sea";
}

void CSH_SeaBar::CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pActor, TActorInstanceMap* pOtherActors)
{
	CCLOG("%s in %s is start --------- ", __FUNCTION__, __FILE__);
	__InitSeaBarOperationData(pTileLayerPeperty, pActor);
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
		g_ResCreator.GetPersonMessageInstance()->FireMessage(SH_SEABAR_EXCHANGE_ACTION, "SH SEABAR exchange action");
	}
	else if (ESeaBar_other == iflag)
	{
		// has owner, then give tip
		g_SeaBarFacade.GetGiveTipInstance()->DoGiveTipToOther(m_oTileLayerPeperty.iSeaBarIndex, m_pActor);
	}
	else if (ESeaBar_self == iflag)
	{
		// the owner of seabar is myself, do nothing 
		g_ResCreator.GetPersonMessageInstance()->FireMessage(SH_SEABAR_SELL_ACTION, "SH SEABAR sell action");
		return;
	}
}

void CSH_SeaBar::OnExecMessageHandle(GWORD nMsgID, const char* szDesc)
{
	switch (nMsgID)
	{
		case SEABAR_EXCHANGE:
			{
				CCLOG("");
				g_SeaBarFacade.GetBuySeaBarInstance()->DoExchangeSeaBar(m_oTileLayerPeperty.iSeaBarIndex, m_pActor);
			}
			break;
		case SEABAR_GIVETIP:
			{
				g_SeaBarFacade.GetGiveTipInstance()->DoGiveTipToOther(m_oTileLayerPeperty.iSeaBarIndex, m_pActor);
			}
			break;
		default:
			break;
	}
}

void CSH_SeaBar::__InitEventMsg()
{
	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(SEABAR_EXCHANGE, this, "seabar exchange");
	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(SEABAR_GIVETIP, this, "seabar give tip");
}

void CSH_SeaBar::__InitSeaBarOperationData(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pActor)
{
	//memcpy(&m_oTileLayerPeperty, pTileLayerPeperty, sizeof(TTileLayerGridProperty));
	m_oTileLayerPeperty.iScoreMult = pTileLayerPeperty->iScoreMult;
	m_oTileLayerPeperty.iScoreValue = pTileLayerPeperty->iScoreValue;
	m_oTileLayerPeperty.iSeaBarIndex = pTileLayerPeperty->iSeaBarIndex;
	m_oTileLayerPeperty.iSeaBarPrice = pTileLayerPeperty->iSeaBarPrice;
	m_oTileLayerPeperty.iSeaBarTip = pTileLayerPeperty->iSeaBarTip;
	m_oTileLayerPeperty.iStopTimes = pTileLayerPeperty->iStopTimes;
	m_oTileLayerPeperty.iTimes = pTileLayerPeperty->iTimes;
	m_oTileLayerPeperty.szName = pTileLayerPeperty->szName;
	m_oTileLayerPeperty.szType = pTileLayerPeperty->szType;

	m_pActor = pActor;
}

