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

USING_NS_CC;

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
	void	Create();

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
	void	OnEixtSettingMenuCallBack();

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

private:
	TVecMenuItem m_vecMenuItem;

	Menu*	m_pMainMenu;
};

#endif