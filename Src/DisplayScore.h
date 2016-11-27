/************************************************************************/
/* 
arthur:		cqf
date:		20161127
version:	1.0
brief:		display actor current score
*/
/************************************************************************/
#ifndef _DISPLAY_SCORE_
#define _DISPLAY_SCORE_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ActorBase.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CDisplayScore:
	public Layer
{
public:
	CDisplayScore();
	~CDisplayScore();

	virtual bool init();

	static	CDisplayScore* CreateDisplayScoreLabel(const char* szPng, CActorBase* pActor);
	bool	initScore(const char* szPng, CActorBase* pActor);
	void	Release();

	/************************************************************************/
	/*
	//update entity score
	*/
	/************************************************************************/

	void	UpdateEntityScore();

private:
	Label*				m_pScoreLabel;
	CActorBase*			m_pActor;
};

#endif // 


