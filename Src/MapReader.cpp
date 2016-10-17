#include "MapReader.h"
#include "ConstUtil.h"
#include "ResCreator.h"

CMapReader g_MapReader;

Scene* CMapReader::createMapReaderScene()
{
	auto scene = Scene::create();
	auto layer = CMapReader::create();

	scene->addChild(layer);

	return scene;
}

bool CMapReader::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	_tilemap = NULL;
	_bg = NULL;
	_player = NULL;

	_tilemap = TMXTiledMap::create("map/otherMap.tmx");
	/*const Size sizeWin = Director::getInstance()->getVisibleSize();
	_tilemap->setPosition(ccp(sizeWin.width, sizeWin.h));*/
	addChild(_tilemap, 0, 1);

	//initPressGrid();
	ParseTileMap();
	setPathWay();
	//
	return true;
}

void CMapReader::initPlayer()
{

}

void CMapReader::ParseTileMap()
{
	TMXObjectGroup* pObjectGroup = _tilemap->getObjectGroup("objects");
	ValueVector vecArray = pObjectGroup->getObjects();
	
	g_ResCreator.GetMapReaderInstance()->setVecObjectPath(vecArray);

	ValueVector::iterator itBegin = vecArray.begin();
	for (; itBegin != vecArray.end(); ++itBegin)
	{
		ValueMap  mapObject = itBegin->asValueMap();

		CCLOG("ParseTileMap		value: %d,	name: %s", mapObject.size(), mapObject["name"]);
		CCLOG("ParseTileMap		X: %s,		Y: %s", mapObject["x"].asString().c_str(), mapObject["y"].asString().c_str());
		CCLOG("ParseTileMap		Type: %s", mapObject["Type"].asString().c_str());

		GWORD dwScore = 0;
		//DoParseScore(mapObject, dwScore);
	}
	
}

bool CMapReader::CheckCanTakeAddSocre(GWORD &dwScore, Vec2 oPoint)
{

	CCLOG("Dest: x = %02f,   y = %02f ", oPoint.x, oPoint.y);
	ValueVector vecArray = g_ResCreator.GetMapReaderInstance()->getVecObjectPath();
	
	ValueVector::iterator itBegin = vecArray.begin();
	for (; itBegin != vecArray.end(); ++itBegin)
	{
		ValueMap  mapObject = itBegin->asValueMap();

		CCLOG("value: %d, %s", mapObject.size(), mapObject["name"]);
		float x = mapObject["x"].asFloat();
		float y	= mapObject["y"].asFloat();

		Vec2 vecPoint = Vec2(x, y);

		Vec2 vecPoint1 = Vec2(x + 1, y + 1);
		Vec2 vecPoint2 = Vec2(x + 1, y);
		Vec2 vecPoint3 = Vec2(x, y + 1);

		Vec2 vecPoint4 = Vec2(x - 1, y - 1);
		Vec2 vecPoint5 = Vec2(x - 1, y);
		Vec2 vecPoint6 = Vec2(x, y - 1);

		CCLOG("Src: x = %02f,   y = %02f ", x, y);
		
		bool bFlag_x = (fabs(oPoint.x - x) <= CoordinateDiff);
		bool bFlag_y = (fabs(oPoint.y - y) <= CoordinateDiff);
		CCLOG("fabs: x = %02f,   y = %02f ", fabs(oPoint.x - x), fabs(oPoint.y - y));

		if (bFlag_x && bFlag_y)
		{
			if (DoParseScore(mapObject, dwScore))
			{
				CCLOG("Src Map		value: %d,	name: %s", mapObject.size(), mapObject["name"]);
				CCLOG("Src Map		X: %s,		Y: %s", mapObject["x"].asString().c_str(), mapObject["y"].asString().c_str());
				CCLOG("Src eMap		Type: %s", mapObject["Type"].asString().c_str());
				CCLOG("Src: x = %02f,   y = %02f ", x, y);
				return true;
			}
		}
		
	}
	return false;
}

bool CMapReader::DoParseScore(ValueMap mapObject, GWORD &dwScore)
{
	if (strcmp(mapObject["name"].asString().c_str(), "Score") == 0)
	{
		CCLOG("find Score pos....");

		if (strcmp(mapObject["Type"].asString().c_str(), "int") == 0)
		{
			CCLOG("---------------------------finally find result Coordinate----------------------------");
			CCLOG("Dest Map		value: %d,	name: %s", mapObject.size(), mapObject["name"]);
			CCLOG("Dest Map		X: %s,		Y: %s", mapObject["x"].asString().c_str(), mapObject["y"].asString().c_str());
			CCLOG("Dest Map			Type: %s", mapObject["Type"].asString().c_str());
			CCLOG("Dest Map			Type: %s", mapObject["Value"].asString().c_str());

			dwScore = mapObject["Value"].asDouble();

			return true;
		}
	}

	return false;
}

void CMapReader::setPathWay()
{
	int layNum = _tilemap->getLayerNum();

	TMXLayer* pLayer = _tilemap->getLayer("pathway");

	int **arrPassGrid = new int*[TILE_ROW];
	initPressGrid(arrPassGrid);

	Size oMapsize = pLayer->getLayerSize();
	std::vector<Vec2> vevLayerPath;
	for (int i = 0; i < oMapsize.width; ++i)
	{
		for (int j = 0; j < oMapsize.height; ++j)
		{
			Vec2 v = Point(i, j);
			Sprite* pGrid = pLayer->tileAt(v);
			if (pGrid)
			{
				float iLocX = pGrid->getPositionX();
				float iLocY = pGrid->getPositionY();
				int iRow = iLocY / TILE_HEIGHT;
				int iCol = iLocX / TILE_WIDTH;

				arrPassGrid[iRow][iCol] = 1;
				
				Vec2 vecPos = pGrid->getPosition();
				vevLayerPath.push_back(vecPos);

				CCLOG("Grid's row = %d, col = %d, pass: %d", iRow, iCol,  arrPassGrid[iRow][iCol]);
			}
		}
	}

	g_MapReader.SetMapLayPath(vevLayerPath);
	g_MapReader.SetCanGoPath(arrPassGrid);
}

void CMapReader::initPressGrid(int** arrPassGrid)
{
	for (int i = 0; i < TILE_ROW; ++i)
	{
		arrPassGrid[i] = new int[TILE_COL];
	}

	for (int iRow = 0; iRow < TILE_ROW; ++iRow)
	{
		for (int iCol = 0; iCol < TILE_COL; ++iCol)
		{
			arrPassGrid[iRow][iCol] = 0;
		}
	}

}

CMapReader* CMapReader::getMapReaderInstance()
{
	CMapReader* pMapReader = new CMapReader();
	if (pMapReader == NULL)
	{
		return NULL;
	}

	return pMapReader;
}

CMapReader::CMapReader()
{

}

CMapReader::~CMapReader()
{
	
}

void CMapReader::SetCanGoPath(int** arrGrid)
{
	m_arrPassGrid = new int*[TILE_ROW];
	initPressGrid(m_arrPassGrid);

	for (int iRow = 0; iRow < TILE_ROW; ++iRow)
	{
		for (int iCol = 0; iCol < TILE_COL; ++iCol)
		{
			m_arrPassGrid[iRow][iCol] = arrGrid[iRow][iCol];
		}
	}
}


