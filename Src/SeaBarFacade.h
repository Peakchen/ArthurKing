/************************************************************************/
/* 
@arthur:	StefanChen
@date:		20161029
@return:	void
@brief:		Sea bar Facede Instance Tool interface
*/
/************************************************************************/

#ifndef __SEABAR_FACADE__
#define __SEABAR_FACADE__

#include "BuySeaBarAction.h"
#include "GiveTipAction.h"
#include "SellSeaBarAction.h"

class CSeaBarFacade
{
public:
	explicit CSeaBarFacade();
	~CSeaBarFacade();

	/************************************************************************/
	/* 
	@func:		GetBuySeaBarInstance
	@param:		no
	@return:	CBuySeaBarAction*
	@brief:		in some sence, get instance to  do...
	*/
	/************************************************************************/
	CBuySeaBarAction*			GetBuySeaBarInstance(){ return &m_oBuySeaBar; }

	/************************************************************************/
	/*
	@func:		GetGiveTipInstance
	@param:		no
	@return:	CGiveTipAction*
	@brief:		in some sence, get instance to  do...
	*/
	/************************************************************************/
	CGiveTipAction*				GetGiveTipInstance(){ return &m_oGiveTip; }

	/************************************************************************/
	/*
	func: GetSellSeaBarInstance
	Desc: get SellSeaBar ActionInstance , toDO...
	param: No
	return : CSellSeaBarAction*
	*/
	/************************************************************************/
	CSellSeaBarAction*			GetSellSeaBarInstance(){ return &m_oSellSeaBarAction; }

private:

	CBuySeaBarAction m_oBuySeaBar;

	CGiveTipAction   m_oGiveTip;

	CSellSeaBarAction	m_oSellSeaBarAction;

};

extern CSeaBarFacade g_SeaBarFacade;

#endif