#include "StdAfx.h"
#include "PersonMessageEventHandle.h"

CPersonMessageEventHandle::CPersonMessageEventHandle(void)
{
}

CPersonMessageEventHandle::~CPersonMessageEventHandle(void)
{
}

void CPersonMessageEventHandle::RegisterAIMessage(GWORD nMsgID, IAIPersonMessageSink* pAiMessageSink, const char*  szDesc)
{
	if (m_mapPersonMsg.empty())
	{
		m_mapPersonMsg [nMsgID].push_front(pAiMessageSink);
		return;
	}

	TPersonMessageMap::iterator& itMessage = m_mapPersonMsg.find(nMsgID);
	if (itMessage != m_mapPersonMsg.end())
	{
		//MessageBoxA(NULL, "NO Find This Message", "ERROR", 0);
		return;
	}
	
	TPersonMessageList& stMessageList = m_mapPersonMsg [nMsgID];
	TPersonMessageList::iterator it	= find(stMessageList.begin(), stMessageList.end(), pAiMessageSink);
	if (it == stMessageList.end())
	{
		stMessageList.push_front(pAiMessageSink);
	}

}

void CPersonMessageEventHandle::UnRegisterAIMessage( GWORD nMsgID, IAIPersonMessageSink* pAiMessageSink )
{

	TPersonMessageMap::iterator& itMessage = m_mapPersonMsg.find(nMsgID);
	if (itMessage == m_mapPersonMsg.end())
	{
		//MessageBoxA(NULL, "NO Find This Message", "ERROR", 0);
		return;
	}

	TPersonMessageList& stMessageList = itMessage->second;
	TPersonMessageList::iterator it	= find(stMessageList.begin(), stMessageList.end(), pAiMessageSink);
	if (it != stMessageList.end())
	{
		stMessageList.erase(it);
	}
}

void CPersonMessageEventHandle::FireMessage(GWORD nMsgID, const char*  szDesc)
{

	TPersonMessageMap::iterator itMessage = m_mapPersonMsg.find(nMsgID);
	if (itMessage == m_mapPersonMsg.end())
	{
		//MessageBoxA(NULL, "NO Find This Message", "ERROR", 0);
		return;
	}

	TPersonMessageList stMessageList = itMessage->second;
	TPersonMessageList::iterator it	= stMessageList.begin();
	
	for (; it != stMessageList.end(); ++it)
	{
		(*it)->OnExecMessageHandle(nMsgID, szDesc);
	}
	
}

void CPersonMessageEventHandle::ResetData()
{
	m_mapPersonMsg.clear();
}

