/************************************************************************/
/* 
		aurthor:	StefanChen
		date:		20161231
		version:	1.0
		brief:		��˫�ǣ��ȵ��Է������ø��Ѽӱ�������������Ч
*/
/************************************************************************/

#ifndef  __RED_DOUBLESTAR_FACADE__
#define  __RED_DOUBLESTAR_FACADE__

#include "ActionSpiltHandler.h"

class CRed_DoubleStar_Facade :
	public IEntityRulePropHandler
{
public:
	CRed_DoubleStar_Facade();
	~CRed_DoubleStar_Facade();

	//////////////////////////IEntityRulePropHandler////////////////////////

	virtual void	OnEntityRulePropChange(int iPDBID, char* szContext);

private:

};


#endif