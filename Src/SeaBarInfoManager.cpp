#include "SeaBarInfoManager.h"
#include "ConstUtil.h"
#include "GameToolAPI.h"

CSeaBarInfoManager g_SealBarManager;

CSeaBarInfoManager::CSeaBarInfoManager()
{
}


CSeaBarInfoManager::~CSeaBarInfoManager()
{
}

void CSeaBarInfoManager::LoadSeaBarData(std::string fileName)
{
	m_stSeaBarMap.clear();

	// judge file is existed?
	std::string stFile = FileUtils::getInstance()->getStringFromFile(fileName);
	if (stFile.empty())
	{
		Trace_In("warning: %s file is not exist...", __FUNCTION__);
		return;
	}

	ValueMap stFileMap = FileUtils::getInstance()->getValueMapFromFile(fileName);
	ValueMap::iterator itBegin = stFileMap.begin();
	for (; itBegin != stFileMap.end(); ++itBegin)
	{
		TSeaBarInfo stSeaBar;

		__int8 iseaBar_Index = stFileMap ["seaBar_Index"].asInt();
		stSeaBar.iCur_OwnerID = stFileMap ["ownerID"].asInt();
		stSeaBar.iCur_Price = stFileMap ["current_price"].asInt();
		stSeaBar.is_Bought = stFileMap ["is_Bought"].asInt();
		stSeaBar.iTip = stFileMap ["tip"].asInt();
		stSeaBar.iSeaBar_index = iseaBar_Index;

		m_stSeaBarMap [iseaBar_Index] = stSeaBar;
	}
}

/************************************************************************/
/* 
	func: interval dt update data
	param: float dt
	return: no
*/
/************************************************************************/
void CSeaBarInfoManager::UpdateSeaBarData(float dt)
{
	DWORD cur_time = 0;
	
	g_GameToolAPI.GetGameCurrentTime(cur_time);
	if (cur_time == 0)
	{
		return;
	}
	g_GameToolAPI.GetGameCurrentTime(cur_time);
	DWORD user_time = 0;
	g_GameToolAPI.GetUserCurrentTime(user_time);
	
	// 同一天不更新海洋馆 价格数据
	// the same day, don't fix sea bar price 
	if (g_GameToolAPI.IsSameDay(cur_time, user_time))
	{
		return;
	}

	// if not ,then update price


}

void CSeaBarInfoManager::SaveToDataBase()
{
	// cpp json
	if (m_stSeaBarMap.size() == 0)
	{
		Trace_In("error: %s map data is empty...", __FUNCTION__);
		return;
	}

	Json::Value stArrayList;

	TSeaBarInfoMap::iterator itBegin = m_stSeaBarMap.begin();
	for (; itBegin != m_stSeaBarMap.end(); ++itBegin)
	{
		TSeaBarInfo stSeaBarInfo = itBegin->second;

		Json::Value stValue;
		stValue["ownerID"] = stSeaBarInfo.iCur_OwnerID;
		stValue["seaBar_Index"] = stSeaBarInfo.iSeaBar_index;
		stValue["is_Bought"] = stSeaBarInfo.is_Bought;
		stValue["current_price"] = stSeaBarInfo.iCur_Price;
		stValue["tip"] = stSeaBarInfo.iTip;

		stArrayList.append(stValue);
	}


	Json::FastWriter owriter;
	string json_file = owriter.write(stArrayList);

	string strPath = FileUtils::getInstance()->getWritablePath();
	strPath.append(SEABAR_JSON_FILE);

	FILE* pfile = fopen(strPath.c_str(), "wb");
	if (pfile)
	{
		fputs(json_file.c_str(), pfile);
		fclose(pfile);
	}
	
}

void CSeaBarInfoManager::Start()
{
	if (CSeaBarInfoManager::create() == NULL)
	{
		Trace_In("error: %s 初始化失败...", __FUNCTION__);
		return;
	}

	// load file
	string strPath = FileUtils::getInstance()->getWritablePath();
	strPath.append(SEABAR_JSON_FILE);
	LoadSeaBarData(strPath);
	 
	// record current time
	g_GameToolAPI.SaveUserCurrentTime();

}

bool CSeaBarInfoManager::init()
{
	if (!Layer::init())
	{
		return false;
	}

	schedule(schedule_selector(CSeaBarInfoManager::UpdateSeaBarData), 60.0f);
}

void CSeaBarInfoManager::LoadSeaBarRiseData(string fileName)
{
	m_stSeaBarRiseMap.clear();

	// judge file is existed?
	std::string stFile = FileUtils::getInstance()->getStringFromFile(fileName);
	if (stFile.empty())
	{
		Trace_In("warning: %s file is not exist...", __FUNCTION__);
		return;
	}

	ValueMap stFileMap = FileUtils::getInstance()->getValueMapFromFile(fileName);
	ValueMap::iterator itBegin = stFileMap.begin();
	for (; itBegin != stFileMap.end(); ++itBegin)
	{
		TSeaBarRiseData stSeaBarRise;

		stSeaBarRise.day_index = stFileMap ["day_index"].asInt();
		stSeaBarRise.index = stFileMap ["index"].asInt();
		stSeaBarRise.val_rise = stFileMap ["val_rise"].asInt();
	
		m_stSeaBarRiseMap [stSeaBarRise.day_index] = stSeaBarRise;
	}
}
