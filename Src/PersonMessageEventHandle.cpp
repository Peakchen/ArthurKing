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
		m_mapPersonMsg [nMsgID] = pAiMessageSink;
		return;
	}

	TPersonMessageMap::iterator& itMessage = m_mapPersonMsg.find(nMsgID);
	if (itMessage != m_mapPersonMsg.end())
	{
		//MessageBoxA(NULL, "NO Find This Message", "ERROR", 0);
		return;
	}

	m_mapPersonMsg [nMsgID] = pAiMessageSink;
}

void CPersonMessageEventHandle::UnRegisterAIMessage( GWORD nMsgID, IAIPersonMessageSink* pAiMessageSink )
{

	TPersonMessageMap::iterator& itMessage = m_mapPersonMsg.find(nMsgID);
	if (itMessage == m_mapPersonMsg.end())
	{
		//MessageBoxA(NULL, "NO Find This Message", "ERROR", 0);
		return;
	}

	m_mapPersonMsg.erase(nMsgID);
}

void CPersonMessageEventHandle::FireMessage(GWORD nMsgID, const char*  szDesc)
{

	TPersonMessageMap::iterator itMessage = m_mapPersonMsg.find(nMsgID);
	if (itMessage == m_mapPersonMsg.end())
	{
		//MessageBoxA(NULL, "NO Find This Message", "ERROR", 0);
		return;
	}

	if (itMessage->second == nullptr)
		return;

	itMessage->second->OnExecMessageHandle(nMsgID, szDesc);
}

void CPersonMessageEventHandle::ResetData()
{
	m_mapPersonMsg.clear();
}

void CPersonMessageEventHandle::FireRulePropChangeEvent(int iPDBID, char* szContext, GWORD dstMsgID, const char*  szDesc)
{
	TPersonMessageMap::iterator itMessage = m_mapPersonMsg.find(dstMsgID);
	if (itMessage == m_mapPersonMsg.end())
	{
		return;
	}

	if (itMessage->second == nullptr)
		return;

	itMessage->second->OnExecRuleEventMessage(iPDBID, szContext, dstMsgID, szDesc);
}

