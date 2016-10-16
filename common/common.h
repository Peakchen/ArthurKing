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
	__int8 iSeaBar_index;		// �±� ��Ψһ��ʶ	only index 

	// ע�ͣ� ����������ˣ�����ռ���ߣ�����û��ռ����
	//  is bought ? 1-> yes, 0->no	
	__int8   is_Bought;			// �Ƿ��ѱ�����	 1->�ѱ�����0-> δ������

	__int8   iCur_OwnerID;		// ��ǰӵ����,	0-> no one, 1->any one

	int	   iCur_Price;			// ��ǰ�۸�  current price
	int	   iTip;				// Ӧ��С�ѻ���	should give tip to other

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
// ������Ϣ person info
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