
/************************************************************************/
/* 

*/
/************************************************************************/
#ifndef __TILEBASE__
#define __TILEBASE__

#include "ActionSpiltHandler.h"


class CTileBase :public IArthurActionSpiltHandler
{
public:

	virtual char* GetActionName(){ return ""; }

	virtual void CheckCurrentAction(TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorTileLayerInfoMap* pOtherActors){}


protected:

private:

};

typedef map<string, CTileBase*> TSPLITHANDLERMAP;

#endif