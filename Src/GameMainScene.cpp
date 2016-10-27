#include "GameMainScene.h"
#include "MacroDefine.h"
#include "MapReader.h"
#include "ConstUtil.h"
#include "CardSprite.h"
#include "ResCreator.h"
#include "base\ccMacros.h"
#include "AIPlayer.h"
#include "PlayerManager.h"
#include "GameToolAPI.h"
#include "SettingMenu.h"

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

	m_bAiAutoOpen = false;

	g_ResCreator.GetPersonMessageInstance()->ResetData();

	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(ACTOR_START, this, "player action");
	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(AI_START, this, "AI action");
	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(OpenCard_Action, this, "Open Card action");

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	pCallFunc_AfterOpen = CallFunc::create(CC_CALLBACK_0(CGameMainScene::AfterOpenCard, this));

	AddSceneMap();

	AddButton_StartGoAction();
	//initMainLayout();

	InitPlayerAnimation();
	addPlayer();
	addAI();

	g_PalyerManager.Create(m_pCurAction);

	//g_GameToolAPI.CreateSeaBarRiseFallJsonFile(SEABAR_RISEFALL);

	AddButton_SettingMenu();

	// touch event
	this->setTouchEnabled(true);

	EventDispatcher* pEventDispatcher = Director::getInstance()->getEventDispatcher();
	if (pEventDispatcher != NULL)
	{
		auto pTouchOneByOne = EventListenerTouchOneByOne::create();
		if (pTouchOneByOne)
		{
			pTouchOneByOne->onTouchBegan		= CC_CALLBACK_2(CGameMainScene::onTouchBegan, this);
			pTouchOneByOne->onTouchMoved		= CC_CALLBACK_2(CGameMainScene::onTouchMoved, this);
			pTouchOneByOne->onTouchEnded		= CC_CALLBACK_2(CGameMainScene::onTouchEnded, this);
			pTouchOneByOne->onTouchCancelled	= CC_CALLBACK_2(CGameMainScene::onTouchCancelled, this);
			pEventDispatcher->addEventListenerWithSceneGraphPriority(pTouchOneByOne, this);

			pTouchOneByOne->setSwallowTouches(true);
		}
	}

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

void CGameMainScene::AddButton_StartGoAction()
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
	pBtn_Go->setPosition(ccp(visibleSize.width/2 - 250, visibleSize.height - 50));
	pBtn_Go->setTag(ESTART_Go);
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
	TurnToGoAction();

	ControlButton* pCtrlBtn = (ControlButton*)pSender;
	if (pCtrlBtn == NULL)
	{
		return;
	}

	pCtrlBtn->runAction(OrbitCamera::create(0.5f, 2.0f, 0.0f, 0.0f, 720.0f, 0.0f, 0.0f));

	pCtrlBtn->setVisible(false);
	pCtrlBtn->setEnabled(false);
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

	m_pArthurKing = CArthurKing::CreateArthurKing(pInitPlayFrame, EFirstPlayer);
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
	int iRand = g_GameToolAPI.GetRandomNum(iPathSize);
	Vec2 vec2_p1 = pstVecMap->at(iRand);

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

	m_pPlayer_2_FrameCache = SpriteFrameCache::getInstance();
	m_pPlayer_2_FrameCache->addSpriteFramesWithFile ( player_2_list, player_2_png );

	// ��ɫ�ĸ����� ֵ

	GetAnimateVec(1, 4, m_vecPAI_down, ESecondPlayer);
	GetAnimateVec(5, 8, m_vecPAI_left, ESecondPlayer);
	GetAnimateVec(9, 12, m_vecPAI_right, ESecondPlayer);
	GetAnimateVec(13, 16, m_vecPAI_up, ESecondPlayer);

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

	m_pAIplayer = CAIPlayer::CreateAIPlayer ( pInitPlayFrame, ESecondPlayer );
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

	int index = g_GameToolAPI.GetRandomNum(iPathSize);
	/*while (index == 0)
	{
	index = CCRANDOM_0_1()*iPathSize;
	}*/

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

