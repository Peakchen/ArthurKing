/************************************************************************/
/* 
	author:	StefanChen
	date:	20161213
	version:	1.0
	brief:	�ȵ����ף�ԭ�����ˣ��ֿ�����
*/
/************************************************************************/

#include "TileBase.h"

class CSH_StopThreeTimes:
	public CTileBase
{
public:
	CSH_StopThreeTimes();
	~CSH_StopThreeTimes();

	/////////////////////////CTileBase//////////////////////////////////////
	virtual char* GetActionName();

	virtual void CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors);


private:
	void	__OnStopThreeTimesAction(CActorBase* pSelfActor);
};

