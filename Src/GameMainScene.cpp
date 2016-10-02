#include "GameMainScene.h"
#include "MacroDefine.h"
#include "MapReader.h"
#include "ConstUtil.h"
#include "CardSprite.h"
#include "ResCreator.h"
#include "base\ccMacros.h"

USING_NS_CC;

bool CGameMainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	pCallFunc_AfterOpen = CallFunc::create(CC_CALLBACK_0(CGameMainScene::AfterOpenCard, this));

	AddSceneMap();

	AddButton_Test();
	//initMainLayout();

	InitPlayerAnimation();
	addPlayer();

	return true;
}

Scene* CGameMainScene::createMainScene()
{
	auto scene = Scene::create();
	auto layer = CGameMainScene::create();
	scene->addChild(layer);
	return scene;
}

void CGameMainScene::initMainLayout()
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create(BgPicture);

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	m_pRockerAction = CRockerAction::CreateRockerEntity(Rocker_Point, Rocker_BG, ccp(110, 60));
	if (!m_pRockerAction)
	{
		CCLOG("创建 摇杆失败.");
		return;
	}
	this->addChild(m_pRockerAction, 2);
	m_pRockerAction->StartRockerAction(true);

	

	this->scheduleUpdate();
}

void CGameMainScene::update(float delta)
{
	CCLOG("frame begins update....");

	bool bActorRunDirector = m_pRockerAction->GetRockerRunDirection();
	if (!m_pArthurKing)
	{
		CCLOG("no begin...");
		return;
	}

	switch (m_pRockerAction->GetRockerDirection())
	{
	case EnRocker_Right:
	{
		m_pArthurKing->SetAnimation(RunAnimation_List, RunAnimation_Png, "run_", 8, bActorRunDirector);
		const Vec2 vec2ActorPoint = m_pArthurKing->getPosition();
		CCLOG("Right: x:%lf , y:%lf ", vec2ActorPoint.x, vec2ActorPoint.y);
		m_pArthurKing->setPosition(ccp(vec2ActorPoint.x + 1, vec2ActorPoint.y));
	}
	break;
	case EnRocker_Up:
	{
		m_pArthurKing->SetAnimation(RunAnimation_List, RunAnimation_Png, "run_", 8, bActorRunDirector);
		const Vec2 vec2ActorPoint = m_pArthurKing->getPosition();
		CCLOG("Up: x:%lf , y:%lf ", vec2ActorPoint.x, vec2ActorPoint.y);
		m_pArthurKing->setPosition(ccp(vec2ActorPoint.x + 2, vec2ActorPoint.y + 2));
	}
	case EnRocker_Left:
	{
		m_pArthurKing->SetAnimation(RunAnimation_List, RunAnimation_Png, "run_", 8, bActorRunDirector);
		const Vec2 vec2ActorPoint = m_pArthurKing->getPosition();
		CCLOG("Left: x:%lf , y:%lf ", vec2ActorPoint.x, vec2ActorPoint.y);
		m_pArthurKing->setPosition(ccp(vec2ActorPoint.x - 2, vec2ActorPoint.y + 1));
	}
	case EnRocker_Down:
	{
		m_pArthurKing->SetAnimation(RunAnimation_List, RunAnimation_Png, "run_", 8, bActorRunDirector);
		const Vec2 vec2ActorPoint = m_pArthurKing->getPosition();
		CCLOG("Down: x:%lf , y:%lf ", vec2ActorPoint.x, vec2ActorPoint.y);
		m_pArthurKing->setPosition(ccp(vec2ActorPoint.x, vec2ActorPoint.y - 1));
	}
	default:
		CCLOG("Error Director...");
		m_pArthurKing->StopAnimation();
		break;
	}
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
/* func： Go行走，出现卡牌，此处回调为 创建卡牌处

*/
/************************************************************************/
int schedule_count = 0;
void CGameMainScene::onClick_StartControl(Object* pSender, Control::EventType event)
{
	if (getChildByTag(ECARD_TEST))
	{
		removeChildByTag(ECARD_TEST);
	}
	
	//AddFadeSprite_Test();
	m_CurRandNum = 0;
	if (event == Control::EventType::TOUCH_DOWN)
	{
		int iRandom = GetRandomNum(KAPAI_COUNT);
		const char* strInCard = CCString::createWithFormat("kapai/k_%d.png", iRandom)->getCString();
		CCardSprite* pCardSprite = CCardSprite::create(strInCard, FACE_KAPAI, 5.0f);
		if (pCardSprite)
		{
			pCardSprite->setTag(ECARD_TEST);
			addChild(pCardSprite);
		}
		
		m_CurRandNum = iRandom;
		//// 翻拍后 行走
		schedule_count = 0;
		AfterOpenCard();
	}
}

/************************************************************************/
/* func: 实现 卡牌 随机数字
		情况一： 点击过快，导致随机数为0 的情况
*/
/************************************************************************/
int CGameMainScene::GetRandomNum(int Randsize)
{
	timeval psv;
	cocos2d::gettimeofday(&psv, NULL);    // 计算时间种子   
	unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000;    // 初始化随机数   
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

	m_pArthurKing = CArthurKing::CreateArthurKing(pInitPlayFrame);
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


}

void CGameMainScene::GetAnimateVec(int iMin, int iMax, TVecSpriteFrame &vecPlayer_director, EPlayer iState)
{
	char szPngName[10];
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
}

void CGameMainScene::AfterOpenCard()
{
	// 取得路径，请求控制 角色行走
	if (m_pArthurKing == NULL || m_CurRandNum == 0)
	{
		return;
	}

	m_pArthurKing->GetPlayerGoPath(m_CurRandNum, g_MapReader.GetCanGoPathArr());
	m_pArthurKing->RequestActorCtrl();

	// 翻拍后 显示 分数
	
	BeginFloatHead();

	// 行走
	
	BeginActorGo();
}

int sche_aboutScore = 0;
Vec2 g_Point;
void CGameMainScene::BeginFloatHead()
{
	// 首先 判断是否能够 飘字
	m_CurPalyer_1_Socre = 0;
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
	if (!g_ResCreator.GetMapReaderInstance()->CheckCanTakeAddSocre(m_CurPalyer_1_Socre, g_Point))
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

		std::string szMsg = String::createWithFormat("+%d", m_CurPalyer_1_Socre)->getCString();
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

		/*if (m_pArthurKing == NULL || m_CurRandNum == 0)
		{
		return;
		}

		m_pArthurKing->GetPlayerGoPath(m_CurRandNum, g_MapReader.GetCanGoPathArr());
		m_pArthurKing->RequestActorCtrl();*/

		m_pArthurKing->PlayStartGo();

		//unschedule("AfterOpen_Close");
	}
	, 5.0f, 1, 0.0f, "AfterOpen_Close");
}
