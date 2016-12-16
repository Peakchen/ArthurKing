/************************************************************************/
/*
	@aurthor:	StefanChen
	@date:		20161216
	@version:	1.0
	@brief:		消息处理器 -
	遇到火星，之后不能购买土地，踩到分数无效，共两次

*/
/************************************************************************/

#include "TileBase.h"

class CSH_Yellow_Star:
	public CTileBase
{
public:
	CSH_Yellow_Star();
	~CSH_Yellow_Star();

	virtual char * GetActionName();

	virtual void CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors);


private:

	void	__OnEvent_Yellow_Star(CActorBase* pSelfActor);

};
