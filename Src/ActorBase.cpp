#include "ActorBase.h"
#include "ConstUtil.h"
#include "MapReader.h"


CActorBase::CActorBase()
{
	m_dwScore = 0;
}


CActorBase::~CActorBase()
{
}

void CActorBase::GetPlayerGoPath(int iStepCount, int** arrCanGoGrid)
{
	float dwLocx = this->getPositionX();
	float dwLocy = this->getPositionY();

	int iNextColStep = 0;
	int iNextRowStep = 0;

	int iCurrentColStep = ceil(dwLocx / TILE_WIDTH);
	int iCurrentRowStep = ceil((dwLocy - TILE_HEIGHT / 5) / TILE_HEIGHT);

	CCLOG("iCurrentColStep: %d, iCurrentRowStep: %d", iCurrentColStep, iCurrentRowStep);

	// ���õ�ǰ�ܹ����ߵ� ����
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

	// ��¼��ǰ �ߵĲ���
	int iCurStepCount = 0;

	// ��¼��ǰ �ߵ�·������
	std::vector<int> vecPassedPath;
	vecPassedPath.reserve(Go_Direction);

	//��¼ ��ǰ���ߵķ���
	std::vector<int> vecCanPassDirection;
	vecCanPassDirection.resize(Go_Direction);

	m_passColPath.clear();
	m_passColPath.push_back(iCurrentColStep);
	m_passRowPath.clear();
	m_passRowPath.push_back(iCurrentRowStep);

	while (iCurStepCount < iStepCount)
	{
		// ���÷���
		vecCanPassDirection.resize(Go_Direction);
		/*for (int indx = 0; indx < Go_Direction; ++indx)
		{
		vecCanPassDirection[indx] = 0;
		}*/

		vecCanPassDirection[Direction_Up] = arrTempCanGoGrid[iCurrentRowStep - 1][iCurrentColStep];
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

		// ȡ�� ��һ���ߵ�λ��
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

void CActorBase::GetCanGoColRowData(int iRandnum, int iCol, int iRow, int& iNextCol, int &iNextRow)
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
				iNextRow = iRow;
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
			CCLOG ( "error: ������ݴ���..." );
			break;
	}
	
}

void CActorBase::UpdateScoreItem ( int addScore )
{
	m_dwScore += addScore;
}

int CActorBase::GetEntityPDBID()
{
	return 0;
}

int CActorBase::GetEntityRuleProp(int iRulePropID)
{
	return 0;
}

