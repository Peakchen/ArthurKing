/************************************************************************/
/*
	@aurthor:	StefanChen
	@date:		20161216
	@version:	1.0
	@brief:		消息处理器 -
	红双星，踩到对方土地用付费加倍，走三次内有效


*/
/************************************************************************/

#include "TileBase.h"

class CSH_Red_DoubleStar:
	public CTileBase
{
public:
	CSH_Red_DoubleStar();
	~CSH_Red_DoubleStar();


	virtual char * GetActionName();

	virtual void CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors);


private:

	void	__OnEvent_Red_DoubleStar(CActorBase* pSelfActor);

};
