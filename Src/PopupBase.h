/************************************************************************/
/* 
author:		StefanChen
mail:		chenfeng1790291543@163.com
date:		20161021
version:	1.0
Desc:		Popup Base
*/
/************************************************************************/

#ifndef __POPUP_MENU__
#define __POPUP_MENU__

#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum ESettingMenuTag
{
	EBackGround = 100,
	EBG_Music,
	EBG_EXIT,
};

class CPopupBase :
	public Layer
{
public:
	typedef Vector<MenuItem*> TVecMenuItem;

public:
	CPopupBase();
	~CPopupBase();
	
	/************************************************************************/
	/* 
	@func:		CreateMenuItemByfontCallback
	@param:		const char* szBtnName
	@param:		ccMenuCallback callback
	@param:		int oFontSize
	@param:		const char* szFontName
	@param:		MenuItem* pMenuItem
	@param:		Point oPoint,		Default Value:	Point::ZERO
	@param:		Size oSize			Default Value:	CCSizeZero
	@return:	void
	@brief:		you can add menuitem which type is font to map, then join in and construct menu
	*/
	/************************************************************************/
	void	CreateMenuItemByfontCallback(const char* szBtnName, ccMenuCallback callback, int oFontSize, const char* szFontName, MenuItemLabel** pMenuItem, Point oPoint = Point::ZERO, Size oSize = Size::ZERO);

	
	/************************************************************************/
	/*
	@func:		CreateMenuItemByLabelCallBack
	@param:		const char* szBtnName
	@param:		const char*	szFontType
	@param:		ccMenuCallback callback
	@param:		MenuItem* pMenuItem
	@param:		Point oPoint,		Default Value:	Point::ZERO,
	@param:		Size oSize			Default Value:	CCSizeZero
	@return:	void
	@brief:		you can add menuitem which type is Label  to map, then join in and construct menu
	*/
	/************************************************************************/
	void	CreateMenuItemByLabelCallBack(const char*	szBtnName, const char*	szFontType, ccMenuCallback callback, MenuItem** pMenuItem, Point point = Point::ZERO, Size oSize = Size::ZERO);

	/************************************************************************/
	/*
	@func:		CreatMenuItemByeImageCallback
	@param:		const char* szBtnName
	@param:		const char* szSelectpic
	@param:		const char* szDisablepic
	@param:		ccMenuCallback callback
	@param:		MenuItemImage* pMenuItem
	@param:		Point oPoint,		Default Value:	Point::ZERO,
	@param:		Size oSize			Default Value:	CCSizeZero
	@return:	void
	@brief:		you can add menuitem which type is Image  to map, then join in and construct menu
	*/
	/************************************************************************/
	void	CreatMenuItemByeImageCallback(const char*  szNormalpic, const char* szSelectpic, const char* szDisablepic, ccMenuCallback callback, MenuItemImage** pMenuItem, Point point = Point::ZERO, Size oSize = Size::ZERO);

	/************************************************************************/
	/* 
	@func:		CreateMenuItemBySpriteCallBack
	@param:		const char* szBtnName
	@param:		const char* szSelectpic
	@param:		ccMenuCallback callback
	@param:		MenuItem* pMenuItem
	@param:		Point oPoint,		Default Value:	Point::ZERO,
	@param:		Size oSize			Default Value:	CCSizeZero
	@return:	void
	@brief:		you can add menuitem which type is sprite to map, then join in and construct menu
	*/
	/************************************************************************/

	void	CreateMenuItemBySpriteCallBack(const char* szNormalpic, const char* szSelectpic, const char* szdisablepic, ccMenuCallback callback, MenuItem** pMenuItem, Point point = Point::ZERO, Size oSize = Size::ZERO);


	/************************************************************************/
	/*
	@func:		OnEixtSettingMenuCallBack()
	@param:		no
	@return:	void
	@brief:		Exit SettingMenu, then todo ...
	*/
	/************************************************************************/
	virtual void	OnEixtSettingMenuCallBack(Object* pSender, Control::EventType event);

	/************************************************************************/
	/*
	@func:		CreatePopupModule
	@param:		no
	@return:	no
	@brief:		create common pop module for child class
	*/
	/************************************************************************/
	void	CreatePopupModule();

	/************************************************************************/
	/* 
	@func:		setPopContext
	@param:		const char * szTitle
	@param:		const char * szContext
	@return:	no
	@brief:		set pop dialog title and context
	*/
	/************************************************************************/
	virtual void  setPopContext(const char * szTitle, const char* szContext) = 0;


	/** Callback function for touch began.
	*
	* @param touch Touch information.
	* @param unused_event Event information.
	* @return if return false, onTouchMoved, onTouchEnded, onTouchCancelled will never called.
	* @js NA
	*/
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	/** Callback function for touch moved.
	*
	* @param touch Touch information.
	* @param unused_event Event information.
	* @js NA
	*/
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	/** Callback function for touch ended.
	*
	* @param touch Touch information.
	* @param unused_event Event information.
	* @js NA
	*/
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	/** Callback function for touch cancelled.
	*
	* @param touch Touch information.
	* @param unused_event Event information.
	* @js NA
	*/
	virtual void onTouchCancelled(Touch *touch, Event *unused_event);

	/************************************************************************/
	/*
	func:
	*/
	/************************************************************************/

	virtual void	OnEnter();

	virtual void	onExit();
};

#endif
