
/************************************************************************/
/* 
	@aurthor:	StefanChen
	@date:		20161216
	@version:	1.0
	@brief:		��Ϣ������ -
	��ѽ���ȿ��ˣ�ԭ����Ϣһ��

*/
/************************************************************************/

#include "TileBase.h"

class CSH_Foot_Blue:
	public CTileBase
{
public:
	CSH_Foot_Blue();
	~CSH_Foot_Blue();

	
	virtual char * GetActionName();

	virtual void CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors);

private:
	void	__OnEvent_Foot_Blue(CActorBase* pSelfActor);
};

