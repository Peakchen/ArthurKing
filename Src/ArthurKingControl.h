#pragma once
#include "cocos2d.h"
#include "ArthurKing.h"

USING_NS_CC;

class CArthurKingControl :
	public Layer
{
public:
	CArthurKingControl();
	~CArthurKingControl();

	void StartActorGo(std::vector<int> vecRowGo, std::vector<int> vecColGo, CArthurKing* pActor);
	virtual bool init();

	CC_SYNTHESIZE(std::vector<int>, m_passColPath, RecordPassColPath);
	CC_SYNTHESIZE(std::vector<int>, m_passRowPath, RecordPassRowPath);

	CREATE_FUNC(CArthurKingControl);

private:
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

	CArthurKing* m_pActor;

private:
	void OnPlayerMoveEnd();
	void OnPlayerMove();
};

