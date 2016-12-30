
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

	// 随机出奖励或者惩罚
	/************************************************************************/
	/* 
		@param:	随机一个枚举操作	输出
	*/
	/************************************************************************/
	int	GetRandomOneOperation();

	/************************************************************************/
	/* 
		@brief:	执行操作

	*/
	/************************************************************************/

	void	OnEnterOperation(int iOperation, int PDBID);

	//////////////////////IEntityRulePropHandler///////////////////////////////
	
	virtual void	OnEntityRulePropChange(int iPDBID, char* szContext);

protected:
	
private:
		
};