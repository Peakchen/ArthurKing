//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* ��Ϣ��������                                                                     */
/************************************************************************/

#include "stdafx.h"

#pragma once
#include "common.h"

struct IAIPersonMessageSink 
{
	virtual void  OnExecMessageHandle(GWORD nMsgID, const char* szDesc ) = 0;

	virtual void  OnExecRuleEventMessage(int iPDBID, char* szContext, GWORD nMsgID, const char* szDesc) = 0;
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
	/************************************************************************/
	/* 
		@Desc:		һ��ͨ���¼�������
		@brief:
		@param:		GWORD nMsgID			�¼�ID
		@param:		const char*  szDesc		�¼�����
	*/
	/************************************************************************/
	void FireMessage(GWORD nMsgID, const char*  szDesc);

	// �����¼�����
	/************************************************************************/
	/* 
		@brief:		�����¼�������
		@param:		int iPDBID				��ɫPDBID
		@param:		char* szContext			�ֳ�		--��תΪ��Ҫ�Ľṹ
		@param:		GWORD dstMsgID			�¼�ID
		@param:		const char*  szDesc		����

	*/
	/************************************************************************/
	void FireRulePropChangeEvent(int iPDBID, char* szContext, GWORD dstMsgID, const char*  szDesc);

private:
	TPersonMessageMap m_mapPersonMsg;

};
