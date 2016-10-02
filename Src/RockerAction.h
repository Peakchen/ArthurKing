#ifndef __ROKER_ACTION__
#define __ROKER_ACTION__

#include "cocos2d.h"

using namespace cocos2d;

typedef enum{
	En_Rocker = 0,
	En_RockerBg,
} ENROCKER_RECONGNITION;

typedef enum{
	EnRocker_Stay = 0,
	EnRocker_Right,
	EnRocker_Up,
	EnRocker_Left,
	EnRocker_Down,
} ENROCKER_DIRECTION;

#pragma once
class CRockerAction :
	public Layer
{
public:
	CRockerAction();
	~CRockerAction();

	// create Rocker
	/******************
	*func: CreateRockerEntity
	*first param: Rocker's Image Name
	*sec Param: Rocker's Background Image Name
	*third Param: Rocker's Point
	***************/
	static CRockerAction* CreateRockerEntity(const char* strRockerImageName, const char* strRockerImageBgName, cocos2d::CCPoint stPoint);

	/************************
	*func: Start Rocker Action
	*param:  If to Stop Rocker Action, or not
	************************/
	void StartRockerAction(bool bStopRockerAction);

	/*******************************
	* func: Stop Rocker Action
	* param: no
	****************************/
	void StopRockerAction();
	
	// create current Class 
	CREATE_FUNC(CRockerAction);

	//////////////////////Layer///////////////////////////////
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);

	CCPoint getAnglePosition(float fHepotenuse, float fAngle);

	// Get Rocker Direction
	int GetRockerDirection(){ return m_nRockerDirection; }

	// out get Rocker actor Run Direction
	bool GetRockerRunDirection(){ return m_bPersonRunDirection; }

private:

	/***************************
	*func: Rocker Init
	*first param: Rocker's Image Name
	*sec Param: Rocker's Background Image Name
	*third Param: Rocker's Point
	************************/
	void __RockerInit(const char* strRockerImageName, const char* strRockerImageBgName, cocos2d::CCPoint stPoint);

	/***************************
	*func: Gain Rocker and Screen 's Angle
	*first param: Rocker's Image Name
	*sec Param: Rocker's Background Image Name
	************************/
	float __GetRockerAndScreenAngle(cocos2d::CCPoint oFirstPoint, cocos2d::CCPoint oSecPoint);

private:
	// Now Rocker Direction 
	int m_nRockerDirection;

	// Now Personn Direction
	bool m_bPersonRunDirection;

	//Whether can operate rocker
	bool m_bCanMove; 

	// Get Rocker Bg Point
	CCPoint m_oRockerBgPoint;

	//Get Rocker Bg Radius;
	float m_fRockerBgRadius;

	// 事件 分发
	EventDispatcher* m_pEventDispatcher;
	
	// 单点触摸 事件监听
	EventListenerTouchOneByOne* m_pEventTouchListener;
};

#endif



