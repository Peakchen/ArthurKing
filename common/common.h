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

class CActorBase;

/************************************************************************/
/*
sea bar struct
*/
/************************************************************************/
struct TSeaBarInfo
{
	__int8			iSeaBar_index;		// 下标 ，唯一标识	only index 

	// 注释： 如果被购买了，则有占有者，否则，没有占有者
	//  is bought ? 1-> yes, 0->no	
	__int8			is_Bought;			// 是否已被购买	 1->已被购买，0-> 未被购买

	__int8			iCur_OwnerID;		// 当前拥有者,	0-> no one, 1->any one

	float			iCur_Score;			// 当前价格  current Score
	float			iTip;				// 应付小费积分	should give tip to other

	//GWORD  save_time;			// save time

	TSeaBarInfo(){
		iSeaBar_index = 1;
		is_Bought = 0;
		iCur_OwnerID = 0;
		iCur_Score = 0.0f;
		iTip = 0.0f;
		//save_time = 0;
	}
};

typedef std::map<__int8, TSeaBarInfo*> TSeaBarInfoMap;

////////////////////////////////////////////////////////////////////////////////////
// 人物信息 person info
struct TPersonInfo
{
	double		dw_save_time;			// save time
	__int8		person_ID;				// only one id
	float		Loc_x;					// coordate x
	float		Loc_y;					// coordate y

	float		dt_score;					// score

	TPersonInfo()
	{
		dw_save_time = 0;
		person_ID = 0;
		Loc_y = 0.0f;
		Loc_x = 0.0f;
		dt_score = 0.0f;
	}
};

typedef map<__int8, TPersonInfo*> TPersonInfoMap;

typedef long long LGWORD;

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

typedef map<int, TSeaBarRiseData*> TSeaBarRiseMap;

// 海洋馆 归属
// seabar owner
enum ESeaBarAttach
{
	ESeaBar_None = 0,		// no one 
	ESeaBar_other,			// other
	ESeaBar_self,			// self
	ESeaBar_Error,			// but error
};

// 角色 枚举 
// actor menu
enum EPlayer
{
	EFirstPlayer = 1,
	ESecondPlayer,
};

typedef unsigned long GWORD;


// eleven tile layer type name
// date:  20161029
const string TILELAYER_NAME [] = {
							"OnceAgain", 
							"sea", 
							"Score",
							"Question",
							"Turn_Free",
							"Foot_red",
							"Yellow_Star",
							"Red_DoubleStar",
							"Foot_Blue",
							"Blue_Star",
							"Blue_DoubleStar",
							};

#define		ETILELAYER_ONCEAGAIN	"OnceAgain"
#define		ETILELAYER_SEABAR		"sea"
#define		ETILELAYER_SCORE		"Score"
#define		ETILELAYER_QUESTION		"Question"
#define		ETILELAYER_TUEN_FREE		"Turn_Free"
#define		ETILELAYER_FOOT_RED		"Foot_red"
#define		ETILELAYER_YELLOW_STAR	"Yellow_Star"
#define		ETILELAYER_RED_DOUBLESTAR	"Red_DoubleStar"
#define		ETILELAYER_FOOT_BLUE		"Foot_Blue"
#define		ETILELAYER_BLUE_STAR		"Blue_Star"
#define		ETILELAYER_BLUE_DOUBLESTAR	"Blue_DoubleStar"


// custom type

#define		ETILELAYER_TYPE_RAND_NUM	"rand_num"
#define		ETILELAYER_TYPE_BAR			"Bar"
#define		ETILELAYER_TYPE_INT			"int"
#define		ETILELAYER_TYPE_RANDOM		"random"
#define		ETILELAYER_TYPE_UP			"Up"
#define		ETILELAYER_TYPE_DOWN		"Down"

const string TILELAYER_CUSTOM_TYPE [] = { 
								  "rand_num",
								  "Bar",
								  "int",
								  "random",
								  "Up",
								  "Down",
								};

struct TTileLayerGridProperty
{
	string	szName;
	string	szType;
	int		iScoreValue;
	int		iSeaBarIndex;
	int		iSeaBarPrice;
	int		iSeaBarTip;
	int		iTimes;
	int		iStopTimes;
	int		iScoreMult;

	TTileLayerGridProperty()
	{
		szName = "";
		szType = "";
		iScoreValue = 0;
		iSeaBarIndex = 0;
		iSeaBarPrice = 0;
		iSeaBarTip = 0;
		iTimes = 0;
		iStopTimes = 0;
		iScoreMult = 0;
	}

	TTileLayerGridProperty& operator=( TTileLayerGridProperty &stTileGrid)
	{
		this->szName = stTileGrid.szName;
		this->szType = stTileGrid.szType;
		this->iScoreValue = stTileGrid.iScoreValue;
		this->iSeaBarIndex = stTileGrid.iSeaBarIndex;
		this->iSeaBarPrice = stTileGrid.iSeaBarPrice;
		this->iSeaBarTip = stTileGrid.iSeaBarTip;
		this->iTimes = stTileGrid.iTimes;
		this->iStopTimes = stTileGrid.iStopTimes;
		this->iScoreMult = stTileGrid.iScoreMult;

		return *this;
	}

};

typedef map<int, CActorBase*> TActorTileLayerInfoMap;


typedef map<int, int>			TPropMap;
typedef map<int, TPropMap*>		TPerosnRulePropMap;
typedef map<int, TPropMap*>		TPerosnPropMap;

//随机 操作
enum EQuestionType
{
	EType_Score_Sub_Ten = 1,		//-10分
	EType_Foot_Blue,				//对方轮空一次

	/////////
	EType_Max,		//最大类型,上述不得超过
};


#define FOR_EACH_CONTAINER(TYPE, CONTAINER, IT) for(TYPE::iterator IT = CONTAINER.begin(); IT != CONTAINER.end(); ++IT)

#endif