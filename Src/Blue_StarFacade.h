
/************************************************************************/
/* 
	aurthor:	StefanChen
	date:		20161231
	version:	1.0
	brief:		遇到蓝星，之后无论购买什么土地都免费，踩到分数加倍，两次内有效

*/
/************************************************************************/

#ifndef __BLUE_STAR_FACADE__
#define __BLUE_STAR_FACADE__

#include "ActionSpiltHandler.h"

class CBlue_StarFacade :
	public	IEntityRulePropHandler
{
public:
	CBlue_StarFacade();
	~CBlue_StarFacade();

	///////////////////////////////IEntityRulePropHandler/////////////////////////////

	virtual	void	OnEntityRulePropChange(int iPDBID, char* szContext);

private:

};

#endif