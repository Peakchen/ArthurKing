//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 消息处理中心                                                                     */
/************************************************************************/

#include "stdafx.h"

#pragma once

struct IAIPersonMessageSink 
{
	virtual void  OnExecMessageHandle(DWORD nMsgID, LPCSTR szDesc ) = 0;
};

class CPersonMessageEventHandle
{
	typedef std::list<IAIPersonMessageSink*> TPersonMessageList;
	typedef std::map<DWORD, TPersonMessageList> TPersonMessageMap;

public:
	CPersonMessageEventHandle(void);
	~CPersonMessageEventHandle(void);

	void ResetData();

	// register message
	void RegisterAIMessage(DWORD nMsgID, IAIPersonMessageSink* pAiMessageSink, LPCSTR szDesc);
	
	// unregister message
	void UnRegisterAIMessage(DWORD nMsgID, IAIPersonMessageSink* pAiMessageSink);

	// exec message
	void FireMessage(DWORD nMsgID, LPCSTR szDesc);


private:
	TPersonMessageMap m_mapPersonMsg;

};
