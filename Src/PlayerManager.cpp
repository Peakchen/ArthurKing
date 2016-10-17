#include "PlayerManager.h"
#include "ConstUtil.h"

CPlayerManager g_PalyerManager;

void CPlayerManager::DoChangeState(EPLAYER_ACTION nState)
{
	if (m_pActorBase != NULL)
	{
		m_pActorBase->OnLeave();
	}

	switch (nState)
	{
		case EACTOR_PLAYER_ACTION:
			{
				m_pActorBase = &m_oArthur;
			}
			break;
		case EAI_PLAYER_ACTION:
			{
				m_pActorBase = &m_oAiPlayer;
			}
			break;
		default:
			CCLOG("error: %s action is wrong...", __FUNCTION__);
			break;
	}

	if (m_pActorBase)
	{
		m_pActorBase->OnEnter();
	}
}

void CPlayerManager::Release()
{
	CC_SAFE_DELETE(m_pActorBase);
	m_pActorBase = NULL;
}

void CPlayerManager::Create(CActorBase* pActor)
{
	m_pActorBase = pActor;

	m_CurPlayerAction = EACTOR_PLAYER_ACTION;
	m_NextPlayerAction = EAI_PLAYER_ACTION;
}

CPlayerManager::CPlayerManager()
{

}

CPlayerManager::~CPlayerManager()
{

}

void CPlayerManager::LoadPersonInfoData(std::string filename)
{
	m_mapPersonLocation.clear();

	// judge file is existed?
	std::string stFile = FileUtils::getInstance()->getStringFromFile(filename);
	if (stFile.empty())
	{
		Trace_In("warning: %s file is not exist...", __FUNCTION__);
		return;
	}

	ValueMap stFileMap = FileUtils::getInstance()->getValueMapFromFile(filename);
	ValueMap::iterator itBegin = stFileMap.begin();
	for (; itBegin != stFileMap.end(); ++itBegin)
	{
		TPersonInfo stPerson;

		stPerson.dt_score		= stFileMap ["score"].asFloat();
		stPerson.dw_save_time	= stFileMap ["save_time"].asDouble();
		stPerson.Loc_x			= stFileMap ["x"].asFloat();
		stPerson.Loc_y			= stFileMap ["y"].asFloat();
		stPerson.person_ID		= stFileMap ["PDBID"].asFloat();

		m_mapPersonLocation [stPerson.person_ID] = &stPerson;
	}
}

void CPlayerManager::SavePersonInfoData()
{
	if (m_mapPersonLocation.size() == 0)
	{
		Trace_In("error: %s map data is empty...", __FUNCTION__);
		return;
	}

	Json::Value stArrayList;

	TPersonInfoMap::iterator itBegin = m_mapPersonLocation.begin();
	for (; itBegin != m_mapPersonLocation.end(); ++itBegin)
	{
		TPersonInfo* stPerson = itBegin->second;

		Json::Value stValue;
		stValue ["score"]		= stPerson->dt_score;
		stValue ["save_time"]	= stPerson->dw_save_time;
		stValue ["x"]			= stPerson->Loc_x;
		stValue ["y"]			= stPerson->Loc_y;
		stValue ["PDBID"]		= stPerson->person_ID;

		stArrayList.append(stValue);
	}


	Json::FastWriter owriter;
	string json_file = owriter.write(stArrayList);

	string strPath = "";
#if DEBUG
	strPath = FileUtils::getInstance()->fullPathForFilename(PERSON_JSON_FILE);
#else
	strPath = FileUtils::getInstance()->getWritablePath();
	strPath.append(PERSON_JSON_FILE);
#endif

	FILE* pfile = fopen(strPath.c_str(), "wb");
	if (pfile)
	{
		fputs(json_file.c_str(), pfile);
		fclose(pfile);
	}

}

TPersonInfo* CPlayerManager::GetPersonInfo(__int8 PDBID)
{
	if (m_mapPersonLocation [PDBID] == NULL)
		return NULL; 
	
	return m_mapPersonLocation [PDBID];

}

