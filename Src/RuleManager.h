
/************************************************************************/
/* 
	aurthor:	StefanChen
	date:		20161226
	version:	1.0
	mail:		2572915286@qq.com
	brief:		���������
*/
/************************************************************************/

#ifndef __RULE_MANAGER__
#define __RULE_MANAGER__

#include "PersonMessageEventHandle.h"

class CRuleManager: 
	public	IAIPersonMessageSink
{
public:
	CRuleManager();
	~CRuleManager();

	////////////////////////////IAIPersonMessageSink//////////////////////////////////////////////

	virtual void OnExecMessageHandle(GWORD nMsgID, const char* szDesc){}

	virtual void OnExecRuleEventMessage(int iPDBID, char* szContext, GWORD nMsgID, const char* szDesc);

	// ע����Ϣ�¼�
	void	RegisterMsgEvent();

	void	Release();
private:

};

#endif