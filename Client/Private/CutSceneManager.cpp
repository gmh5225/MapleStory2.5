#include "stdafx.h"
#include "..\Public\CutSceneManager.h"

#include "GameInstance.h"
#include "Camera_Free.h"

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




void CCutSceneManager::Free()
{

}
