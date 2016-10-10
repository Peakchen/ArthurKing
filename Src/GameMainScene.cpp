#include "GameMainScene.h"
#include "MacroDefine.h"
#include "MapReader.h"
#include "ConstUtil.h"
#include "CardSprite.h"
#include "ResCreator.h"
#include "base\ccMacros.h"
#include "AIPlayer.h"
#include "PlayerManager.h"

USING_NS_CC;

bool CGameMainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_pCurAction = NULL;
	m_pAIplayer = NULL;
	m_pArthurKing = NULL;

	g_ResCreator.GetPersonMessageInstance()->ResetData();

	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(ACTOR_START, this, "player action");
	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(AI_START, this, "AI action");

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	pCallFunc_AfterOpen = CallFunc::create(CC_CALLBACK_0(CGameMainScene::AfterOpenCard, this));

	AddSceneMap();

	AddButton_Test();
	//initMainLayout();

	InitPlayerAnimation();
	addPlayer();
	addAI();

	g_PalyerManager.Create(m_pCurAction);

	return true;
}

Scene* CGameMainScene::createMainScene()
{
	auto scene = Scene::create();
	auto layer = CGameMainScene::create();
	scene->addChild(layer);
	return scene;
}

void CGameMainScene::AddSceneMap()
{
	Scene* pMapReaderScene = CMapReader::createMapReaderScene();
	addChild(pMapReaderScene);

	//m_pMapReader = CMapReader::getMapReaderInstance();
	//m_pMapReader->initMainLayer();
}

void CGameMainScene::AddSetItem()
{

}

void CGameMainScene::AddButton_Test()
{
	Scale9Sprite* pNormal_Scale = Scale9Sprite::create(GO_NORMAL);
	Scale9Sprite* pPress_Scale = Scale9Sprite::create(GO_PRESS);

	if (pNormal_Scale == NULL || pPress_Scale == NULL)
	{
		CCLOG("%s error :  create ScaleSprite....", __FUNCTION__);
		return;
	}

	LabelTTF* pGoTTF = LabelTTF::create("", FONT_MENU, 20);
	if (pGoTTF == NULL)
	{
		CCLOG("error: %s create LabelTTF...", __FUNCTION__);
		return;
	}

	ControlButton* pBtn_Go = ControlButton::create(pGoTTF, pNormal_Scale);
	pBtn_Go->setBackgroundSpriteForState(pPress_Scale, Control::State::SELECTED);
	pBtn_Go->addTargetWithActionForControlEvents(this, cccontrol_selector(CGameMainScene::onClick_StartControl), Control::EventType::TOUCH_DOWN);
	pBtn_Go->setPreferredSize(Size(82, 82));
	pBtn_Go->setPosition(ccp(visibleSize.width / 2 - 250 , visibleSize.height - 50));
	pBtn_Go->setTag(ESTART_TEST);
	/*pBtn_Go->setScale(0.6f);*/
	addChild(pBtn_Go);

	
}

/************************************************************************/
/* func�� Go���ߣ����ֿ��ƣ��˴��ص�Ϊ �������ƴ�

*/
/************************************************************************/
int schedule_count = 0;
void CGameMainScene::onClick_StartControl(Object* pSender, Control::EventType event)
{
	TurnToGoAction(pSender, event);
}

