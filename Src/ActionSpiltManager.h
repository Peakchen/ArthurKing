/************************************************************************/
/* 
@arthor:	StefanChen
@date:		20161029
@version:	1.0
@brief:		the last step msg mmanage
*/
/************************************************************************/
#ifndef __ACTIVE_MSG_
#define __ACTIVE_MSG_

#pragma once
#include "TileBase.h"

class CActionSpiltManager
{
public:
	CActionSpiltManager();
	~CActionSpiltManager();


	/************************************************************************/
	/* 
	@func:		CreateALiveMsg
	@param:		no
	@return:	void
	@brief:		create many msgs, which are stored in map
	*/
	/************************************************************************/

	void CreateALiveMsg();

	/************************************************************************/
	/* 
	@func:		CreateALiveMsg
	@param:		no
	@return:	void
	@brief:		remove all msgs, which are in map
	*/
	/************************************************************************/
	void ReleaseAliveMsg();

	/************************************************************************/
	/* 
	@func:		GetSplitHandlerMap
	@param:		no
	@return:	TSPLITHANDLERMAP*
	@brief:		get SH map
	*/
	/************************************************************************/
	TSPLITHANDLERMAP* GetSplitHandlerMap(){ return &m_mapSH; }

private:

	/************************************************************************/
	/*
	@func:		AddLiveMsg
	@param:		IArthurActionSpiltHandler* pSH
	@return:	void
	@brief:		you can add one SH into map
	*/
	/************************************************************************/
	void AddLiveMsg(CTileBase* pSH);

	/************************************************************************/
	/*
	@func:		RemoveLiveMsg
	@param:		IArthurActionSpiltHandler* pSH
	@return:	void
	@brief:		you can remove one SH from map
	*/
	/************************************************************************/
	void RemoveLiveMsg(CTileBase* pSH);

private:

	TSPLITHANDLERMAP m_mapSH;
};

extern CActionSpiltManager g_ActionSpiltManager;

#endif