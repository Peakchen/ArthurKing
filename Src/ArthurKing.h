#ifndef __ARTHUR_KING__
#define __ARTHUR_KING__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#pragma once
class CArthurKing :
	public Sprite
{
public:
	CArthurKing();
	~CArthurKing();

	// Create Arthur King 
	/***************************
	* func: Create Arthur King actor 
	* param: strArthurKingName is picture' name
	* return: void
	*************************/
	static CArthurKing* CreateArthurKing(SpriteFrame* pFrame);

	/******************************
	func: SetAnimation  , to set Current actor animation
	param: szNameList  , config animation
	param: szPngName , Png's name
	param: szEachName, public name
	param: nPngCount, png count
	param: bRunDirector, Run Director , if is false, right, else left
	*****************************/
	void SetAnimation(const char* szName_list, const char* szPngName, const char* szEachName, const UINT32 nPngCount, bool bRunDirector );

	// Stop Animation
	void StopAnimation();

	bool init();

	CC_SYNTHESIZE(Vector<SpriteFrame*>, vecPlayer_anim_Left, vecAnim_Left);
	CC_SYNTHESIZE(Vector<SpriteFrame*>, vecPlayer_anim_right, vecAnim_Right);
	CC_SYNTHESIZE(Vector<SpriteFrame*>, vecPlayer_anim_down, vecAnim_down);
	CC_SYNTHESIZE(Vector<SpriteFrame*>, vecPlayer_anim_up, vecAnim_up);

	void PlayStartGo();

	void GetPlayerGoPath(int iStepCount, int** arrCanGoGrid);

	//CREATE_FUNC(CArthurKing);

	CC_SYNTHESIZE(std::vector<int>, m_passColPath, RecordPassColPath);
	CC_SYNTHESIZE(std::vector<int>, m_passRowPath, RecordPassRowPath);
private:
	// to Check actor is runing?
	bool m_bCheckActorRuning;

	bool m_bActorRunDirector; //actor run director
	
	CCSprite* m_pActorSprite; // sprite addr
	char* m_szSpriteName; // init picture name

	//四方向动画
	Animate* m_pActor_Left_Animate;
	Animate* m_pActor_Right_Animate;
	Animate* m_pActor_Up_Animate;
	Animate* m_pActor_Down_Animate;

	struct TMovePathData
	{
		int iCurCol;
		int iCurRow;
		int iNextCol;
		int iNextRow;
		
		int iStepCount;
	};

	TMovePathData stPlayerMovePath;

	CallFunc* pCallFunc_MoveEnd;

private:

	void GetCanGoColRowData(int iRandnum, int iCol, int iRow, int& iNextCol, int &iNextRow);
	void OnPlayerMove();

	void OnPlayerMoveEnd();
};

#endif



