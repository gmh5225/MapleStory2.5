#include "stdafx.h"
#include "..\Public\Camera_Free.h"
#include "GameInstance.h"

CCamera_Free::CCamera_Free(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCamera(pGraphic_Device)
{
}

CCamera_Free::CCamera_Free(const CCamera_Free & rhs, CTransform::TRANSFORMDESC * pArg)
	: CCamera(rhs, pArg)
{

}

HRESULT CCamera_Free::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCamera_Free::Initialize(void * pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;


	return S_OK;
}

void CCamera_Free::Tick(_float fTimeDelta)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	// ī�޶� ��ġ ����
	CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_ComponentPtr(LEVEL_GAMEPLAY, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);
	_float3 vPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);

	m_pTransformCom->RotationSpot(vPlayerPos, _float3{ 0.f, 5.f, -5.f }, 0.f);
	
	Safe_Release(pGameInstance);

	//if (pGameInstance->Get_DIKState(DIK_W) & 0x80)
	//{
	//	m_pTransformCom->Go_Straight(fTimeDelta);
	//}

	//if (pGameInstance->Get_DIKState(DIK_S) & 0x80)
	//{
	//	m_pTransformCom->Go_Backward(fTimeDelta);
	//}

	//if (pGameInstance->Get_DIKState(DIK_A) & 0x80)
	//{
	//	m_pTransformCom->Go_Left(fTimeDelta);
	//}

	//if (pGameInstance->Get_DIKState(DIK_D) & 0x80)
	//{
	//	m_pTransformCom->Go_Right(fTimeDelta);
	//}

	//_long	MouseMove = 0;

	//if (MouseMove = pGameInstance->Get_DIMMoveState(DIMM_X))
	//{
	//	m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), MouseMove * fTimeDelta * 0.05f);		
	//}

	//if (MouseMove = pGameInstance->Get_DIMMoveState(DIMM_Y))
	//{
	//	m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_RIGHT), MouseMove * fTimeDelta * 0.05f);
	//}

	
	__super::Tick(fTimeDelta);



}

void CCamera_Free::LateTick(_float fTimeDelta)
{
}

HRESULT CCamera_Free::Render()
{
	return S_OK;
}

CCamera_Free * CCamera_Free::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CCamera_Free*		pInstance = new CCamera_Free(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CCamera_Free"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCamera_Free::Clone(void* pArg)
{
	CCamera::CAMERADESC*		pCameraDesc = (CCamera::CAMERADESC*)pArg;

	CCamera_Free*		pInstance = new CCamera_Free(*this, &pCameraDesc->TransformDesc);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Created : CTerrain"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCamera_Free::Free()
{
	__super::Free();


}
