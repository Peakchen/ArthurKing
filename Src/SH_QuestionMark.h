
/************************************************************************/
/* 
	aurthor:	StefanChen
	date:		20161211
	version:	1.0
	brief:		�ʺű�Ǹ��� ��Ϣ����
*/
/************************************************************************/

#include "TileBase.h"

class CSH_QuestionMark:
	public	CTileBase
{
public:
	CSH_QuestionMark();
	~CSH_QuestionMark();

	/////////////////////////CTileBase//////////////////////////////////////
	virtual char* GetActionName();

	virtual void CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors);

private:

	void	__DealWithRandomAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor );
private:

};
