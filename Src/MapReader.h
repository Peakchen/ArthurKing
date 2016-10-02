#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "MacroDefine.h"

USING_NS_CC;
USING_NS_CC_EXT;

const float CoordinateDiff = 3.0f;

class CMapReader :
	public LayerColor
{
public:

	CMapReader();
	~CMapReader();

	static Scene* createMapReaderScene();
	virtual bool init();

	void initMainLayer();

	static CMapReader* getMapReaderInstance();

	CC_SYNTHESIZE_RETAIN(TMXTiledMap*, _tilemap, TileMap);
	CC_SYNTHESIZE_RETAIN(TMXLayer*, _bg, MapBackground);
	CC_SYNTHESIZE_RETAIN(Sprite*, _player, Player);

	CC_SYNTHESIZE(ValueVector, m_vecArray, VecObjectPath);

	CREATE_FUNC(CMapReader);

private:
	void initPlayer();
	void ParseTileMap();

	bool DoParseScore(ValueMap mapObject, DWORD &dwScore);

	void setPathWay();

	void SetMapLayPath(std::vector<Vec2> vevLayerPath){ m_vecLayerPath = vevLayerPath; }

	//设置可走格子
	void SetCanGoPath(int** arrGrid);

private:
	int** m_arrPassGrid;
	//std::vector<Vec2> vevLayerPath;

	std::vector<Vec2> m_vecLayerPath;

	//ValueVector m_vecArray;
public:
		// 取得 行走路径
	std::vector<Vec2>* GetGoPathMap(){ return &m_vecLayerPath; }
	int** GetCanGoPathArr(){ return m_arrPassGrid; }

	void initPressGrid(int** arrPassGrid);

	bool CheckCanTakeAddSocre(DWORD &iScore, Vec2 oPoint);
};

extern CMapReader g_MapReader;

