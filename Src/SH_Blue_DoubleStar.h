
/************************************************************************/
/* 
	@aurthor:	StefanChen
	@date:		20161216
	@version:	1.0
	@brief:		消息处理器 - 蓝双星玩法
				蓝双星，踩到对方海洋馆免费，走三次内有效

				考虑到海洋馆SeaBar，需要在SeaBar处理相关逻辑当前20161216不处理

*/
/************************************************************************/

#include "TileBase.h"

class CSH_Blue_DoubleStar:
	public CTileBase
{
public:
	CSH_Blue_DoubleStar();
	~CSH_Blue_DoubleStar();

	virtual char* GetActionName();

	virtual void CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors);


private:

	void __OnEvent_Blue_DoubleStar(CActorBase* pSelfActor);
};

