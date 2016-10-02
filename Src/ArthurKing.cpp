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

	//pCallFunc_MoveEnd = CallFunc::create(CC_CALLBACK_0(CArthurKing::OnPlayerMoveEnd, this));
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

void CArthurKing::SetAnimation(const char* szName_list, const char* szPngName, const char* szEachName, const UINT32 nPngCount, bool bRunDirector)
{

	// judge Now Director
	if (m_bActorRunDirector != bRunDirector)
	{
		m_bActorRunDirector = bRunDirector;
		m_pActorSprite->setFlippedX(bRunDirector);
	}

	if (m_bCheckActorRuning)
	{
		return;
	}
	
	CCSpriteFrameCache* pFrameCache = CCSpriteFrameCache::getInstance();
	//CCSpriteFrameCache* pFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	if (!pFrameCache)
	{
		return;
	}
	/*pFrameCache->removeSpriteFrames();
	pFrameCache->removeSpriteFramesFromFileContent(szName_list);*/

	pFrameCache->addSpriteFramesWithFile(szName_list, szPngName);

	// list save all fram cache
	//CCArray* pArray = CCArray::createWithCapacity(nPngCount);
	Vector<CCSpriteFrame*> vecPngArray;
	vecPngArray.reserve(nPngCount);
	/*if (!pArray)
	{
		return;
	}*/

	CCSpriteFrame* pSpriteFram = NULL;
	
	for (int iPngIdx = 1; iPngIdx <= nPngCount; ++iPngIdx)
	{
		pSpriteFram = pFrameCache->spriteFrameByName(CCString::createWithFormat("%s%d.png", szEachName, iPngIdx)->getCString());
		if (!pSpriteFram)
		{
			continue;
		}
		vecPngArray.pushBack(pSpriteFram);
		//pArray->addObject(pSpriteFram);
	}
	
	CCAnimation* pAnimation = CCAnimation::createWithSpriteFrames(vecPngArray);
	// infinite Loop
	pAnimation->setLoops(-1);
	// Delay = 0.1f
	pAnimation->setDelayPerUnit(0.1f);

	CCAnimate* pAction = CCAnimate::create(pAnimation);
	if (!pAction)
	{
		return;
	} 
	
	/*CCRepeatForever* pRepeatForever = CCRepeatForever::create(pAction);
	if (!pRepeatForever)
	{
	return;
	}*/
	m_pActorSprite->runAction(pAction);
	m_bCheckActorRuning = true;

}

