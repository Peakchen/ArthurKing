
/************************************************************************/
/* 
	aurthor:	StefanChen
	date:		20161231
	version:	1.0
	brief:		�������ǣ�֮�����۹���ʲô���ض���ѣ��ȵ������ӱ�����������Ч

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