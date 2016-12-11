/************************************************************************/
/*
arthur:		StefanChen
date:		20161127
version:	1.0
brief:		make others action is invalid
*/
/************************************************************************/

#include "TileBase.h"
#include "PersonMessageEventHandle.h"

class CSH_OtherActionInvalid:
	public	CTileBase
{
public:
	CSH_OtherActionInvalid();
	~CSH_OtherActionInvalid();

	/////////////////////////CTileBase//////////////////////////////////////
	virtual char* GetActionName();

	virtual void CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors);


private:
	void	__AllowOpponentBye(TActorTileLayerInfoMap* pOtherActors);
};
