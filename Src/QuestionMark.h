
/************************************************************************/
/* 
arthur:		StefanChen
date:		20161127
version:	1.0
brief:		random prize or punish
*/
/************************************************************************/

#include "ActionSpiltHandler.h"

class CQuestionMark:
	public IEntityRulePropHandler
{
public:
	CQuestionMark();
	~CQuestionMark();

	// ������������߳ͷ�
	/************************************************************************/
	/* 
		@param:	���һ��ö�ٲ���	���
	*/
	/************************************************************************/
	int	GetRandomOneOperation();

	/************************************************************************/
	/* 
		@brief:	ִ�в���

	*/
	/************************************************************************/

	void	OnEnterOperation(int iOperation, int PDBID);

	//////////////////////IEntityRulePropHandler///////////////////////////////
	
	virtual void	OnEntityRulePropChange(int iPDBID, char* szContext);

protected:
	
private:
		
};