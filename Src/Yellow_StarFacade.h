
/************************************************************************/
/* 
	aurthor:	StefanChen
	date:		20161230
	version��	1.0
	brief:		�������ǣ�֮���ܹ������أ��ȵ�������Ч��������

*/
/************************************************************************/

#ifndef __YELLOW_STAR_FACADE__
#define __YELLOW_STAR_FACADE__

#include "ActionSpiltHandler.h"

class CYellowStarFacade
	:	public IEntityRulePropHandler
{
public:
	CYellowStarFacade();
	~CYellowStarFacade();

	//////////////////////////IEntityRulePropHandler///////////////////////////

	virtual void OnEntityRulePropChange(int iPDBID, char* szContext);

private:

};



#endif