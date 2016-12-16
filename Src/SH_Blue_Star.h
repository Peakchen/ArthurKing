/************************************************************************/
/* 
	@aurthor:	StefanChen
	@date:		20161216
	@version:	1.0
	@brief:		消息处理器 - 
	遇到蓝星，之后无论购买什么土地都免费，踩到分数加倍，两次内有效

*/
/************************************************************************/

#include "TileBase.h"

class CSH_Blue_Star:
	public CTileBase
{
public:
	CSH_Blue_Star();
	~CSH_Blue_Star();

	virtual char* GetActionName();

	virtual void CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors);


private:
	void	__OnEvent_Blue_Star(CActorBase* pSelfActor);
};

