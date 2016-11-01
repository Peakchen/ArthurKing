
/************************************************************************/
/* 

*/
/************************************************************************/

#include "ActionSpiltHandler.h"
#include "TileBase.h"

class CSH_SeaBar: public CTileBase
{
public:
	CSH_SeaBar();
	~CSH_SeaBar();

	virtual char* GetActionName();

	virtual void CheckCurrentAction(const TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorInstanceMap* pOtherActors);


private:

};
