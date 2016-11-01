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
#include "ActionSpiltManager.h"
#include "ExchangeSeaBarPopup.h"

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
	g_ResCreator.GetPersonMessageInstance()->RegisterAIMessage(SH_SEABAR_ACTION, this, "SH SEABAR action");

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

	g_ActionSpiltManager.CreateALiveMsg();

	g_PalyerManager.AddActorInstace(m_pArthurKing);
	g_PalyerManager.AddActorInstace(m_pAIplayer);

	//g_ResCreator.SetMainSceneInstance(this);

	return true;
}

Scene* CGameMainScene::createMainScene()
{
	auto scene = Scene::create();
	auto layer = CGameMainScene::create();
	scene->addChild(layer);
	return scene;

	/*CGameMainScene* pMainScene = new CGameMainScene();
	if (pMainScene)
	{
		pMainScene->autorelease();
		return pMainScene;
	}

	CC_SAFE_DELETE(pMainScene);
	return nullptr;*/
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
	pBtn_Go->setPosition(ccp(visibleSize.width/2 - 220, visibleSize.height - 50));
	pBtn_Go->setTag(ESTART_Go);
	/*pBtn_Go->setScale(0.6f);*/
	addChild(pBtn_Go);

}

/************************************************************************/
/* func： Go行走，出现卡牌，此处回调为 创建卡牌处

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
/* func： 实现终点闪烁                                                                     */
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
		CCLOG("ERROR: %s 创建 闪烁精灵失败...", __FUNCTION__);
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
		CCLOG("error: %d 淡入淡出效果 非法...", __FUNCTION__);
		return;
	}
	this->runAction(Sequence::create(pPointOut, DelayTime::create(3.0f), pPointIn, DelayTime::create(3.0f), pPointOut, NULL));*/
}

