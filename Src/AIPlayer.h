
#ifndef _CAI_PLAYER_
#define _CAI_PLAYER_

#pragma once

#include "cocos2d.h"
#include "PersonMessageEventHandle.h"
#include "ActorBase.h"

USING_NS_CC;

class CAIPlayer :
	public CActorBase,
	public IAIPersonMessageSink	
{
public:
	CAIPlayer ( );
	~CAIPlayer ( );

	/************************************************************************/
	/* 
		IAIPersonMessageSink 
	*/
	/************************************************************************/

	virtual void  OnExecMessageHandle ( DWORD nMsgID, LPCSTR szDesc );

	/************************************************************************/
	/*
	CActorBase:

	OnEnter()
	*/
	/************************************************************************/
	virtual void OnEnter ( );

	/************************************************************************/
	/*
	CActorBase:

	OnLeave()
	*/
	/************************************************************************/
	virtual void OnLeave ( );

	/***************************
	* func: Create ai
	* param: strName is picture' name
	* return: void
	*************************/
	static CAIPlayer* CreateAIPlayer ( SpriteFrame* pFrame );

private:

};

#endif