
/************************************************************************/
/* 
	aurthor:	StefanChen
	date:		20161231
	version:	1.0
	brief:		��˫�ǣ��ȵ��Է�������ѣ�����������Ч

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

