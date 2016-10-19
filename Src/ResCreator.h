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
#include "PersonMessageEventHandle.h"
#include "BuySeaBarAction.h"
#include "GiveTipAction.h"
#include "SellSeaBarAction.h"


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

	/************************************************************************/
	/* 
		func: GetPersonMessageInstance
		Desc: get Player Message Instance , to ... 
		param: No
		date: 20161007
		return : CPersonMessageEventHandle*
	*/
	/************************************************************************/
	CPersonMessageEventHandle* GetPersonMessageInstance ( ){ return &m_oPersonMessageHandle; }

	/************************************************************************/
	/* 
	func: GetBuySeaBarActionInstance
	Desc: get Buy SeaBar ActionInstance , toDO
	param: No
	date: 20161018
	return : CBuySeaBarAction*
	*/
	/************************************************************************/
	CBuySeaBarAction*			GetBuySeaBarActionInstance(){ return&m_oBuySeaBarAction; }

	/************************************************************************/
	/*
	func: GetGiveTipInstance
	Desc: get Give Tip to SeaBar's owner ActionInstance , toDO...
	param: No
	date: 20161019
	return : CGiveTipAction*
	*/
	/************************************************************************/
	CGiveTipAction*				GetGiveTipInstance(){ return &m_oGiveTipAction; }

	/************************************************************************/
	/*
	func: GetSellSeaBarInstance
	Desc: get SellSeaBar ActionInstance , toDO...
	param: No
	date: 20161019
	return : CSellSeaBarAction*
	*/
	/************************************************************************/
	CSellSeaBarAction*			GetSellSeaBarInstance(){ return &m_oSellSeaBarAction; }

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

	/************************************************************************/
	/* 
		Player Event Message
	*/
	/************************************************************************/
	CPersonMessageEventHandle m_oPersonMessageHandle;

	CBuySeaBarAction	m_oBuySeaBarAction;
	CGiveTipAction		m_oGiveTipAction;
	CSellSeaBarAction	m_oSellSeaBarAction;
};

extern CResCreator g_ResCreator;

#endif