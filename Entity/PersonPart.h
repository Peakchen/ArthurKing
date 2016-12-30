

/************************************************************************/
/* 
	author:	StefanChen
	mail:	2572915286@qq.com
	date:	20161210
	version:1.0
	brief:	��ɫ����
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
		���ݿ����ݵ��뵽�ڴ���
	*/
	/************************************************************************/

	void ImportPersonData();

	/************************************************************************/
	/* 
		�ڴ����ݱ��������ݿ��ļ�
	*/
	/************************************************************************/
	
	void ExportPersonData();

	///////////////////////////////IAIPersonMessageSink//////////////////////////////////////
	virtual void  OnExecMessageHandle(GWORD nMsgID, const char* szDesc);

	virtual void OnExecRuleEventMessage(int iPDBID, char* szContext, GWORD nMsgID, const char* szDesc){}

	// ȡ�� ��ɫ ��������
	int		GetPersonRuleProp(int PDBID, int iRulePropID);

	// ���� ��ɫ ��������
	void	SetPersonRuleProp(int PDBID, int iRulePropID, int iValue);

	// ȡ�� ��ɫ����
	int		GetPersonProp(int PDBID, int iPropID);

	// ���� ��ɫ����
	void	SetPersonProp(int PDBID, int iPropID, int iValue);

	TRulePropCollectMap *GetPerosnRulePropData(){ return &m_stRuleProp; }

	TPerosnPropCollectMap	*GetPersonPropData(){ return &m_stNumProp; }

private:
	//		��ʼ����ɫ��������
	void	__InitPersonRulePropData(int PDBID);

	//		��ʼ����ɫ��������
	void	__InitPersonSelfPropData(int PDBID);

	//		������������¼�
	void	__OnEvent_RuleProp();

private:

	TRulePropCollectMap		m_stRuleProp;
	TPerosnPropCollectMap	m_stNumProp;
};


extern	CPersonPart		g_PersonPart;

#endif