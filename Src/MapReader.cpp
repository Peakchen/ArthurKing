#include "MapReader.h"
#include "ConstUtil.h"

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
	
	ValueVector::iterator itBegin = vecArray.begin();
	for (; itBegin != vecArray.end(); ++itBegin)
	{
		ValueMap  mapObject = itBegin->asValueMap();

		CCLOG("value: %d, %s", mapObject.size(), mapObject["name"]);
		DoParseObject(mapObject);
	}
	
}

void CMapReader::DoParseObject(ValueMap mapObject)
{
	if (strcmp(mapObject["name"].asString().c_str(), "player_1") == 0)
	{

		CCLOG("find player pos....");
	}
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
			Sprite* pGrid = pLayer->tileAt(Point(i, j));
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


