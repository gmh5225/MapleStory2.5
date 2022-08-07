#pragma once


#include "Client_Defines.h"
#include "Camera_Free.h"

BEGIN(Client)

class CCutSceneManager final : CBase
{
	DECLARE_SINGLETON(CCutSceneManager)

private:
	CCutSceneManager();
	virtual ~CCutSceneManager() = default;


public:
	class CCamera_Free* Get_MainCam();


public:
	virtual void Free() override;

};


END