/************************************************************************/
/* func: ʵ�� ���� �������
		���һ�� ������죬���������Ϊ0 �����
*/
/************************************************************************/
int CGameMainScene::GetRandomNum(int Randsize)
{
	timeval psv;
	cocos2d::gettimeofday(&psv, NULL);    // ����ʱ������   
	unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000;    // ��ʼ�������   
	srand(tsrans);

	int arr_seq[RADN_COUNT] = { 0 };
	int arr_RandResult[RADN_COUNT] = {0};
	int iSub = RADN_COUNT - 1;

	for (int i = 0; i < RADN_COUNT; ++i)
	{
		int iRandom = CCRANDOM_0_1()*Randsize + 1;
		CCLOG("rand num: %d ",iRandom);
		arr_seq[i] = iRandom;
		arr_RandResult[i] = iRandom;
	}

	for (int index = 0; index < RADN_COUNT; ++index)
	{
		int iRandom = CCRANDOM_0_1()*Randsize + 1;
		arr_RandResult[index] = arr_seq[iRandom];
		CCLOG("arr_RandResult num: %d ", arr_RandResult[index]);
		arr_seq[iRandom] = arr_seq[iSub];
		--iSub;
	}

	int iendIndex = CCRANDOM_0_1()*RADN_COUNT;

	CCLOG("Result num: %d ", arr_RandResult[iendIndex]);
	return arr_RandResult[iendIndex];
}

/************************************************************************/
/* func�� ʵ���յ���˸                                                                     */
/************************************************************************/
void CGameMainScene::AddFadeSprite_Test()
{
	if (getChildByTag(EFADESPRITE_TEST))
	{
		removeChildByTag(EFADESPRITE_TEST);
	}

	Sprite* pPointSprite = Sprite::create("Direction_bt.png");
	if (pPointSprite == NULL)
	{
		CCLOG("ERROR: %s ���� ��˸����ʧ��...", __FUNCTION__);
		return;
	}

	pPointSprite->setPosition(ccp(visibleSize.width / 2 - 250, visibleSize.height - 200));
	pPointSprite->setAnchorPoint(ccp(0, 0));
	pPointSprite->setTag(EFADESPRITE_TEST);
	addChild(pPointSprite);
	
	CCActionInterval* pBlink = CCBlink::create(3, 3);
	if (pBlink == NULL)
	{
		return;
	}

	pPointSprite->runAction(pBlink);

	/*FadeIn* pPointIn = FadeIn::create(0.3f);
	FadeOut* pPointOut = FadeOut::create(0.3f);
	if (pPointIn == NULL || pPointOut == NULL)
	{
		CCLOG("error: %d ���뵭��Ч�� �Ƿ�...", __FUNCTION__);
		return;
	}
	this->runAction(Sequence::create(pPointOut, DelayTime::create(3.0f), pPointIn, DelayTime::create(3.0f), pPointOut, NULL));*/
}

void CGameMainScene::addPlayer()
{
	SpriteFrame* pInitPlayFrame = m_pPlayer_1_FrameCache->getSpriteFrameByName(player_1_01);
	if (pInitPlayFrame == NULL)
	{
		CCLOG("error: %s ȡ�þ����ʧ��...", __FUNCTION__);
		return;
	}

	m_pArthurKing = CArthurKing::CreateArthurKing(pInitPlayFrame);
	if (m_pArthurKing == NULL)
	{
		CCLOG("error�� ��ǰ��ɫ����ʧ��.");
		return;
	}

	std::vector<Vec2>* pstVecMap = g_MapReader.GetGoPathMap();
	int iPathSize = pstVecMap->size();
	if (iPathSize == 0)
	{
		CCLOG("error��ȡ��·��Ϊ0..");
		return;
	}
	//int iRand = GetRandomNum(iPathSize);
	Vec2 vec2_p1 = pstVecMap->front();

	CCLOG("Random Map x: %02f , y: %02f", vec2_p1.x, vec2_p1.y);

	vec2_p1.y += TILE_HEIGHT/5;
	//vec2_p1.x += TILE_HEIGHT/2;

	CCLOG("After player1 vec2_p1 x: %.2f , vec2_p1 y: %.2f", vec2_p1.x, vec2_p1.y);

	int iCol = (int)vec2_p1.y/TILE_HEIGHT;
	int iRow = (int)vec2_p1.x/TILE_WIDTH;
	m_pArthurKing->setPosition(vec2_p1);

	CCLOG("player1 x: %d , y: %d", iRow, iCol);

	m_pArthurKing->setAnchorPoint(ccp(0, 0));
	addChild(m_pArthurKing);

	m_pArthurKing->setvecAnim_down(m_vecPlayer_down);
	m_pArthurKing->setvecAnim_Left(m_vecPlayer_left);
	m_pArthurKing->setvecAnim_Right(m_vecPlayer_right);
	m_pArthurKing->setvecAnim_up(m_vecPlayer_up);

	m_pCurAction = m_pArthurKing;
}

