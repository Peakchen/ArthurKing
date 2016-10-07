#include "ArthurKing.h"
#include "ConstUtil.h"
#include "MapReader.h"
#include "ArthurKingControl.h"
#include "ResCreator.h"

USING_NS_CC;

CArthurKing::CArthurKing()
{
	m_ActorScore = 0;
	m_pCtrl = NULL;

	m_bCheckActorRuning = false;
	m_bActorRunDirector = false;
	m_pActorSprite = NULL;
	m_szSpriteName = NULL;

	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(AI_START, this, "½ÇÉ«¶¯×÷");
}


CArthurKing::~CArthurKing()
{
}

CArthurKing* CArthurKing::CreateArthurKing(SpriteFrame* pFrame)
{
	CArthurKing* pArthur = new CArthurKing();

	if (pArthur && pArthur->initWithSpriteFrame(pFrame))
	{
		pArthur->autorelease();
		return pArthur;
	}

	CC_SAFE_DELETE(pArthur);
	return NULL;
}


bool CArthurKing::init()
{
	return true;
}

void CArthurKing::RequestActorCtrl()
{
	
	m_pCtrl = CArthurKingControl::create();
	if (m_pCtrl == NULL)
	{
		return;
	}
	
	addChild(m_pCtrl);

	m_pCtrl->InitData(m_passRowPath, m_passColPath, this);
}

void CArthurKing::PlayStartGo()
{
	m_pCtrl->StartActorGo();
}

void CArthurKing::UpdateScoreItem ( int addScore )
{
	m_ActorScore += addScore;
}

void CArthurKing::OnEnter ( )
{
	
}

void CArthurKing::OnLeave ( )
{
	
}

void CArthurKing::OnExecMessageHandle ( DWORD nMsgID, LPCSTR szDesc )
{
	switch (nMsgID)
	{
		case AI_START:
			{

			}
			break;
		default:
			CCLOG ( "error: %s message is wrong...", __FUNCTION__ );
			break;
	}
}
