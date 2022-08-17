#include "stdafx.h"
#include "..\Public\ChasingShotHit.h"
#include "GameInstance.h"

CChasingShotHit::CChasingShotHit(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCreature(pGraphic_Device)
{
}
CChasingShotHit::CChasingShotHit(const CChasingShotHit & rhs)
	: CCreature(rhs)
{
}

HRESULT CChasingShotHit::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}
HRESULT CChasingShotHit::Initialize(void * pArg)
{
	__super::Initialize(pArg);

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, *(_float3*)pArg);
	m_pTransformCom->Set_Scaled(3.5f);
	m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_ChasingShot_Hit"), 0.08f, CAnimator::STATE_ONCE);
	m_fYDistance = 10.f;
	Set_Billboard();
	_float3 vCLook = m_pTransformCom->Get_State(CTransform::STATE_LOOK);
	_float3 vPo = *(_float3*)pArg - m_pTransformCom->Get_State(CTransform::STATE_LOOK)*0.4f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPo);
	return S_OK;
}

HRESULT CChasingShotHit::SetUp_Components()
{
	{
		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_ChasingShot_Hit"), nullptr);
	}

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"), TEXT("Com_Transform"), (CComponent**)&m_pTransformCom)))
		return E_FAIL;

	return S_OK;
}




void CChasingShotHit::Tick(_float fTimeDelta)
{

}
void CChasingShotHit::LateTick(_float fTimeDelta)
{
	Compute_CamDistance(m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_ALPHABLEND, this);


	if (m_pAnimatorCom->Get_AnimCount() == 10)
		Set_Dead();

	Set_Billboard();

}
HRESULT CChasingShotHit::Render()
{

	if (FAILED(m_pTransformCom->Bind_WorldMatrix()))
		return E_FAIL;

	_float fDF = CGameInstance::Get_Instance()->Get_TimeDelta(TEXT("Timer_60"));
	if (FAILED(m_pAnimatorCom->Play_Ani(1.f * fDF)))
		return E_FAIL;

	if (FAILED(Set_RenderState()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	if (FAILED(Reset_RenderState()))
		return E_FAIL;



	return S_OK;
}


void CChasingShotHit::SetAni()
{

}


CChasingShotHit * CChasingShotHit::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CChasingShotHit*		pInstance = new CChasingShotHit(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CChasingShotHit"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
CGameObject * CChasingShotHit::Clone(void* pArg)
{
	CChasingShotHit*		pInstance = new CChasingShotHit(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CChasingShotHit"));
		Safe_Release(pInstance);
	}

	return pInstance;
}




void CChasingShotHit::Collision(CGameObject * pOther)
{

}

HRESULT CChasingShotHit::Set_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphic_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphic_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	return S_OK;
}

HRESULT CChasingShotHit::Reset_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pTransformCom->CulRUByLook(m_vLookTemp);
	return S_OK;
}




void CChasingShotHit::Free()
{
	__super::Free();

}