void CGameMainScene::GetAnimateVec(int iMin, int iMax, TVecSpriteFrame &vecPlayer_director, EPlayer iState)
{
	char szPngName[15];
	memset(szPngName, 0, sizeof(szPngName));

	switch (iState)
	{
	case EFirstPlayer:
	{
		for (int idex = iMin; idex <= iMax; ++idex)
		{
			sprintf(szPngName, "p_%d.png", idex);
			std::string strName = szPngName;
	
			SpriteFrame* pSpriteFrame = m_pPlayer_1_FrameCache->getSpriteFrameByName(strName);
			if (pSpriteFrame == NULL)
			{
				continue;
			}
			vecPlayer_director.pushBack(pSpriteFrame);
		}
	}
		break;
	case ESecondPlayer:
		{
			for (int idex = iMin; idex <= iMax; ++idex)
			{
				sprintf ( szPngName, "p_2_%d.png", idex );
				std::string strName = szPngName;
				SpriteFrame* pSpriteFrame = m_pPlayer_2_FrameCache->getSpriteFrameByName(strName);
				if (pSpriteFrame == NULL)
				{
					continue;
				}
				vecPlayer_director.pushBack ( pSpriteFrame );
			}
		}
		break;
	default:
		break;
	}
	
}

void CGameMainScene::InitPlayerAnimation()
{
	m_pPlayer_1_FrameCache = SpriteFrameCache::getInstance();
	m_pPlayer_1_FrameCache->addSpriteFramesWithFile(player_1_list, player_1_png);

	// ��ɫ�ĸ����� ֵ
	
	GetAnimateVec(1, 4, m_vecPlayer_down, EFirstPlayer);
	GetAnimateVec(5, 8, m_vecPlayer_left, EFirstPlayer);
	GetAnimateVec(9, 12, m_vecPlayer_right, EFirstPlayer);
	GetAnimateVec(13, 16, m_vecPlayer_up, EFirstPlayer);

	// ��ʼ���ĸ�������
	Animation* pPlayer_1_Animation_down = Animation::createWithSpriteFrames(m_vecPlayer_down, 0.1f);
	Animation* pPlayer_1_Animation_left = Animation::createWithSpriteFrames(m_vecPlayer_left, 0.1f);
	Animation* pPlayer_1_Animation_right = Animation::createWithSpriteFrames(m_vecPlayer_right, 0.1f);
	Animation* pPlayer_1_Animation_up = Animation::createWithSpriteFrames(m_vecPlayer_up, 0.1f);

	if (pPlayer_1_Animation_down == NULL || pPlayer_1_Animation_left == NULL ||
		pPlayer_1_Animation_right == NULL || pPlayer_1_Animation_up == NULL)
	{
		CCLOG("error: %s, ��ɫ%d ���򴴽�ʧ��...", __FUNCTION__, EFirstPlayer);
		return;
	}

	m_Pplayer_animate_down = Animate::create(pPlayer_1_Animation_down);
	m_Pplayer_animate_left = Animate::create(pPlayer_1_Animation_left);
	m_Pplayer_animate_up = Animate::create(pPlayer_1_Animation_up);
	m_Pplayer_animate_right = Animate::create(pPlayer_1_Animation_right);
	
	///////////////////////////////////////////Create AI animatio //////////////////////////////////////////////////////

	m_pPlayer_2_FrameCache = SpriteFrameCache::getInstance ( );
	m_pPlayer_2_FrameCache->addSpriteFramesWithFile ( player_2_list, player_2_png );

	// ��ɫ�ĸ����� ֵ

	GetAnimateVec ( 1, 4, m_vecPAI_down, ESecondPlayer );
	GetAnimateVec ( 5, 8, m_vecPAI_left, ESecondPlayer );
	GetAnimateVec ( 9, 12, m_vecPAI_right, ESecondPlayer );
	GetAnimateVec ( 13, 16, m_vecPAI_up, ESecondPlayer );

	// ��ʼ���ĸ�������
	Animation* pPlayer_2_Animation_down = Animation::createWithSpriteFrames ( m_vecPAI_down, 0.1f );
	Animation* pPlayer_2_Animation_left = Animation::createWithSpriteFrames ( m_vecPAI_left, 0.1f );
	Animation* pPlayer_2_Animation_right = Animation::createWithSpriteFrames ( m_vecPAI_right, 0.1f );
	Animation* pPlayer_2_Animation_up = Animation::createWithSpriteFrames ( m_vecPAI_up, 0.1f );

	if (pPlayer_2_Animation_down == NULL || pPlayer_2_Animation_left == NULL ||
		 pPlayer_2_Animation_right == NULL || pPlayer_2_Animation_up == NULL)
	{
		CCLOG ( "error: %s, ��ɫ%d ���򴴽�ʧ��...", __FUNCTION__, ESecondPlayer );
		return;
	}

	m_PAI_animate_down = Animate::create ( pPlayer_2_Animation_down );
	m_PAI_animate_left = Animate::create ( pPlayer_2_Animation_left );
	m_PAI_animate_up = Animate::create ( pPlayer_2_Animation_up );
	m_PAI_animate_right = Animate::create ( pPlayer_2_Animation_right );

}

