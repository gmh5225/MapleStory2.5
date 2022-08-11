#include "stdafx.h"
#include "..\Public\CutSceneManager.h"

#include "GameInstance.h"
#include "Camera_Free.h"
#include "UIManager.h"

IMPLEMENT_SINGLETON(CCutSceneManager)

CCutSceneManager::CCutSceneManager()
{
}



void CCutSceneManager::Tick(_float fTimeDelta)
{

	if (nullptr == Get_MainCam())
		return;

	if (m_bEnter_Henesys_1)
		Enter_Henesys_1(fTimeDelta);

	if (m_bEnter_Henesys_2)
		Enter_Henesys_2(fTimeDelta);

	if (m_bEnter_Elenya)
		Enter_Elenya(fTimeDelta);

	if (m_bEnter_ElenyaEnter)
		Enter_ElenyaEnter(fTimeDelta);
}

CCamera_Free* CCutSceneManager::Get_MainCam()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CCamera_Free* pCam = (CCamera_Free*)CGameInstance::Get_Instance()->Get_ObjectPtr(LEVEL_STATIC, TEXT("Layer_Camera"), 0);
	
	Safe_Release(pGameInstance);

	return pCam;
}


void CCutSceneManager::SetCamPos(_float3 vPos)
{
	Get_MainCam()->Get_Transform()->Set_State(CTransform::STATE_POSITION, vPos);
}




void CCutSceneManager::Start_Enter_Henesys_1()
{
	if (m_bHenesys_1)
		return;
	m_bHenesys_1 = true;

	m_fHenesys_1_TimeAcc = 0.f;
	Get_MainCam()->SetCamMode(CCamera_Free::CAM_CUTSCENE);
	Get_MainCam()->Get_Transform()->Rotation(_float3(1.f, 0.f, 0.f), 30.f);
	SetCamPos(_float3(-30.f, 12.f, -16.f));
	Get_MainCam()->SetSpeed(3.f);
	m_bIsCutScene = true;
	m_bEnter_Henesys_1 = true;
}
void CCutSceneManager::Enter_Henesys_1(_float fTimeDelta)
{
	m_fHenesys_1_TimeAcc += fTimeDelta;


	Get_MainCam()->Get_Transform()->Go_Right(fTimeDelta);

	if (13.f < m_fHenesys_1_TimeAcc && !m_b1)
	{
		Get_MainCam()->Get_Transform()->RotationTwo(_float3(1.f, 0.f, 0.f), 30.f, _float3(0.f, 1.f, 0.f), -30.f);
		SetCamPos(_float3(20.f, 12.f, -30.f));
		m_b1 = true;
	}

	if (18.f < m_fHenesys_1_TimeAcc)
	{
		Get_MainCam()->Get_Transform()->Rotation(_float3(1.f, 0.f, 0.f), 30.f);
		End_Enter_Henesys_1();
	}

}
void CCutSceneManager::End_Enter_Henesys_1()
{
	m_fHenesys_1_TimeAcc = 0.f;
	Get_MainCam()->SetCamMode(CCamera_Free::CAM_PLAYER);
	m_bIsCutScene = false;
	m_bEnter_Henesys_1 = false;
}



void CCutSceneManager::Start_Enter_Henesys_2()
{
	if (m_bHenesys_2)
		return;
	m_bHenesys_2 = true;

	m_fHenesys_2_TimeAcc = 0.f;
	Get_MainCam()->SetCamMode(CCamera_Free::CAM_CUTSCENE);
	Get_MainCam()->Get_Transform()->Rotation(_float3(1.f, 0.f, 0.f), 30.f);
	SetCamPos(_float3(-10.f, 12.f, -16.f));
	Get_MainCam()->SetSpeed(3.f);
	m_bIsCutScene = true;
	m_bEnter_Henesys_2 = true;
}
void CCutSceneManager::Enter_Henesys_2(_float fTimeDelta)
{
	m_fHenesys_2_TimeAcc += fTimeDelta;


	if(!m_b2_2)
		Get_MainCam()->Get_Transform()->Go_Right(fTimeDelta);
	else
		Get_MainCam()->Get_Transform()->Go_Up(fTimeDelta);



	if (13.f < m_fHenesys_2_TimeAcc && !m_b2_1)
	{
		Get_MainCam()->Get_Transform()->RotationTwo(_float3(1.f, 0.f, 0.f), 30.f, _float3(0.f, 1.f, 0.f), -30.f);
		SetCamPos(_float3(30.f, 12.f, -30.f));
		m_b2_1 = true;
	}

	if (18.f < m_fHenesys_2_TimeAcc && !m_b2_2)
	{
		Get_MainCam()->Get_Transform()->RotationTwo(_float3(1.f, 0.f, 0.f), 30.f, _float3(0.f, 1.f, 0.f), 30.f);
		SetCamPos(_float3(30.f, 15.f, -40.f));
		m_b2_2 = true;
	}



	if (23.f < m_fHenesys_2_TimeAcc)
	{
		Get_MainCam()->Get_Transform()->Rotation(_float3(1.f, 0.f, 0.f), 30.f);
		End_Enter_Henesys_2();
	}

}
void CCutSceneManager::End_Enter_Henesys_2()
{
	m_fHenesys_2_TimeAcc = 0.f;
	Get_MainCam()->SetCamMode(CCamera_Free::CAM_PLAYER);
	m_bIsCutScene = false;
	m_bEnter_Henesys_2 = false;
}