void CArthurKing::StopAnimation()
{
	//// current no runing
	//m_pActorSprite->removeChild(this, true);

	if (!m_bCheckActorRuning)
	{
		return;
	}

	m_pActorSprite->stopAllActions();

	this->removeChild(m_pActorSprite, true);

	m_pActorSprite = CCSprite::create(m_szSpriteName);
	m_pActorSprite->setFlippedX(m_bActorRunDirector);
	this->addChild(m_pActorSprite);

	m_bCheckActorRuning = false;
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

void CArthurKing::GetPlayerGoPath(int iStepCount, int** arrCanGoGrid)
{
	float dwLocx = this->getPositionX();
	float dwLocy = this->getPositionY();

	int iNextColStep = 0;
	int iNextRowStep = 0;

	int iCurrentColStep = (dwLocx) / TILE_WIDTH;
	int iCurrentRowStep = (dwLocy - TILE_HEIGHT/5) / TILE_HEIGHT;

	CCLOG("iCurrentColStep: %d, iCurrentRowStep: %d", iCurrentColStep, iCurrentRowStep);
	
	// 设置当前能够行走的 格子
	int **arrTempCanGoGrid = new int *[TILE_ROW];
	g_MapReader.initPressGrid(arrTempCanGoGrid);

	for (int iRow = 0; iRow < TILE_ROW; ++iRow)
	{
		for (int iCol = 0; iCol < TILE_COL; ++iCol)
		{
			arrTempCanGoGrid[iRow][iCol] = arrCanGoGrid[iRow][iCol];

			//CCLOG("arrTempCanGoGrid[iRow][iCol]: %d,  iRow: %d, iCol: %d  ", arrTempCanGoGrid[iRow][iCol], iRow, iCol);
		}
	}

	// 记录当前 走的步数
	int iCurStepCount = 0;

	// 记录当前 走的路径数据
	std::vector<int> vecPassedPath;
	vecPassedPath.reserve(Go_Direction);

	//记录 当前能走的方向
	std::vector<int> vecCanPassDirection;
	vecCanPassDirection.resize(Go_Direction);

	m_passColPath.clear();
	m_passColPath.push_back(iCurrentColStep);
	m_passRowPath.clear();
	m_passRowPath.push_back(iCurrentRowStep);

	while (iCurStepCount < iStepCount)
	{
		// 重置方向
		vecCanPassDirection.resize(Go_Direction);
		/*for (int indx = 0; indx < Go_Direction; ++indx)
		{
		vecCanPassDirection[indx] = 0;
		}*/

		vecCanPassDirection[Direction_Up]	= arrTempCanGoGrid[iCurrentRowStep - 1][iCurrentColStep];
		vecCanPassDirection[Direction_Down] = arrTempCanGoGrid[iCurrentRowStep + 1][iCurrentColStep];
		vecCanPassDirection[Direction_Left] = arrTempCanGoGrid[iCurrentRowStep][iCurrentColStep - 1];
		vecCanPassDirection[Direction_Right] = arrTempCanGoGrid[iCurrentRowStep][iCurrentColStep + 1];

		/*CCLOG("Direction_Up: %d, ", arrTempCanGoGrid[iCurrentRowStep - 1][iCurrentColStep]);
		CCLOG("Direction_Down: %d, ", arrTempCanGoGrid[iCurrentRowStep + 1][iCurrentColStep]);
		CCLOG("Direction_Left: %d, ", arrTempCanGoGrid[iCurrentRowStep][iCurrentColStep - 1]);
		CCLOG("Direction_Right: %d, ", arrTempCanGoGrid[iCurrentRowStep][iCurrentColStep + 1]);*/

		vecPassedPath.clear();
		for (int i = 0; i < Go_Direction; ++i)
		{
			if (vecCanPassDirection[i] == 1)
			{
				vecPassedPath.push_back(i);
			}
		}

		if (vecPassedPath.size() == 0)
		{
			CCLOG("error: vecPassedPath ......... ");
			continue;
		}
		int iRandPath = rand() % vecPassedPath.size();
		
		// 取得 下一步走的位置
		GetCanGoColRowData(vecPassedPath[iRandPath], iCurrentColStep, iCurrentRowStep, iNextColStep, iNextRowStep);

		m_passColPath.push_back(iNextColStep);
		m_passRowPath.push_back(iNextRowStep);

		CCLOG("iNextColStep: %d, ", iNextColStep);
		CCLOG("iNextRowStep: %d, ", iNextRowStep);
		
		arrTempCanGoGrid[iCurrentRowStep][iCurrentColStep] = 0;

		iCurrentColStep = iNextColStep;
		iCurrentRowStep = iNextRowStep;

		++iCurStepCount;
	}

}

void CArthurKing::GetCanGoColRowData(int iRandnum, int iCol, int iRow, int& iNextCol, int &iNextRow)
{
	switch (iRandnum)
	{
		case Direction_Up:
			{
				if (iRow > 1)
					iNextRow = iRow - 1;

				iNextCol = iCol;
			}
			break;
		case Direction_Down:
			{
				iNextRow = iRow + 1;
				iNextCol = iCol;
			}
			break;
		case Direction_Left:
			{
				iNextRow = iRow ;
				if (iCol > 1)
					iNextCol = iCol - 1;
			}
			break;
		case Direction_Right:
			{
				iNextRow = iRow;
				iNextCol = iCol + 1;
			}
			break;

		default:
			CCLOG("error: 随机数据错误...");
			break;
	}
}

void CArthurKing::OnPlayerMove()
{
	stPlayerMovePath.iNextCol = m_passColPath[stPlayerMovePath.iStepCount + 1];
	stPlayerMovePath.iNextRow = m_passRowPath[stPlayerMovePath.iStepCount + 1];

	int iHorizontalDistence = stPlayerMovePath.iNextRow - stPlayerMovePath.iCurRow;
	int iVerticalDistence = stPlayerMovePath.iNextCol - stPlayerMovePath.iCurCol;

	MoveBy *pMove = NULL;
	Repeat *pRepeat = NULL;

	if (iHorizontalDistence > 0)
	{
		pMove = MoveBy::create(0.2f, ccp(0, TILE_HEIGHT));
		if (m_pActor_Up_Animate != NULL)
		{
			pRepeat = Repeat::create(m_pActor_Up_Animate, 1);
		}

	}
	else if (iHorizontalDistence < 0)
	{
		pMove = MoveBy::create(0.2f, ccp(0, -TILE_HEIGHT));
		if (m_pActor_Down_Animate != NULL)
		{
			pRepeat = Repeat::create(m_pActor_Down_Animate, 1);
		}
	}

	if (iVerticalDistence > 0)
	{
		pMove = MoveBy::create(0.2f, ccp(TILE_HEIGHT, 0));
		if (m_pActor_Right_Animate != NULL)
		{
			pRepeat = Repeat::create(m_pActor_Right_Animate, 1);
		}
	}
	else if (iVerticalDistence < 0)
	{
		pMove = MoveBy::create(0.2f, ccp(-TILE_HEIGHT, 0));
		if (m_pActor_Left_Animate != NULL)
		{
			pRepeat = Repeat::create(m_pActor_Left_Animate, 1);
		}
	}

	if (pMove == NULL || pRepeat == NULL)
	{
		CCLOG("error: %s 走路动作创建失败...", __FUNCTION__);
		return;
	}
	Spawn* pSpawn = Spawn::create(pMove, pRepeat, NULL);

	if (pSpawn == NULL)
	{
		CCLOG("error: %s 动作产出 失败。。。", __FUNCTION__);
	}
	Sequence* pSequence = Sequence::create(pSpawn, pCallFunc_MoveEnd, NULL);
	this->runAction(pSequence);
}

void CArthurKing::OnPlayerMoveEnd()
{
	stPlayerMovePath.iStepCount++;
	if (stPlayerMovePath.iStepCount >= (m_passRowPath.size() - 1))
	{
		return;
	}

	stPlayerMovePath.iCurCol = stPlayerMovePath.iNextCol;
	stPlayerMovePath.iCurRow = stPlayerMovePath.iNextRow;
	OnPlayerMove();
}

void CArthurKing::UpdateScoreItem(int addScore)
{
	m_ActorScore += addScore;
}

void CArthurKing::PlayStartGo()
{
	m_pCtrl->StartActorGo();
}
