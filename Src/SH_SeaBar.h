
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

	virtual void CheckCurrentAction(const TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorInstanceMap* pOtherActors);

	///////////////////////IAIPersonMessageSink////////////////////////////////
	virtual void OnExecMessageHandle(GWORD nMsgID, const char* szDesc);
private:
	TTileLayerGridProperty *m_pTileLayerPeperty;
	CActorBase* m_pActor;

private:
	void __InitEventMsg();
};
