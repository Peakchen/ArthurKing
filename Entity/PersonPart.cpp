
#include "PersonPart.h"
#include "EntityProp.h"
#include "PlayerManager.h"

CPersonPart	 g_PersonPart;

CPersonPart::CPersonPart()
{

}

CPersonPart::~CPersonPart()
{

}

void CPersonPart::ImportPersonData()
{
	FOR_EACH_CONTAINER(TPersonInfoMap, ( *g_PalyerManager.GetActorLocInfo() ), itActor)
	{
		__InitPersonRulePropData(itActor->first);
		__InitPersonSelfPropData(itActor->first);
	}
}

void CPersonPart::ExportPersonData()
{
	//g_PalyerManager.SavePersonInfoData();
}

void CPersonPart::OnExecMessageHandle(GWORD nMsgID, const char* szDesc)
{
	switch (nMsgID)
	{
		default:
			break;
	}
}

void CPersonPart::__InitPersonRulePropData(int PDBID)
{

	SetPersonRuleProp(PDBID, CREATURE_RULE_ID, 0);	//不必赋值	不必赋值	不必赋值

	////////////////////////////////导入规则数据//////////////////////////////////

	SetPersonRuleProp(PDBID, CREATURE_RULE_TURN_FREE, 0);
	SetPersonRuleProp(PDBID, CREATURE_RULE_QUESTION, 0);
	SetPersonRuleProp(PDBID, CREATURE_RULE_FOOT_RED, 0);
	SetPersonRuleProp(PDBID, CREATURE_RULE_YELLOW_STAR, 0);
	SetPersonRuleProp(PDBID, CREATURE_RULE_RED_DOUBLESTAR, 0);
	SetPersonRuleProp(PDBID, CREATURE_RULE_FOOT_BLUE, 0);
	SetPersonRuleProp(PDBID, CREATURE_RULE_BLUE_STAR, 0);
	SetPersonRuleProp(PDBID, CREATURE_RULE_BLUE_DOUBLESTAR, 0);
}

void CPersonPart::__InitPersonSelfPropData(int PDBID)
{
	////////////////////////////////导入角色数据/////////////////////////////
	SetPersonProp(PDBID, CREATURE_PROP_PDBID, 1);
}

int CPersonPart::GetPersonRuleProp(int PDBID, int iRulePropID)
{
	if (iRulePropID <= CREATURE_RULE_ID ||
		iRulePropID >= CREATURE_RULE_MAX)
	{
		return INVALID_RULE_VALUE;
	}

	TPropMap* pstRuleProp = m_stRuleProp [PDBID];
	if (pstRuleProp == nullptr)
	{
		return INVALID_RULE_VALUE;
	}

	TPropMap::iterator it = pstRuleProp->find(iRulePropID);
	if (it == pstRuleProp->end())
	{
		return INVALID_RULE_VALUE;
	}

	return it->second;
}

void CPersonPart::SetPersonRuleProp(int PDBID, int iRulePropID, int iValue)
{
	if (iRulePropID <= CREATURE_RULE_ID ||
		iRulePropID >= CREATURE_RULE_MAX)
	{
		Trace_In("error: %s 错误的规则属性ID.", __FUNCTION__);
		return;
	}

	if (INVALID_MAX_VALUE < iValue || 
		iValue >= INVALID_RULE_VALUE)
	{
		Trace_In("error: %s 错误的规则属性值.", __FUNCTION__);
		return;
	}

	if (m_stRuleProp.empty())
	{
		TPropMap pstRuleProp;
		pstRuleProp [iRulePropID] = 0;
		m_stRuleProp [PDBID] = &pstRuleProp;
	}

	TPropMap* pstRuleProp = m_stRuleProp [PDBID];
	if (pstRuleProp == nullptr)
	{
		return;
	}

	TPropMap::iterator& it = pstRuleProp->find(iRulePropID);
	if (it == pstRuleProp->end())
	{
		return;
	}

	it->second = iValue;
}

int CPersonPart::GetPersonProp(int PDBID, int iPropID)
{
	if (iPropID <= CREATURE_RULE_ID ||
		iPropID >= CREATURE_RULE_MAX)
	{
		return INVALID_RULE_VALUE;
	}

	TPropMap* pstProp = m_stNumProp [PDBID];
	if (pstProp == nullptr)
	{
		return INVALID_RULE_VALUE;
	}

	TPropMap::iterator it = pstProp->find(iPropID);
	if (it == pstProp->end())
	{
		return INVALID_RULE_VALUE;
	}

	return it->second;
}

void CPersonPart::SetPersonProp(int PDBID, int iPropID, int iValue)
{
	if (iPropID <= CREATURE_RULE_ID ||
		iPropID >= CREATURE_RULE_MAX)
	{
		Trace_In("error: %s 错误的规则属性ID.", __FUNCTION__);
		return;
	}

	if (INVALID_MAX_VALUE < iValue ||
		iValue >= INVALID_RULE_VALUE)
	{
		Trace_In("error: %s 错误的规则属性值.", __FUNCTION__);
		return;
	}

	if (m_stNumProp.empty())
	{
		TPropMap pstProp;
		pstProp [iPropID] = 0;
		m_stNumProp [PDBID] = &pstProp;
	}

	TPropMap* pstProp = m_stNumProp [PDBID];
	if (pstProp == nullptr)
	{
		return;
	}

	TPropMap::iterator& it = pstProp->find(iPropID);
	if (it == pstProp->end())
	{
		return;
	}

	it->second = iValue;
}

