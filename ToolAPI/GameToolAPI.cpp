#include "GameToolAPI.h"
#include "ConstUtil.h"
#include "stdafx.h"
#include "common.h"

CGameToolAPI g_GameToolAPI;

CGameToolAPI::CGameToolAPI()
{
}


CGameToolAPI::~CGameToolAPI()
{
}

int CGameToolAPI::GetRandomNum(int Randsize)
{
	struct timeval psv;
	cocos2d::gettimeofday(&psv, NULL);    // 计算时间种子   
	unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000;    // 初始化随机数   
	srand(tsrans);

	int arr_seq [RADN_COUNT] = { 0 };
	int arr_RandResult [RADN_COUNT] = { 0 };
	int iSub = RADN_COUNT - 1;

	for (int i = 0; i < RADN_COUNT; ++i)
	{
		int iRandom = rand()%Randsize + 1;
		Trace_In("rand num: %d ", iRandom);
		arr_seq [i] = iRandom;
		arr_RandResult [i] = iRandom;
	}

	for (int index = 0; index < RADN_COUNT; ++index)
	{
		int iRandom = rand() % Randsize + 1;
		arr_RandResult [index] = arr_seq [iRandom];
		Trace_In("arr_RandResult num: %d ", arr_RandResult [index]);
		arr_seq [iRandom] = arr_seq [iSub];
		--iSub;
	}

	int iendIndex = rand() % RADN_COUNT;

	Trace_In("Result num: %d ", arr_RandResult [iendIndex]);
	return arr_RandResult [iendIndex];
}

void CGameToolAPI::GetGameCurrentTime(DWORD &dw_time)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	struct timeval tval;
	struct tm* time;

	cocos2d::gettimeofday(&tval, NULL);
	/*time = localtime(&tval.tv_sec);*/
	dw_time = old_time.tv_sec;
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	struct tm* tme;
	time_t st_time;
	time(&st_time);

	dw_time = st_time;
#endif

}

void CGameToolAPI::SaveUserCurrentTime()
{
	DWORD dwTime = 0;
	g_GameToolAPI.GetGameCurrentTime(dwTime);
	Data userData;
	userData.copy(( unsigned char* ) &dwTime, sizeof(dwTime));
	UserDefault::getInstance()->setDataForKey("cur_time", userData);
}

void CGameToolAPI::GetUserCurrentTime(DWORD &dw_time)
{
	auto userTime = UserDefault::getInstance()->getDataForKey("cur_time", Data());
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	time_t old_time = *( time_t* ) ( userTime.getBytes() );
	dw_time = old_time;
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	struct timeval tval;
	struct timeval old_time = *( struct timeval* ) ( userTime.getBytes() );
	dw_time = old_time.tv_sec;
#endif

}

bool CGameToolAPI::IsSameDay(long long time_1, long long time_2)
{
	int one_day = 24*3600;
	long long result = abs(time_1 - time_2);
	return result < one_day;
}

void CGameToolAPI::CreateSeaBarRiseFallJsonFile(std::string filename)
{
	Json::Value stArrayList;

	Json::Value stDayList;

	for (int i=1; i<=7; ++i)
	{
		// every day data
		for (int index = 1; index < SEABAR_COUNT; ++index)
		{
			Json::Value stValue;

			stValue ["index"] = index;
			stValue ["val_rise"] = 0;
			// 当天？ 存储 第一天...?
			stValue ["day_index"] = 0;
			stArrayList.append(stValue);
		}

		stDayList.append(stArrayList);
	}


	Json::FastWriter owriter;
	string json_file = owriter.write(stDayList);

	string strPath = FileUtils::getInstance()->getWritablePath();
	strPath.append(filename);

	FILE* pfile = fopen(strPath.c_str(), "wb");
	if (pfile)
	{
		fputs(json_file.c_str(), pfile);
		fclose(pfile);
	}
}
