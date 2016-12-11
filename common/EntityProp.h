/************************************************************************/
/* 
arthur:		cqf
date:		20161208
version:	1.0
brief：		实体属性
*/
/***********************************************************************/

#ifndef __ENTITY_PROP__
#define __ENTITY_PROP__


#define  INVALID_PROP_VALUE  -1  	// 非法属性值

#define  INVALID_RULE_VALUE  -1		// 非法规则属性值

#define	 INVALID_MAX_VALUE	4294967295	// 32位整数最大值

// 实体属性
enum EEntityProp
{
	CREATURE_PROP_PDBID = 1,		//	角色PDBID 

	///////////////////////////////////
	CREATURE_PROP_MAX,				//  当前做大属性值，上述属性值不得超过该属性
};

// 规则属性
enum EEntityRuleProp{
	CREATURE_RULE_ID = 1,			//	规则ID , 无用
	CREATURE_RULE_PDBID,		//	角色PDBID 
	CREATURE_RULE_TURN_FREE,		//  是否轮空一次, 默认不轮空
	CREATURE_RULE_QUESTION,			//	随机获得一个当前规则的奖励或者惩罚
	CREATURE_RULE_FOOT_RED,			//	踩到地雷，原地疗伤，轮空三次
	CREATURE_RULE_YELLOW_STAR,		//  遇到火星，之后不能购买土地，踩到分数无效，共两次
	CREATURE_RULE_RED_DOUBLESTAR,	//  红双星，踩到对方土地用付费加倍，走三次内有效
	CREATURE_RULE_FOOT_BLUE,		//  哎呀，踩空了，原地休息
	CREATURE_RULE_BLUE_STAR,		//	遇到蓝星，之后无论购买什么土地都免费，踩到分数加倍，两次内有效
	CREATURE_RULE_BLUE_DOUBLESTAR,	//	蓝双星，踩到对方土地免费，走三次内有效

	///////////////////////////////////
	CREATURE_RULE_MAX,				//  当前做大属性值，上述属性值不得超过该属性
};


#endif