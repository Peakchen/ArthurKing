
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

	virtual void CheckCurrentAction(const TTileLayerGridProperty *pTileLayerPeperty, CActorBase* pSelfActor, TActorInstanceMap* pOtherActors){}


protected:

private:

};

typedef map<string, CTileBase*> TSPLITHANDLERMAP;

#endif