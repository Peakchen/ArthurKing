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
	func: ��� ���£�����һ��
	param: ������ pSender
	param: �¼� CCEvent
	return : No 
	************************/
	void TouchDownAction(cocos2d::CCObject* pSender, cocos2d::CCEvent oEven);

	/**********************************
	func: ������
	param: ������ pSender
	param: �¼� CCEvent
	return : No
	******************************/
	void TouchDragEnter(cocos2d::CCObject* pSender, cocos2d::CCEvent oEven);

	/********************************
	func: ����뿪
	param: ������ pSender
	param: �¼� CCEvent
	return : No
	***************************/
	void TouchDragExit(cocos2d::CCObject* pSender, cocos2d::CCEvent oEven);

	/***********************************
	func: �����룬���������� ����һ������
	param: ������ pSender
	param: �¼� CCEvent
	return : No
	**************g********************/
	void TouchDragInside(cocos2d::CCObject* pSender, cocos2d::CCEvent oEven);

	/********************************
	func: ����뿪������������ ����һ������
	param: ������ pSender
	param: �¼� CCEvent
	return : No
	*****************************/
	void TouchDragOutside(cocos2d::CCObject* pSender, cocos2d::CCEvent oEven);

	/********************************
	func: ����ɿ����ڷ�Χ�ڣ�����
	param: ������ pSender
	param: �¼� CCEvent
	return : No
	*****************************/
	void TouchDragUpInside(cocos2d::CCObject* pSender, cocos2d::CCEvent oEven);
	
	/********************************
	func: ����ɿ����ڷ�Χ�⣬����
	param: ������ pSender
	param: �¼� CCEvent
	return : No
	*****************************/
	void TouchDragUpOutside(cocos2d::CCObject* pSender, cocos2d::CCEvent oEven);

	/**************************************
	func: �� ��� ����
	param: No
	return: void
	******************************/
	void TouchCancle();

private:
	bool m_bIsTouch;	// �Ƿ� ���� ��ť
	
	Sprite* m_pSprite;
};

#endif