void CGameMainScene::OnExecMessageHandle(GWORD nMsgID, LPCSTR szDesc)
{
	switch (nMsgID)
	{
		case ACTOR_START:
			{
				// ���ƣ� ��·...
				m_pCurAction = m_pArthurKing;

				m_bAiAutoOpen = false;
				CCLOG("-----------------------------player go ---------------------------");
			}
			break;

		case AI_START:
			{
				// �Զ����ƣ� ��·...
				m_pCurAction = m_pAIplayer;
				m_bAiAutoOpen = true;
				CCLOG("-----------------------------ai go ---------------------------");
			}
			break;

		case OpenCard_Action:
			{
				CCLOG("-----------------------------Open Card ---------------------------");
				AfterOpenCard();
				return;
			}
		default:
			CCLOG("error: %s message is wrong...", __FUNCTION__);
			break;
	}
	
	pCallFunc_CreateCard = CallFunc::create(CC_CALLBACK_0(CGameMainScene::TurnToGoAction, this));

	CCSequence* pSequence_CreateCard = CCSequence::create(
		CCDelayTime::create(3.5f),
		pCallFunc_CreateCard,
		//CCDelayTime::create(3.5f),
		NULL
		);
	
	if (pSequence_CreateCard)
	{
		this->runAction(pSequence_CreateCard);
	}
	
}

void CGameMainScene::TurnToGoAction()
{
	if (getChildByTag(ECARD_TEST))
	{
		removeChildByTag(ECARD_TEST);
	}

	//AddFadeSprite_Test();
	m_CurRandNum = 0;

	int iRandom = g_GameToolAPI.GetRandomNum(KAPAI_COUNT);
	if (iRandom == 0)
	{
		iRandom += 1;
	}

	m_CurRandNum = iRandom;
	schedule_count = 0;

	const char* strInCard = CCString::createWithFormat("kapai/k_%d.png", iRandom)->getCString();
	CCardSprite* pCardSprite = CCardSprite::create(strInCard, FACE_KAPAI, 5.0f, m_bAiAutoOpen);
	if (pCardSprite)
	{
		pCardSprite->setTag(ECARD_TEST);
		addChild(pCardSprite);
	}

	
	//// ���ĺ� ����
}

void CGameMainScene::onClick_StartShowSettingMenu(Object* pSender, Control::EventType event)
{
	Trace_In("%s is start ", __FUNCTION__);

	if (getChildByTag(ESTART_SETTINGMENU))
	{
		removeChildByTag(ESTART_SETTINGMENU);
	}
	
	CSettingMenu* pSettingMenu = CSettingMenu::create();
	pSettingMenu->setTag(ESTART_SETTINGMENU);
	addChild(pSettingMenu);
	
}

void CGameMainScene::AddButton_SettingMenu()
{
	Scale9Sprite* pNormal_Scale = Scale9Sprite::create(SETTING_MENU);

	if (pNormal_Scale == NULL)
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

	ControlButton* pBtn_SettingMenu = ControlButton::create(pGoTTF, pNormal_Scale);
	pBtn_SettingMenu->addTargetWithActionForControlEvents(this, cccontrol_selector(CGameMainScene::onClick_StartShowSettingMenu), Control::EventType::TOUCH_DOWN);
	pBtn_SettingMenu->setPreferredSize(Size(34, 34));
	pBtn_SettingMenu->setPosition(ccp(visibleSize.width - 50, visibleSize.height - 150));
	//pBtn_SettingMenu->setTag(ESTART_SETTINGMENU);
	/*pBtn_Go->setScale(0.6f);*/
	addChild(pBtn_SettingMenu, 128);
}

bool CGameMainScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	CCLOG("%s is starting -------------------------", __FUNCTION__);
	if (getChildByTag(ESTART_SETTINGMENU))
	{
		CSettingMenu* pMenu = static_cast<CSettingMenu*>( getChildByTag(ESTART_SETTINGMENU) );
		if (pMenu == nullptr)
		{
			return false;
		}

		pMenu->ccTouchBegan(touch, unused_event);

		return true;
	}

	return false;
}

void CGameMainScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	Trace_In("%s is starting -------------------------", __FUNCTION__);
}

void CGameMainScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	Trace_In("%s is starting -------------------------", __FUNCTION__);
}

void CGameMainScene::onTouchCancelled(Touch *touch, Event *unused_event)
{
	Trace_In("%s is starting -------------------------", __FUNCTION__);
}
