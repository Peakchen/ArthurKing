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


// 规则属性map
struct TRuleProp
{
	int iRulePropID;
	int iRulePropValue;
	TRuleProp()
	{
		memset(this, 0, sizeof(TRuleProp));
	}

	TRuleProp& operator=( const TRuleProp stRuleProp )
	{
		iRulePropID = stRuleProp.iRulePropID;
		iRulePropValue = stRuleProp.iRulePropValue;
		return *this;
	}

};

typedef map<int, TRuleProp>					TRuleSinglePropMap;
typedef map<int, TRuleSinglePropMap>		TRulePropCollectMap;

// 角色属性map
struct TPersonProp
{
	int iPropID;
	int iValue;
	TPersonProp()
	{
		memset(this, 0, sizeof(TPersonProp));
	}

	TPersonProp& operator=( const TPersonProp stPersonProp)
	{
		iPropID = stPersonProp.iPropID;
		iValue = stPersonProp.iValue;
		return *this;
	}
};

typedef map<int, TPersonProp>				TPersonSinglePropMap;
typedef map<int, TPersonSinglePropMap>		TPerosnPropCollectMap;

//随机 操作
enum EQuestionType
{
	EType_Score_Sub_Ten = 1,		//-10分
	EType_Foot_Blue,				//对方轮空一次

	/////////
	EType_Max,		//最大类型,上述不得超过
};


// 正向遍历宏
#define FOR_EACH_CONTAINER(TYPE, CONTAINER, IT) for(TYPE::iterator IT = CONTAINER.begin(); IT != CONTAINER.end(); ++IT)

/////////////////////////////////////规则事件现场///////////////////////////////////
// 注意申明：
//			凡规则现场，都以	"TR_" 打头，	后面接  规则自定义名称		

//	Once Again	随机五个数字，走随机出来的格子数

struct TR_OnceAgain
{
	int iRandomStep;		//随机步数
	TR_OnceAgain()
	{
		memset(this, 0, sizeof(TR_OnceAgain));
	}
};

// 随机获得一个当前规则的奖励或者惩罚
struct TR_Question
{
	//字段...

	// 初始化
	TR_Question()
	{
		memset(this, 0, sizeof(TR_Question));
	}
};

//让对手轮空一次
struct TR_Turn_Free
{
	//字段...

	// 初始化
	TR_Turn_Free()
	{
		memset(this, 0, sizeof(TR_Turn_Free));
	}
};

//踩到地雷，原地疗伤，轮空三次
struct TR_Foot_Red
{
	//字段...

	// 初始化
	TR_Foot_Red()
	{
		memset(this, 0, sizeof(TR_Foot_Red));
	}
};

//遇到火星，之后不能购买土地，踩到分数无效，共两次
struct TR_Yellow_Star
{
	//字段...

	// 初始化
	TR_Yellow_Star()
	{
		memset(this, 0, sizeof(TR_Yellow_Star));
	}
};

//红双星，踩到对方土地用付费加倍，走三次内有效

struct TR_Red_DoubleStar
{
	//字段...

	// 初始化
	TR_Red_DoubleStar()
	{
		memset(this, 0, sizeof(TR_Red_DoubleStar));
	}
};

//哎呀，踩空了，原地休息一次
struct TR_Foot_Blue
{
	//字段...

	// 初始化
	TR_Foot_Blue()
	{
		memset(this, 0, sizeof(TR_Foot_Blue));
	}
};

//遇到蓝星，之后无论购买什么土地都免费，踩到分数加倍，两次内有效
struct TR_Blue_Star
{
	//字段...

	// 初始化
	TR_Blue_Star()
	{
		memset(this, 0, sizeof(TR_Blue_Star));
	}
};

//蓝双星，踩到对方土地免费，走三次内有效
struct TR_Blue_DoubleStar
{
	//字段...

	// 初始化
	TR_Blue_DoubleStar()
	{
		memset(this, 0, sizeof(TR_Blue_DoubleStar));
	}
};

///////////////////////////////////////////规则现场////////end////////////////////////////////////


#endif