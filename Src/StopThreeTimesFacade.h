
/************************************************************************/
/* 
		aurthor:	StefanChen
		date:		20161229
		version:	1.0
		brief:		ԭ��ֹͣ����	
*/
/************************************************************************/

#include "ActionSpiltHandler.h"

#ifndef __STOP_THREE_TIMES__
#define __STOP_THREE_TIMES__

class CStopThreeTimesFacade :
	public IEntityRulePropHandler
{
public:
	CStopThreeTimesFacade();
	~CStopThreeTimesFacade();

	//////////////////////////IEntityRulePropHandler/////////////////////////////
	
	virtual		void	OnEntityRulePropChange(int iPDBID, char* szContext);

private:

};

#endif