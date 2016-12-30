

/************************************************************************/
/* 
	author:	StefanChen
	mail:	2572915286@qq.com
	date:	20161210
	version:1.0
	brief:	角色部件
*/
/************************************************************************/

#ifndef __PERSON_PART__
#define __PERSON_PART__

#include "PersonMessageEventHandle.h"
#include "EntityProp.h"


class CPersonPart:
	public IAIPersonMessageSink
{
public:
	CPersonPart();
	~CPersonPart();

	//
	/************************************************************************/
	/* 
		数据库数据导入到内存中
	*/
	/************************************************************************/

	void ImportPersonData();

	/************************************************************************/
	/* 
		内存数据保存至数据库文件
	*/
	/************************************************************************/
	
	void ExportPersonData();

	///////////////////////////////IAIPersonMessageSink//////////////////////////////////////
	virtual void  OnExecMessageHandle(GWORD nMsgID, const char* szDesc);

	virtual void OnExecRuleEventMessage(int iPDBID, char* szContext, GWORD nMsgID, const char* szDesc){}

	// 取得 角色 规则属性
	int		GetPersonRuleProp(int PDBID, int iRulePropID);

	// 设置 角色 规则属性
	void	SetPersonRuleProp(int PDBID, int iRulePropID, int iValue);

	// 取得 角色属性
	int		GetPersonProp(int PDBID, int iPropID);

	// 设置 角色属性
	void	SetPersonProp(int PDBID, int iPropID, int iValue);

	TRulePropCollectMap *GetPerosnRulePropData(){ return &m_stRuleProp; }

	TPerosnPropCollectMap	*GetPersonPropData(){ return &m_stNumProp; }

private:
	//		初始化角色规则数据
	void	__InitPersonRulePropData(int PDBID);

	//		初始化角色自身属性
	void	__InitPersonSelfPropData(int PDBID);

	//		处理规则属性事件
	void	__OnEvent_RuleProp();

private:

	TRulePropCollectMap		m_stRuleProp;
	TPerosnPropCollectMap	m_stNumProp;
};


extern	CPersonPart		g_PersonPart;

#endif