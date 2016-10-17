#ifndef _GAME_TOOL_API_
#define _GAME_TOOL_API_

#include "cocos2d.h"
#include <math.h>
#include "jsoncpp/include/json/json.h"

USING_NS_CC;
using namespace Json;

#pragma once
#include "common.h"
class CGameToolAPI
{
public:
	CGameToolAPI();
	~CGameToolAPI();

	/************************************************************************/
	/*
	func: GetRandomNum
	Desc: rand get a num between 1 and randsize
	return: int
	*/
	/************************************************************************/
	int GetRandomNum(int Randsize);


	/************************************************************************/
	/* 
	func: GetCurrentTime
	Desc:  get current time , unit s
	return: void 
	*/
	/************************************************************************/

	void GetGameCurrentTime(GWORD &dw_time);


	/************************************************************************/
	/* 
	func: SaveUserCurrentTime
	Desc:  save user opertion current time , unit s
	return: void
	*/
	/************************************************************************/
	void SaveUserCurrentTime();


	/************************************************************************/
	/*
	func: GetUserCurrentTime
	Desc:  get user opertion current time , unit s
	return: void
	*/
	/************************************************************************/
	void GetUserCurrentTime(GWORD &dw_time);

	/************************************************************************/
	/* 
	func: GetUserCurrentTime
	Desc:  get user opertion current time , unit s
	@param : time_1
	@param : time_2
	return: void
	*/
	/************************************************************************/
	bool IsSameDay(long long time_1, long long time_2);

	/************************************************************************/
	/* 
		func:  CreateSeaBarRiseFallJsonFile()
		Desc:  Create Json file for test
		@param : string filename
		return: void
	*/
	/************************************************************************/

	void CreateSeaBarRiseFallJsonFile(std::string filename);
};

extern CGameToolAPI g_GameToolAPI;

#endif