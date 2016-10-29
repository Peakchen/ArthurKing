
/************************************************************************/
/* 

*/
/************************************************************************/

#include "ActionSpiltHandler.h"

class CSH_SeaBar: public IArthurActionSpiltHandler
{
public:
	CSH_SeaBar();
	~CSH_SeaBar();

	virtual char* GetActionName();

	virtual void CheckCurrentAction(const char* szName, const char* szType, CActorBase* pActor);

private:

};