void CGameMainScene::AfterOpenCard()
{
	// ȡ��·����������� ��ɫ����
	if (m_pCurAction == NULL || m_CurRandNum == 0)
	{
		return;
	}

	m_pCurAction->GetPlayerGoPath(m_CurRandNum, g_MapReader.GetCanGoPathArr());
	m_pCurAction->RequestActorCtrl();

	// ���ĺ� ��ʾ ����
	
	BeginFloatHead();

	// ����
	
	BeginActorGo();
}

int sche_aboutScore = 0;
Vec2 g_Point;
void CGameMainScene::BeginFloatHead()
{
	// ���� �ж��Ƿ��ܹ� Ʈ��
	m_CurPalyer_Socre = 0;
	std::vector<int>  vecRow = g_ResCreator.GetActorCtrlInstance()->getRecordPassRowPath();
	if (vecRow.empty())
	{
		return;
	}

	std::vector<int>  vecCol = g_ResCreator.GetActorCtrlInstance()->getRecordPassColPath();
	if (vecCol.empty())
	{
		return;
	}

	int iRow = vecRow.back();
	int iCol = vecCol.back();
	
	float y = (float)1.0f * iRow * TILE_WIDTH;
	float x = (float)1.0f * iCol * TILE_HEIGHT;

	g_Point = Vec2(x, y);
	if (!g_ResCreator.GetMapReaderInstance()->CheckCanTakeAddSocre(m_CurPalyer_Socre, g_Point))
	{
		return;
	}

	// ִ��Ʈ�ֲ���
	sche_aboutScore = 0;
	schedule([this](float dt){
		sche_aboutScore += dt;
		if (sche_aboutScore >= 2)
		{
			unschedule("AfterOpen_Score");
		}

		std::string szMsg = String::createWithFormat("+%d", m_CurPalyer_Socre)->getCString();
		g_ResCreator.GetFloatingHeadInstance()->createFloatingHead(this, szMsg, 3.0f, g_Point);
	}
	, 5.0f, 1, 0.0f, "AfterOpen_Score");
}

void CGameMainScene::BeginActorGo()
{
	schedule_count = 0;
	schedule([this](float dt){

		CCLOG("BeginActorGo: schedule  dt = %02f", dt);
		schedule_count += dt;
		if (schedule_count >= 1)
		{
			unschedule("AfterOpen_Close");
		}

		m_pCurAction->PlayStartGo();

	}
	, 5.0f, 1, 0.0f, "AfterOpen_Close");
}

