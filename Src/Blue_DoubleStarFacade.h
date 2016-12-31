
/************************************************************************/
/* 
	aurthor:	StefanChen
	date:		20161231
	version:	1.0
	brief:		蓝双星，踩到对方土地免费，走三次内有效

*/
/************************************************************************/

#include "ActionSpiltHandler.h"

class CBlue_DoubleStarFacade :
	public	IEntityRulePropHandler
{
public:
	CBlue_DoubleStarFacade();
	~CBlue_DoubleStarFacade();

	//////////////////////////////////IEntityRulePropHandler//////////////////////////////////////////

	virtual void OnEntityRulePropChange(int iPDBID, char* szContext);

private:

};

