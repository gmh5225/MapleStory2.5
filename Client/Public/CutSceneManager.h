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
	void Tick(_float fTimeDelta);

public:
	class CCamera_Free* Get_MainCam();


	_bool IsCutScene() { return m_bIsCutScene; }

	void Start_Enter_Henesys_1(); 
	void End_Enter_Henesys_1();

	void Start_Enter_Henesys_2();
	void End_Enter_Henesys_2();


	void SetCamPos(_float3 vPos);

public:
	void Enter_Henesys_1(_float fTimeDelta);
	void Enter_Henesys_2(_float fTimeDelta);


private:

	//.for total
	_bool m_bIsCutScene = false;

	//.for Henesys_1
	_bool m_bEnter_Henesys_1 = false;
	_float m_fHenesys_1_TimeAcc = 0.f;
	_bool m_b1 = false;

public:
	virtual void Free() override;

};


END
