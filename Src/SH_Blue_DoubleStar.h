
/************************************************************************/
/* 
	@aurthor:	StefanChen
	@date:		20161216
	@version:	1.0
	@brief:		��Ϣ������ - ��˫���淨
				��˫�ǣ��ȵ��Է��������ѣ�����������Ч

				���ǵ������SeaBar����Ҫ��SeaBar��������߼���ǰ20161216������

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

