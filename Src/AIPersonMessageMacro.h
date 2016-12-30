/************************************************************************/
/* 消息处理中心 —— 宏                                                 */
/************************************************************************/
#include "stdafx.h"

#ifndef __AIPERSON_MESSAGE_MACRO__
#define __AIPERSON_MESSAGE_MACRO__

enum EActionMacro
{
	AI_PERSON_MOVE = 1,		//AI Move

	AI_PERSON_STOP,		//AI Stop 

	AI_START,		//actor start action

	ACTOR_START,		//actor start action

	ACTOR_MOVE,		//AI Move

	ACTOR_STOP,		//AI Stop 

	OpenCard_Action,		// Open Card

	SH_SEABAR_EXCHANGE_ACTION,	//sh  seabar exchange action

	DIALOG_CLOSE_ACTION,	// close pop

	SEABAR_EXCHANGE,	//Seabar	exchange
	SEABAR_GIVETIP,	//Seabar	give tip

	SH_SEABAR_SELL_ACTION,	//sh  seabar sell action

	PERON_RULE_PROP_CHANGE,	//actor rule prop change

	EN_RULE_PROP_EVENT,		// 规则属性事件

	////////////////////////////规则个体属性事件//////////////// 命名规则：EN_RULE_EVENT_XXX   XXX是具体事件名称
	EN_RULE_EVENT_ONCE_AGAIN,
	EN_RULE_EVENT_QUESTION,
	EN_RULE_EVENT_TURN_FREE,
	EN_RULE_EVENT_FOOT_RED,
	EN_RULE_EVENT_YELLOW_STAR,
	EN_RULE_EVENT_RED_DOUBLE_STAR,
	EN_RULE_EVENT_FOOT_BULE,
	EN_RULE_EVENT_BLUE_STAR,
	EN_RULE_EVENT_BLUE_DOUBLE_STAR,
	///////////////////////////////////////////////////////////

		//Any One can not use Max Value, and A custom Macro is In front.
	AI_MESSAGE_MAX_VALUE,
};

// 通用走法action, 
//			以后再加新的翻牌action，则在数组后面继续追加即可.
const int arrOpenCard [] = { ACTOR_START, AI_START };

#endif