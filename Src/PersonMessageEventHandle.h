//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 消息处理中心                                                                     */
/************************************************************************/

#include "stdafx.h"

#pragma once
#include "common.h"

struct IAIPersonMessageSink 
{
	virtual void  OnExecMessageHandle(GWORD nMsgID, const char* szDesc ) = 0;
};

class CPersonMessageEventHandle
{
	typedef std::map<GWORD, IAIPersonMessageSink*> TPersonMessageMap;

public:
	CPersonMessageEventHandle(void);
	~CPersonMessageEventHandle(void);

	void ResetData();

	// register message
	void RegisterAIMessage(GWORD nMsgID, IAIPersonMessageSink* pAiMessageSink, const char*  szDesc);
	
	// unregister message
	void UnRegisterAIMessage(GWORD nMsgID, IAIPersonMessageSink* pAiMessageSink);

	// exec message
	void FireMessage(GWORD nMsgID, const char*  szDesc);


private:
	TPersonMessageMap m_mapPersonMsg;

};
