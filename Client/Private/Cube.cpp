#include "stdafx.h"
#include "..\Public\Cube.h"

#include "GameInstance.h"

CCube::CCube(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CCube::CCube(const CCube & rhs)
	: CGameObject(rhs)
{
}


HRESULT CCube::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCube::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;	

	if (nullptr == pArg)
		return E_FAIL;

	m_pData = (CMap_Manager::CUBEDATA*)pArg;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pData->vPos);

	// m_pTransformCom->Rotation(_float3{ 0.f, 1.f, 0.f }, 45.f);

	return S_OK;
}

void CCube::Tick(_float fTimeDelta)
{
	
}

void CCube::LateTick(_float fTimeDelta)
{

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CCube::Render()
{
	if (FAILED(m_pTransformCom->Bind_WorldMatrix()))
		return E_FAIL;	
	
	if (FAILED(m_pTextureCom->Bind_Texture(m_pData->iIndex)))
		return E_FAIL;


	if (FAILED(Set_RenderState()))
		return E_FAIL;


		m_pVIBufferCom->Render();


	if (FAILED(Reset_RenderState()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCube::Set_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	return S_OK;
}

HRESULT CCube::Reset_RenderState()
{


	return S_OK;
}

HRESULT CCube::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), TEXT("Com_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Cube"), TEXT("Com_VIBuffer"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */

	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Cube"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;
	

	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(TransformDesc));

	TransformDesc.fSpeedPerSec = 5.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"), TEXT("Com_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;

	return S_OK;
}

CCube * CCube::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CCube*		pInstance = new CCube(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CCube"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCube::Clone(void* pArg)
{
	CCube*		pInstance = new CCube(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CCube"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCube::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
}

