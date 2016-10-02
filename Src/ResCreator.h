#pragma once

/************************************************************************/
/* 
author: StefanChen
date: 20161001
version: 1.0
*/
/************************************************************************/

#ifndef _RES_CREATOR_
#define _RES_CREATOR_


#include "FloatingHead.h"
#include "MapReader.h"
#include "ArthurKingControl.h"

class CResCreator
{
public:
	CResCreator();
	~CResCreator();

	/************************************************************************/
	/* 
		func: GetFloatingHeadInstance
		Desc: get Float Head Instace to get ... its funcs
		param: No
		return : CFloatingHead*
	*/
	/************************************************************************/
	CFloatingHead* GetFloatingHeadInstance(){ return &m_oFloatingHead; }

	/************************************************************************/
	/* 
		func: GetMapReaderInstance
		Desc: get Map Data Instace to get ... its funcs
		param: No
		return : CMapReader*
	*/
	/************************************************************************/
	CMapReader* GetMapReaderInstance(){ return &m_oMapReader; }

	/************************************************************************/
	/* 
		func: GetMapReaderInstance
		Desc: get Map Data Instace to get ... its funcs
		param: No
		return : CMapReader*
	*/
	/************************************************************************/
	CArthurKingControl* GetActorCtrlInstance(){ return	&m_oActorCtrl; }

private:
	
	/************************************************************************/
	/* 
		Float Head
	*/
	/************************************************************************/
	CFloatingHead m_oFloatingHead;
	
	/************************************************************************/
	/* 
		Map
	*/
	/************************************************************************/
	CMapReader m_oMapReader;

	/************************************************************************/
	/* 
		player Ctrl
	*/
	/************************************************************************/
	CArthurKingControl m_oActorCtrl;
};

extern CResCreator g_ResCreator;

#endif