void CGameMainScene::addPlayer()
{
	SpriteFrame* pInitPlayFrame = m_pPlayer_1_FrameCache->getSpriteFrameByName(player_1_01);
	if (pInitPlayFrame == NULL)
	{
		CCLOG("error: %s 取得精灵层失败...", __FUNCTION__);
		return;
	}

	m_pArthurKing = CArthurKing::CreateArthurKing(pInitPlayFrame, EFirstPlayer);
	if (m_pArthurKing == NULL)
	{
		CCLOG("error： 当前角色创建失败.");
		return;
	}

	std::vector<Vec2>* pstVecMap = g_MapReader.GetGoPathMap();
	int iPathSize = pstVecMap->size();
	if (iPathSize == 0)
	{
		CCLOG("error：取得路径为0..");
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

	// 角色四个方向 值
	
	GetAnimateVec(1, 4, m_vecPlayer_down, EFirstPlayer);
	GetAnimateVec(5, 8, m_vecPlayer_left, EFirstPlayer);
	GetAnimateVec(9, 12, m_vecPlayer_right, EFirstPlayer);
	GetAnimateVec(13, 16, m_vecPlayer_up, EFirstPlayer);

	// 初始化四个方向动作
	Animation* pPlayer_1_Animation_down = Animation::createWithSpriteFrames(m_vecPlayer_down, 0.1f);
	Animation* pPlayer_1_Animation_left = Animation::createWithSpriteFrames(m_vecPlayer_left, 0.1f);
	Animation* pPlayer_1_Animation_right = Animation::createWithSpriteFrames(m_vecPlayer_right, 0.1f);
	Animation* pPlayer_1_Animation_up = Animation::createWithSpriteFrames(m_vecPlayer_up, 0.1f);

	if (pPlayer_1_Animation_down == NULL || pPlayer_1_Animation_left == NULL ||
		pPlayer_1_Animation_right == NULL || pPlayer_1_Animation_up == NULL)
	{
		CCLOG("error: %s, 角色%d 方向创建失败...", __FUNCTION__, EFirstPlayer);
		return;
	}

	m_Pplayer_animate_down = Animate::create(pPlayer_1_Animation_down);
	m_Pplayer_animate_left = Animate::create(pPlayer_1_Animation_left);
	m_Pplayer_animate_up = Animate::create(pPlayer_1_Animation_up);
	m_Pplayer_animate_right = Animate::create(pPlayer_1_Animation_right);
	
	///////////////////////////////////////////Create AI animatio //////////////////////////////////////////////////////

	m_pPlayer_2_FrameCache = SpriteFrameCache::getInstance();
	m_pPlayer_2_FrameCache->addSpriteFramesWithFile ( player_2_list, player_2_png );

	// 角色四个方向 值

	GetAnimateVec(1, 4, m_vecPAI_down, ESecondPlayer);
	GetAnimateVec(5, 8, m_vecPAI_left, ESecondPlayer);
	GetAnimateVec(9, 12, m_vecPAI_right, ESecondPlayer);
	GetAnimateVec(13, 16, m_vecPAI_up, ESecondPlayer);

	// 初始化四个方向动作
	Animation* pPlayer_2_Animation_down = Animation::createWithSpriteFrames ( m_vecPAI_down, 0.1f );
	Animation* pPlayer_2_Animation_left = Animation::createWithSpriteFrames ( m_vecPAI_left, 0.1f );
	Animation* pPlayer_2_Animation_right = Animation::createWithSpriteFrames ( m_vecPAI_right, 0.1f );
	Animation* pPlayer_2_Animation_up = Animation::createWithSpriteFrames ( m_vecPAI_up, 0.1f );

	if (pPlayer_2_Animation_down == NULL || pPlayer_2_Animation_left == NULL ||
		 pPlayer_2_Animation_right == NULL || pPlayer_2_Animation_up == NULL)
	{
		CCLOG ( "error: %s, 角色%d 方向创建失败...", __FUNCTION__, ESecondPlayer );
		return;
	}

	m_PAI_animate_down = Animate::create ( pPlayer_2_Animation_down );
	m_PAI_animate_left = Animate::create ( pPlayer_2_Animation_left );
	m_PAI_animate_up = Animate::create ( pPlayer_2_Animation_up );
	m_PAI_animate_right = Animate::create ( pPlayer_2_Animation_right );

}

void CGameMainScene::AfterOpenCard()
{
	// 取得路径，请求控制 角色行走
	if (m_pCurAction == NULL || m_CurRandNum == 0)
	{
		return;
	}

	m_pCurAction->GetPlayerGoPath(m_CurRandNum, g_MapReader.GetCanGoPathArr());
	m_pCurAction->RequestActorCtrl();

	// 行走
	
	BeginActorGo();

	// 翻拍后 显示 分数

	BeginFloatHead();
}

int sche_aboutScore = 0;
Vec2 g_Point;
void CGameMainScene::BeginFloatHead()
{
	// 首先 判断是否能够 飘字
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

	float iRow = vecRow.back();
	float iCol = vecCol.back();
	
	float y = (float)1.0f*iRow * TILE_WIDTH;
	float x = (float)1.0f*iCol * TILE_HEIGHT;

	g_Point = Vec2(x, y);
	if (!g_PalyerManager.CheckCanTakeAddSocre(m_CurPalyer_Socre, g_Point))
	{
		return;
	}

	if (m_CurPalyer_Socre == 0)
	{
		return;
	}

	// 执行飘字操作
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
		CCLOG ( "error: %s 取得精灵层失败...", __FUNCTION__ );
		return;
	}

	m_pAIplayer = CAIPlayer::CreateAIPlayer ( pInitPlayFrame, ESecondPlayer );
	if (m_pAIplayer == NULL)
	{
		CCLOG ( "error： 当前AI创建失败." );
		return;
	}

	std::vector<Vec2>* pstVecMap = g_MapReader.GetGoPathMap ( );
	int iPathSize = pstVecMap->size ( );
	if (iPathSize == 0)
	{
		CCLOG ( "error：取得路径为0.." );
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
				// 翻牌， 走路...
				m_pCurAction = m_pArthurKing;

				m_bAiAutoOpen = false;
				CCLOG("-----------------------------player go ---------------------------");
			}
			break;

		case AI_START:
			{
				// 自动翻牌， 走路...
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
		case SH_SEABAR_ACTION:
			{
				CCLOG("-----------------------------SH seabar ---------------------------");

				OnEvent_DealWithSpiltActionCallBack();
				
			}
		default:
			CCLOG("error: %s message is wrong...", __FUNCTION__);
			break;
	}
	
	pCallFunc_CreateCard = CallFunc::create(CC_CALLBACK_0(CGameMainScene::TurnToGoAction, this));

	if (getChildByTag(ESTART_EXCHANGE))
	{
		CCLOG("event is existing..............................");
	}

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

	
	//// 翻拍后 行走
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

void CGameMainScene::OnEvent_DealWithSpiltActionCallBack()
{

	// get the data which is the last step  data
	Vec2 *pVecLastPoint = nullptr;
	if (!GetTheLastStepPoint(&pVecLastPoint))
	{
		CCLOG("error: %s get the last point  faild....", __FUNCTION__);
		return;
	}

	m_pstTileGridProperty = nullptr;
	if (!g_PalyerManager.CheckActionSplit(Vec2(pVecLastPoint->x, pVecLastPoint->y), m_pCurAction, true, &m_pstTileGridProperty))
	{
		CCLOG("action split is faild....");
	}

	// then open pop up

	CExchangeSeaBarPopup* pExchangePopup = CExchangeSeaBarPopup::CreateExchangeSeaBarPopup();
	if (!pExchangePopup)
	{
		return;
	}

	pExchangePopup->setTag(ESTART_EXCHANGE);
	addChild(pExchangePopup);
}

bool CGameMainScene::GetTheLastStepPoint(Vec2 **point)
{
	std::vector<int>  vecRow = g_ResCreator.GetActorCtrlInstance()->getRecordPassRowPath();
	if (vecRow.empty())
	{
		return false;
	}

	std::vector<int>  vecCol = g_ResCreator.GetActorCtrlInstance()->getRecordPassColPath();
	if (vecCol.empty())
	{
		return false;
	}

	float iRow = vecRow.back();
	float iCol = vecCol.back();

	float y = ( float )1.0f*iRow * TILE_WIDTH;
	float x = ( float )1.0f*iCol * TILE_HEIGHT;

	*point = &Vec2(x, y);
	return true;
}


//bool CGameMainScene::CheckActionSplit(Vec2 opint, CActorBase* pActor)
//{
//	CCLOG("func:%s  Dest: x = %02f,   y = %02f ", __FUNCTION__, opint.x, opint.y);
//	ValueVector vecArray = g_ResCreator.GetMapReaderInstance()->getVecObjectPath();
//
//	ValueVector::iterator itBegin = vecArray.begin();
//	for (; itBegin != vecArray.end(); ++itBegin)
//	{
//		ValueMap  mapObject = itBegin->asValueMap();
//
//		//CCLOG("value: %d, %s", mapObject.size(), mapObject ["name"]);
//		float x = mapObject ["x"].asFloat();
//		float y = mapObject ["y"].asFloat();
//
//		Vec2 vecPoint = Vec2(x, y);
//
//		Vec2 vecPoint1 = Vec2(x + 1, y + 1);
//		Vec2 vecPoint2 = Vec2(x + 1, y);
//		Vec2 vecPoint3 = Vec2(x, y + 1);
//
//		Vec2 vecPoint4 = Vec2(x - 1, y - 1);
//		Vec2 vecPoint5 = Vec2(x - 1, y);
//		Vec2 vecPoint6 = Vec2(x, y - 1);
//
//		//CCLOG("Src: x = %02f,   y = %02f ", x, y);
//
//		bool bFlag_x = ( fabs(opint.x - x) <= CoordinateDiff );
//		bool bFlag_y = ( fabs(opint.y - y) <= CoordinateDiff );
//		CCLOG("fabs: x = %02f,   y = %02f ", fabs(opint.x - x), fabs(opint.y - y));
//
//		if (bFlag_x && bFlag_y)
//		{
//			TSPLITHANDLERMAP* pSplitAction = g_ActionSpiltManager.GetSplitHandlerMap();
//			if (pSplitAction->empty() || pActor == nullptr)
//			{
//				return false;
//			}
//
//			string szName = mapObject ["name"].asString();
//			string szType = mapObject ["Type"].asString();
//			TSPLITHANDLERMAP::iterator it = pSplitAction->find(szName);
//			if (it != pSplitAction->end())
//			{
//				TTileLayerGridProperty oTileGridPeperty;
//				__GetTileContextByName(szName, &oTileGridPeperty, mapObject);
//
//				g_PalyerManager.RemoveActorInstace(pActor->GetPDBID());
//
//				//CTileBase* pSpiltHandler = it->second;
//
//				//g_ResCreator.GetMainSceneInstance()->DealWithSpiltActionCallBack();
//				//DealWithSpiltActionCallBack(pSpiltHandler, &oTileGridPeperty, pActor, g_PalyerManager.GetActorMap());
//				it->second->CheckCurrentAction(&oTileGridPeperty, pActor, g_PalyerManager.GetActorMap());
//				return true;
//			}
//			else
//			{
//				CCLOG("no find this location....");
//			}
//			return false;
//		}
//	}
//
//	return false;
//}
//
//void CGameMainScene::__GetTileContextByName(string szName, TTileLayerGridProperty *pTileContext, ValueMap mapObject)
//{
//	pTileContext->szName = mapObject ["name"].asString();
//	pTileContext->szType = mapObject ["Type"].asString();
//
//	if (szName == ETILELAYER_ONCEAGAIN)
//	{
//		return;
//	}
//	else if (szName == ETILELAYER_BLUE_DOUBLESTAR)
//	{
//		pTileContext->iTimes = mapObject ["times"].asInt();
//	}
//	else if (szName == ETILELAYER_BLUE_STAR)
//	{
//		pTileContext->iTimes = mapObject ["times"].asInt();
//		pTileContext->iScoreMult = mapObject ["ScoreMult"].asInt();
//	}
//	else if (szName == ETILELAYER_FOOT_BLUE)
//	{
//		pTileContext->iStopTimes = mapObject ["stoptimes"].asInt();
//	}
//	else if (szName == ETILELAYER_FOOT_RED)
//	{
//		pTileContext->iStopTimes = mapObject ["stoptimes"].asInt();
//	}
//	else if (szName == ETILELAYER_QUESTION)
//	{
//
//	}
//	else if (szName == ETILELAYER_RED_DOUBLESTAR)
//	{
//		pTileContext->iScoreMult = mapObject ["ScoreMult"].asInt();
//		pTileContext->iTimes = mapObject ["times"].asInt();
//	}
//	else if (szName == ETILELAYER_SCORE)
//	{
//		pTileContext->iScoreValue = mapObject ["value"].asInt();
//	}
//	else if (szName == ETILELAYER_SEABAR)
//	{
//		pTileContext->iSeaBarIndex = mapObject ["index"].asInt();
//		pTileContext->iSeaBarPrice = mapObject ["price"].asInt();
//		pTileContext->iSeaBarTip = mapObject ["tip"].asInt();
//	}
//	else if (szName == ETILELAYER_TUEN_FREE)
//	{
//		pTileContext->iTimes = mapObject ["times"].asInt();
//	}
//	else if (szName == ETILELAYER_YELLOW_STAR)
//	{
//		pTileContext->iTimes = mapObject ["times"].asInt();
//	}
//}
