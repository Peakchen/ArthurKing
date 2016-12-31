/************************************************************************/
/* 
	aurthor:	StefanChen
	version:	1.0
	date:		20161231
	brief:		让对手轮空一次

*/
/************************************************************************/

#ifndef  __TURN_FREE_FACADE__
#define  __TURN_FREE_FACADE__

#include "ActionSpiltHandler.h"

class CTurn_FreeFacade :
	public	IEntityRulePropHandler
{
public:
	CTurn_FreeFacade();
	~CTurn_FreeFacade();

	/////////////////////////////IEntityRulePropHandler////////////////////////////

	virtual void OnEntityRulePropChange(int iPDBID, char* szContext);


private:

};

#endif