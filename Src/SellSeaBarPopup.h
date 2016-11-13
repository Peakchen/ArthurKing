/************************************************************************/
/*
author:	StefanChen
mail:	chenfeng1790291543@163.com
date:	20161025
verion:	1.0
Desc:	parent: Seabar Base
		CSellSeaBarPopup
*/
/************************************************************************/

#ifndef __SELL_SEABAR_POPUP__
#define __SELL_SEABAR_POPUP__

#pragma once
#include "SeaBarPopBase.h"

class CSellSeaBarPopup :
	public CSeaBarPopBase
{
public:
	CSellSeaBarPopup();
	~CSellSeaBarPopup();

	/////////////////////////////////Layer////////////////////////////////

	virtual void	OnEnter();

	virtual void	onExit();

	/////////////////////////////////CSeaBarPopBase//////////////////////////////////////
	/************************************************************************/
	/*
	@func:		setPopContext
	@param:		const char * szTitle
	@param:		const char * szContext
	@return:	no
	@brief:		set pop dialog title and context
	*/
	/************************************************************************/
	virtual void	setPopContext(const char * szTitle, const char* szContext);

	/************************************************************************/
	/* 
	// create instance
	*/
	/************************************************************************/
	static CSellSeaBarPopup* CreateSellBarPopup();

private:

	Menu* m_pPopPlayer;
};

#endif