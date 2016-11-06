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
	@func:		OnEixtSettingMenuCallBack()
	@param:		no
	@return:	void
	@brief:		Exit SettingMenu, then todo ...
	*/
	/************************************************************************/
	virtual void	OnEixtSettingMenuCallBack(Object* pSender, Control::EventType event);


};

#endif
