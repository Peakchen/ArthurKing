/************************************************************************/
/*
author:		StefanChen
mail:		chenfeng1790291543@163.com
date:		20161021
version:	1.0
Desc:		Setting Menu,	parent:	Popup Base
*/
/************************************************************************/

#ifndef __SETTING_MENU__
#define __SETTING_MENU__

#include "cocos2d.h"
#include "PopupBase.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace CocosDenshion;

#pragma once
class CSettingMenu
	:	public	CPopupBase
{
	
public:
	CSettingMenu();
	~CSettingMenu();

	/************************************************************************/
	/*
	@func:		Create
	@param:		no
	@param:		no
	@return:	void
	@brief:		todo someing
	*/
	/************************************************************************/
	CREATE_FUNC(CSettingMenu);

	static CSettingMenu*	create(const char* szTitle);

	
	/************************************************************************/
	/*
	@func:		Release
	@param:		no
	@param:		no
	@return:	void
	@brief:		release	memory
	*/
	/************************************************************************/
	void	Release();
	
	virtual bool init();

	/************************************************************************/
	/* 
	@func:	father class -> Layer
	*/
	/************************************************************************/
	virtual void onEnter();

	/************************************************************************/
	/*
	@func:	father class -> Layer
	*/
	/************************************************************************/
	virtual void onExit();


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
	@func:		setPopContext
	@param:		const char * szTitle
	@param:		const char * szContext
	@return:	no
	@brief:		set pop dialog title and context
	*/
	/************************************************************************/
	virtual void  setPopContext(const char * szTitle, const char* szContext){}

private:
	/************************************************************************/
	/*
	@func:		InitSettingMenu
	@param:		
	@param:		Point oPoint,		Default Value:	Point::ZERO,
	@return:	void
	@brief:		construct menu
	*/
	/************************************************************************/
	void	InitSettingMenu( Point point = Point::ZERO);

	/************************************************************************/
	/* 
	@func:		OnEnterSettingMenuCallBack()
	@param:		no
	@return:	void
	@brief:		Enter SettingMenu, then todo ...
	*/
	/************************************************************************/
	void	OnEnterSettingMenuCallBack();

	/************************************************************************/
	/*
	@func:		OnEixtSettingMenuCallBack()
	@param:		no
	@return:	void
	@brief:		Exit SettingMenu, then todo ...
	*/
	/************************************************************************/
	void	OnEixtSettingMenuCallBack(Object* pSender, Control::EventType event);

	/************************************************************************/
	/* 
	@func:		AddSettingMenuItem()
	@param:		no
	@return:	void
	@brief:		add SettingMenu item to vector
	*/
	/************************************************************************/
	void	AddSettingMenuItem();

	/************************************************************************/
	/* 
	@func:		OnCancleSettingMenuAction()
	@param:		no
	@return:	void
	@brief:		close Menu
	*/
	/************************************************************************/
	void	OnCancleSettingMenuAction();

	/************************************************************************/
	/*
	@func:		OnEixtGameCallBack()
	@param:		no
	@return:	void
	@brief:		Exit Game, then todo ...
	*/
	/************************************************************************/
	void	OnEixtGameCallBack();

	/************************************************************************/
	/*
	@func:		OnPlayGameBgMusicCallBack()
	@param:		no
	@return:	void
	@brief:		Play Game Bg Music, then todo ...
	*/
	/************************************************************************/
	void	OnPlayGameBgMusicCallBack();

private:
	TVecMenuItem m_vecMenuItem;

	Menu*	m_pMainMenu;

	bool	m_isPlayMusic;

	Vec2	m_VecOldPoint;
};

#endif