void CCutSceneManager::Start_Enter_Elenya()
{
	if (m_bElenya)
		return;
	m_bElenya = true;

	m_fElenya_TimeAcc = 0.f;
	Get_MainCam()->SetCamMode(CCamera_Free::CAM_CUTSCENE);
	Get_MainCam()->Get_Transform()->Rotation(_float3(1.f, 0.f, 0.f), 30.f);
	SetCamPos(_float3(-5.f, 12.f, -16.f));
	Get_MainCam()->SetSpeed(3.f);
	m_bIsCutScene = true;
	m_bEnter_Elenya = true;
}
void CCutSceneManager::Enter_Elenya(_float fTimeDelta)
{
	m_fElenya_TimeAcc += fTimeDelta;


	if (!m_b3_1)
		Get_MainCam()->Get_Transform()->Go_Right(fTimeDelta);
	else
		Get_MainCam()->Get_Transform()->Go_Up(fTimeDelta);



	if (13.f < m_fElenya_TimeAcc && !m_b3_1)
	{
		Get_MainCam()->Get_Transform()->RotationTwo(_float3(1.f, 0.f, 0.f), 30.f, _float3(0.f, 1.f, 0.f), -30.f);
		SetCamPos(_float3(10.f, 0.f, -30.f));
		m_b3_1 = true;
	}



	if (20.f < m_fElenya_TimeAcc)
	{
		Get_MainCam()->Get_Transform()->Rotation(_float3(1.f, 0.f, 0.f), 30.f);
		End_Enter_Elenya();
	}

}
void CCutSceneManager::End_Enter_Elenya()
{
	m_fElenya_TimeAcc = 0.f;
	Get_MainCam()->SetCamMode(CCamera_Free::CAM_PLAYER);
	m_bIsCutScene = false;
	m_bEnter_Elenya = false;
}





void CCutSceneManager::Start_Enter_ElenyaEnter()
{
	if (m_bElenyaEnter)
		return;
	m_bElenyaEnter = true;


	m_fElenyaEnter_TimeAcc = 0.f;
	Get_MainCam()->SetCamMode(CCamera_Free::CAM_CUTSCENE);
	Get_MainCam()->Get_Transform()->RotationTwo(_float3(1.f, 0.f, 0.f), 15.f, _float3(0.f, 1.f, 0.f), 90.f);
	SetCamPos(_float3(25.f, 7.f, -9.f));
	Get_MainCam()->SetSpeed(1.f);

	CUIManager::Get_Instance()->On_CutScreen();
	
	m_bEnter_ElenyaEnter = true;
	m_bIsCutScene = true;
}
void CCutSceneManager::Enter_ElenyaEnter(_float fTimeDelta)
{
	m_fElenyaEnter_TimeAcc += fTimeDelta;


	if (!m_b4_1)
		Get_MainCam()->Get_Transform()->Go_Straight(fTimeDelta);



	if (7.5f < m_fElenyaEnter_TimeAcc && !m_b4_1)
	{
		m_b4_1 = true;
	}



	if (12.f < m_fElenyaEnter_TimeAcc)
	{
		Get_MainCam()->Get_Transform()->Rotation(_float3(1.f, 0.f, 0.f), 30.f);
		End_Enter_ElenyaEnter();
	}
}
void CCutSceneManager::End_Enter_ElenyaEnter()
{
	m_fElenyaEnter_TimeAcc = 0.f;
	Get_MainCam()->SetCamMode(CCamera_Free::CAM_PLAYER);

	CUIManager::Get_Instance()->Off_CutScreen();

	m_bIsCutScene = false;
	m_bEnter_ElenyaEnter = false;
}




void CCutSceneManager::Free()
{

}

