
/************************************************************************/
/* 
	aurthor:	StefanChen
	date:		20161231
	version:	1.0
	brief:		��ѽ���ȿ��ˣ�ԭ����Ϣһ��	��Ϣ�ڲ�

*/
/************************************************************************/

#include "ActionSpiltHandler.h"

#ifndef		__FOOT_BLUE_FACADE__
#define		__FOOT_BLUE_FACADE__

class CFoot_BlueFacade :
	public IEntityRulePropHandler
{
public:
	CFoot_BlueFacade();
	~CFoot_BlueFacade();

	/////////////////////////IEntityRulePropHandler///////////////////////////////

	virtual	void OnEntityRulePropChange(int iPDBID, char* szContext);

private:

};


#endif