
/************************************************************************/
/* 
		@aurthor:	StefanChen
		@date:		20161229
		@version:	1.0
		@brief:		�ٴη��ƶ�������
*/
/************************************************************************/

#include "ActionSpiltHandler.h"

#ifndef __ONCE_AGAIN_FACADE__
#define __ONCE_AGAIN_FACADE__

class COnceAgainFacade	:
	public IEntityRulePropHandler
{
public:
	COnceAgainFacade();
	~COnceAgainFacade();
	
	//////////////////////////IEntityRulePropHandler//////////////////////////////////////
	virtual void	OnEntityRulePropChange(int iPDBID, char* szContext);

private:

};

#endif