#pragma once
/************************************************************************/
/*
author:	StefanChen
mail:	chenfeng1790291543@163.com
date:	20161025
verion:	1.0
Desc:	Seabar Base
*/
/************************************************************************/

#ifndef __SEABAR_BASE__
#define __SEABAR_BASE__

#include "PopupBase.h"

class CSeaBarPopBase
	: public CPopupBase
{
public:
	CSeaBarPopBase();
	~CSeaBarPopBase();
	
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

	virtual void	OnEnter();

	virtual void	onExit();
};

#endif
