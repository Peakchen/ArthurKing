/************************************************************************/
/*
	@aurthor:	StefanChen
	@date:		20161216
	@version:	1.0
	@brief:		��Ϣ������ -
	������һ����ǰ����Ľ������߳ͷ�

*/
/************************************************************************/

#include "TileBase.h"

class CSH_OnceAgain:
	public CTileBase
{
public:
	CSH_OnceAgain();
	~CSH_OnceAgain();


	virtual char * GetActionName();

	virtual void CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors);


private:
	void	__OnEvent_OnceAgain(CActorBase* pSelfActor);
};

