
/************************************************************************/
/* 

*/
/************************************************************************/

#include "ActionSpiltHandler.h"
#include "TileBase.h"
#include "PersonMessageEventHandle.h"

class CSH_SeaBar: 
	public CTileBase,
	public IAIPersonMessageSink
{
public:
	CSH_SeaBar();
	~CSH_SeaBar();

	///////////////////////////CTileBase////////////////////////////////////////////
	virtual char* GetActionName();

	virtual void CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors);

	///////////////////////IAIPersonMessageSink////////////////////////////////
	virtual void OnExecMessageHandle(GWORD nMsgID, const char* szDesc);

	virtual void OnExecRuleEventMessage(int iPDBID, char* szContext, GWORD nMsgID, const char* szDesc){}

private:
	TTileLayerGridProperty m_oTileLayerPeperty;
	CActorBase* m_pActor;

private:
	void __InitEventMsg();

	void __InitSeaBarOperationData(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pActor);
};
