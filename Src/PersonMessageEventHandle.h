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
		@Desc:		一般通用事件处理器
		@brief:
		@param:		GWORD nMsgID			事件ID
		@param:		const char*  szDesc		事件描述
	*/
	/************************************************************************/
	void FireMessage(GWORD nMsgID, const char*  szDesc);

	// 规则事件触发
	/************************************************************************/
	/* 
		@brief:		规则事件触发器
		@param:		int iPDBID				角色PDBID
		@param:		char* szContext			现场		--可转为想要的结构
		@param:		GWORD dstMsgID			事件ID
		@param:		const char*  szDesc		描述

	*/
	/************************************************************************/
	void FireRulePropChangeEvent(int iPDBID, char* szContext, GWORD dstMsgID, const char*  szDesc);

private:
	TPersonMessageMap m_mapPersonMsg;

};
