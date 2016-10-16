/************************************************************************/
/* 
author: StefanChen
date:	20161016
mail:	chenfeng1790291543@163.com
verison: 1.0

*/
/************************************************************************/

#ifndef _SEABAR_MANAGER_
#define _SEABAR_MANAGER_

#include "jsoncpp/include/json/json.h"
#include "cocos2d.h"
//#include "json/rapidjson.h"
//#include "json/document.h"


#pragma once
#include "common.h"
#include <string>

USING_NS_CC;

using namespace Json;

class CSeaBarInfoManager
	:public Layer
{

public:
	CSeaBarInfoManager();
	~CSeaBarInfoManager();

	/************************************************************************/
	/* 
		@func:	LoadSeaBarData()
		@param: 
		@return: no
		@desc: load all seabar data
	*/
	/************************************************************************/

	void LoadSeaBarData(std::string fileName);

	/************************************************************************/
	/*
	@func:	UpdateSeaBarData()
	@param: 
	@return: no
	@desc: Update current seabar data
	*/
	/************************************************************************/

	void UpdateSeaBarData(float dt);

	/************************************************************************/
	/*
	@func:	SaveToDataBase()
	@param: no
	@return: no
	@desc: Save all seabar data to Data Base
	*/
	/************************************************************************/

	void SaveToDataBase();

	/************************************************************************/
	/* 
	@func:	LoadSeaBarRiseData()
	@param: no
	@return: no
	@desc: Load all seabar data to memory
	*/
	/************************************************************************/
	void LoadSeaBarRiseData(string fileName);

	void Start();

	virtual bool init();

	void End();
private:

	TSeaBarInfoMap m_stSeaBarMap;
	TSeaBarRiseMap m_stSeaBarRiseMap;
};

extern CSeaBarInfoManager g_SealBarManager;

#endif