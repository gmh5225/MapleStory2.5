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

	void Start_Enter_Elenya();
	void End_Enter_Elenya();


	void SetCamPos(_float3 vPos);

public:
	void Enter_Henesys_1(_float fTimeDelta);
	void Enter_Henesys_2(_float fTimeDelta);
	void Enter_Elenya(_float fTimeDelta);


private:
	//.for total
	_bool m_bIsCutScene = false;

	_bool m_bHenesys_1 = false;
	_bool m_bHenesys_2 = false;
	_bool m_bElenya = false;

	//.for Henesys_1
	_bool	m_bEnter_Henesys_1 = false;
	_float	m_fHenesys_1_TimeAcc = 0.f;
	_bool	m_b1 = false;

	//.for Henesys_2
	_bool	m_bEnter_Henesys_2 = false;
	_float	m_fHenesys_2_TimeAcc = 0.f;
	_bool	m_b2_1 = false;
	_bool	m_b2_2 = false;

	//.for Elenya
	_bool	m_bEnter_Elenya = false;
	_float	m_fElenya_TimeAcc = 0.f;
	_bool	m_b3_1 = false;




public:
	virtual void Free() override;

};


END
