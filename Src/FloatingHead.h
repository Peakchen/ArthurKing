#pragma once

#ifndef _FloatingHead_
#define _FloatingHead_

#include "cocos2d.h"

USING_NS_CC;

enum EFloatHead
{
	EFloatMsg_Label = 1,
	EFloatMsg_Layer,
};

class CFloatingHead :
	public LayerColor
{
public:
	CFloatingHead();
	~CFloatingHead();

	static void createFloatingHead(Node *pNode, const std::string szMsg, float itimes, Vec2 oPoint);
	void removeFloatingHead(Node *node);

	CREATE_FUNC(CFloatingHead);

};

#endif // !1

