/************************************************************************/
/* 
	@aurthor:	StefanChen
	@date:		20161216
	@version:	1.0
	@brief:		��Ϣ������ - 
	�������ǣ�֮�����۹���ʲô���ض���ѣ��ȵ������ӱ�����������Ч

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

