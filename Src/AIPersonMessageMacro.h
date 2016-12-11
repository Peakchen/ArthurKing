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



		//Any One can not use Max Value, and A custom Macro is In front.
	 AI_MESSAGE_MAX_VALUE,
};

//#define AI_PERSON_MOVE	0		//AI Move
//
//#define AI_PERSON_STOP	1		//AI Stop 
//
//#define AI_START		3		//actor start action
//
//#define ACTOR_START		4		//actor start action
//
//#define ACTOR_MOVE		5		//AI Move
//
//#define ACTOR_STOP		6		//AI Stop 
//
//#define OpenCard_Action	7		// Open Card
//
//#define SH_SEABAR_EXCHANGE_ACTION	8	//sh  seabar exchange action
//
//#define DIALOG_CLOSE_ACTION	 9	// close pop
//
//#define SEABAR_EXCHANGE		10	//Seabar	exchange
//#define SEABAR_GIVETIP		11	//Seabar	give tip
//
//#define SH_SEABAR_SELL_ACTION	12	//sh  seabar sell action
//
//
//
////Any One can not use Max Value, and A custom Macro is In front.
//#define AI_MESSAGE_MAX_VALUE 256


#endif