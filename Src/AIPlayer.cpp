#include "AIPlayer.h"
#include "ResCreator.h"


CAIPlayer::CAIPlayer ( )
{
	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(ACTOR_START, this, "½ÇÉ«¶¯×÷");
}


CAIPlayer::~CAIPlayer ( )
{
}

void CAIPlayer::OnExecMessageHandle ( DWORD nMsgID, LPCSTR szDesc )
{
	switch (nMsgID)
	{
		case ACTOR_START:
			{

			}
			break;
		default:
			CCLOG ( "error: %s message is wrong...", __FUNCTION__);
			break;
	}
}

void CAIPlayer::OnEnter ( )
{

}

void CAIPlayer::OnLeave ( )
{
	
}

CAIPlayer* CAIPlayer::CreateAIPlayer ( SpriteFrame* pFrame )
{
	CAIPlayer* pAi = new CAIPlayer();

	if (pAi && pAi->initWithSpriteFrame ( pFrame ))
	{
		pAi->autorelease ( );
		return pAi;
	}

	CC_SAFE_DELETE ( pAi );
	return NULL;
}
