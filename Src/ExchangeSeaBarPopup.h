/************************************************************************/
/* 
author:	StefanChen
mail:	chenfeng1790291543@163.com
date:	20161025
verion:	1.0
Desc:	parent: Seabar Base
		CExchangeSeaBarPopup
*/
/************************************************************************/

#ifndef __EXCHANGE_SEABAR_POPUP__
#define __EXCHANGE_SEABAR_POPUP__

#pragma once
#include "SeaBarPopBase.h"

class CExchangeSeaBarPopup :
	public CSeaBarPopBase
{
public:
	CExchangeSeaBarPopup();
	~CExchangeSeaBarPopup();

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

private:

	Menu* m_pPopPlayer;
};

#endif