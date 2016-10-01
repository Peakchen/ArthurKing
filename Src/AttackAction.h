#ifndef __ATTACK_ACTION__
#define __ATTACK_ACTION__

#include "cocos2d.h"

USING_NS_CC;

typedef enum{
	EN_Touch_Begin = 0,
	EN_Touch_Down,
	EN_Touch_Up,
}ENTOUCHATTACK;

#pragma once

class CAttackAction :
	public cocos2d::CCNode
{
public:
	CAttackAction();
	~CAttackAction();

	CREATE_FUNC(CAttackAction);

	/*******************************
	@ func: create Attack button 
	@ 1 param: attack button png
	@ 2 param: Button Title
	@ 3 param: Font Opacity
	@ return: void
	***************************/
	bool CreateAttackButton(const char* strName_Png, unsigned int unFontOpacity, const char* strButton_Title = "0");

	/***********************
	@ func: Bind button Event
	@ return : void
	@ param: No
	********************/
	void BindButtonEvent();

	/*******************************
	func: 鼠标 按下，触发一次
	param: 发射器 pSender
	param: 事件 CCEvent
	return : No 
	************************/
	void TouchDownAction(cocos2d::CCObject* pSender, cocos2d::CCEvent oEven);

	/**********************************
	func: 鼠标进入
	param: 发射器 pSender
	param: 事件 CCEvent
	return : No
	******************************/
	void TouchDragEnter(cocos2d::CCObject* pSender, cocos2d::CCEvent oEven);

	/********************************
	func: 鼠标离开
	param: 发射器 pSender
	param: 事件 CCEvent
	return : No
	***************************/
	void TouchDragExit(cocos2d::CCObject* pSender, cocos2d::CCEvent oEven);

	/***********************************
	func: 鼠标进入，触发，满足 条件一样触发
	param: 发射器 pSender
	param: 事件 CCEvent
	return : No
	**************g********************/
	void TouchDragInside(cocos2d::CCObject* pSender, cocos2d::CCEvent oEven);

	/********************************
	func: 鼠标离开，触发，满足 条件一样触发
	param: 发射器 pSender
	param: 事件 CCEvent
	return : No
	*****************************/
	void TouchDragOutside(cocos2d::CCObject* pSender, cocos2d::CCEvent oEven);

	/********************************
	func: 鼠标松开且在范围内，触发
	param: 发射器 pSender
	param: 事件 CCEvent
	return : No
	*****************************/
	void TouchDragUpInside(cocos2d::CCObject* pSender, cocos2d::CCEvent oEven);
	
	/********************************
	func: 鼠标松开且在范围外，触发
	param: 发射器 pSender
	param: 事件 CCEvent
	return : No
	*****************************/
	void TouchDragUpOutside(cocos2d::CCObject* pSender, cocos2d::CCEvent oEven);

	/**************************************
	func: 无 鼠标 操作
	param: No
	return: void
	******************************/
	void TouchCancle();

private:
	bool m_bIsTouch;	// 是否 按下 按钮
	
	Sprite* m_pSprite;
};

#endif