void CGameMainScene::addAI ( )
{
	SpriteFrame* pInitPlayFrame = m_pPlayer_2_FrameCache->getSpriteFrameByName ( player_2_01 );
	if (pInitPlayFrame == NULL)
	{
		CCLOG ( "error: %s ȡ�þ����ʧ��...", __FUNCTION__ );
		return;
	}

	m_pAIplayer = CAIPlayer::CreateAIPlayer ( pInitPlayFrame );
	if (m_pAIplayer == NULL)
	{
		CCLOG ( "error�� ��ǰAI����ʧ��." );
		return;
	}

	std::vector<Vec2>* pstVecMap = g_MapReader.GetGoPathMap ( );
	int iPathSize = pstVecMap->size ( );
	if (iPathSize == 0)
	{
		CCLOG ( "error��ȡ��·��Ϊ0.." );
		return;
	}

	int index = CCRANDOM_0_1()*iPathSize;
	while (index == 0)
	{
		index = CCRANDOM_0_1()*iPathSize;
	}

	Vec2 vec2_aiMap = pstVecMap->at(index);

	CCLOG ( "Random Map x: %02f , y: %02f", vec2_aiMap.x, vec2_aiMap.y );

	vec2_aiMap.y += TILE_HEIGHT / 5;
	//vec2_p1.x += TILE_HEIGHT/2;

	CCLOG ( "After AI vec2_p1 x: %.2f , vec2_p1 y: %.2f", vec2_aiMap.x, vec2_aiMap.y );

	int iCol = ( int ) vec2_aiMap.y / TILE_HEIGHT;
	int iRow = ( int ) vec2_aiMap.x / TILE_WIDTH;
	m_pAIplayer->setPosition(vec2_aiMap);

	CCLOG ( "AI x: %d , y: %d", iRow, iCol );

	m_pAIplayer->setAnchorPoint ( ccp ( 0, 0 ) );
	addChild ( m_pAIplayer );

	m_pAIplayer->setvecAnim_down ( m_vecPAI_down );
	m_pAIplayer->setvecAnim_Left ( m_vecPAI_left );
	m_pAIplayer->setvecAnim_Right ( m_vecPAI_right );
	m_pAIplayer->setvecAnim_up ( m_vecPAI_up );
}

void CGameMainScene::OnExecMessageHandle(DWORD nMsgID, LPCSTR szDesc)
{
	switch (nMsgID)
	{
		case ACTOR_START:
			{
				// ���ƣ� ��·...
				m_pCurAction = m_pArthurKing;
				CCLOG("-----------------------------player go ---------------------------");
			}
			break;

		case AI_START:
			{
				// �Զ����ƣ� ��·...
				m_pCurAction = m_pAIplayer;
				CCLOG("-----------------------------ai go ---------------------------");
			}
			break;
		default:
			CCLOG("error: %s message is wrong...", __FUNCTION__);
			break;
	}

	TurnToGoAction(NULL, Control::EventType::TOUCH_DOWN);
}

void CGameMainScene::TurnToGoAction(Object* pSender, Control::EventType event)
{
	if (getChildByTag(ECARD_TEST))
	{
		removeChildByTag(ECARD_TEST);
	}

	//AddFadeSprite_Test();
	m_CurRandNum = 0;
	/*if (event == Control::EventType::TOUCH_DOWN)
	{*/
		int iRandom = GetRandomNum(KAPAI_COUNT);
		const char* strInCard = CCString::createWithFormat("kapai/k_%d.png", iRandom)->getCString();
		CCardSprite* pCardSprite = CCardSprite::create(strInCard, FACE_KAPAI, 5.0f);
		if (pCardSprite)
		{
			pCardSprite->setTag(ECARD_TEST);
			addChild(pCardSprite);
		}

		m_CurRandNum = iRandom;
		//// ���ĺ� ����
		schedule_count = 0;
		AfterOpenCard();
	//}
}
