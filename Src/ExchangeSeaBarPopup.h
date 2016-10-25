
#pragma once
#include "SeaBarPopBase.h"

class CExchangeSeaBarPopup :
	public CSeaBarPopBase
{
public:
	CExchangeSeaBarPopup();
	~CExchangeSeaBarPopup();

	/////////////////////////////////Layer////////////////////////////////

	virtual void	OnEnter();

	virtual void	onExit();

	/////////////////////////////////CSeaBarPopBase//////////////////////////////////////
	/************************************************************************/
	/*
	@func:		setPopContext
	@param:		const char * szTitle
	@param:		const char * szContext
	@return:	no
	@brief:		set pop dialog title and context
	*/
	/************************************************************************/
	virtual void	setPopContext(const char * szTitle, const char* szContext);

private:

	Menu* m_pPopPlayer;
};

