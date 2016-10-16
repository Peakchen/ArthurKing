/************************************************************************/
/* 
	author: StefanChen
	date: 20161016
	mail: chenfeng1790291543@163.com
	version: 1.0
*/
/************************************************************************/

#ifndef _COMMON_
#define _COMMON_

#include "stdafx.h"

/************************************************************************/
/*
sea bar struct
*/
/************************************************************************/
struct TSeaBarInfo
{
	__int8 iSeaBar_index;		// 下标 ，唯一标识	only index 

	// 注释： 如果被购买了，则有占有者，否则，没有占有者
	//  is bought ? 1-> yes, 0->no	
	__int8   is_Bought;			// 是否已被购买	 1->已被购买，0-> 未被购买

	__int8   iCur_OwnerID;		// 当前拥有者,	0-> no one, 1->any one

	int	   iCur_Price;			// 当前价格  current price
	int	   iTip;				// 应付小费积分	should give tip to other

	//DWORD  save_time;			// save time

	TSeaBarInfo(){
		iSeaBar_index = 1;
		is_Bought = 0;
		iCur_OwnerID = 0;
		iCur_Price = 0;
		iTip = 0;
		//save_time = 0;
	}
};

typedef std::map<__int8, TSeaBarInfo> TSeaBarInfoMap;

////////////////////////////////////////////////////////////////////////////////////
// 人物信息 person info
struct TPersonInfo
{
	DWORD  dw_save_time;			// save time
	__int8 person_ID;			// only one id
	float Loc_x;				// coordate x
	float Loc_y;				// coordate y

	DWORD dw_score;				// score

	TPersonInfo()
	{
		dw_save_time = 0;
		person_ID = 0;
		Loc_y = 0.0f;
		Loc_x = 0.0f;
		dw_score = 0;
	}
};

typedef map<__int8, TPersonInfo> TPersonInfoMap;

typedef long long LDWORD;

/************************************************************************/
/* 
	every day rise sea bar data
*/
/************************************************************************/

struct TSeaBarRiseData
{
	int index;			// sea bar index
	float val_rise;		// cur rise value
	int day_index;		// follow day

	TSeaBarRiseData()
	{
		index = 0;
		val_rise = 0.0f;
		day_index = 0;
	}
};

typedef map<int, TSeaBarRiseData> TSeaBarRiseMap;

#endif