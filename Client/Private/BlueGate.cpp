#include "stdafx.h"
#include "..\Public\BlueGate.h"

#include "GameInstance.h"


CBlueGate::CBlueGate(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCreature(pGraphic_Device)
{
}
CBlueGate::CBlueGate(const CBlueGate & rhs)
	: CCreature(rhs)
{
}




HRESULT CBlueGate::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}
HRESULT CBlueGate::Initialize(void * pArg)
{
	__super::Initialize(pArg);

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_sTag = "Tag_Npc";

	m_fColRad = 1.f;	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(10.5f, 1.5f, 0.f));
	m_pTransformCom->Set_Scaled(4.5f);

	SetState(STATE_IDLE, DIR_END);



	return S_OK;
}




HRESULT CBlueGate::SetUp_Components()
{
	{
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_BlueGate"), nullptr);

	}


	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(TransformDesc));

	TransformDesc.fSpeedPerSec = 0.5f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"), TEXT("Com_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;

	return S_OK;
}




void CBlueGate::Tick(_float fTimeDelta)
{

	switch (m_eCurState)
	{
	case Client::CBlueGate::STATE_IDLE:
		Tick_Idle(fTimeDelta);
		break;
	case Client::CBlueGate::STATE_MOVE:
		Tick_Move(fTimeDelta);
		break;
	case Client::CBlueGate::STATE_HIT:
		Tick_Hit(fTimeDelta);
		break;
	case Client::CBlueGate::STATE_CHASE:
		Tick_Chase(fTimeDelta);
		break;
	}

}
void CBlueGate::LateTick(_float fTimeDelta)
{
	Set_Billboard();

	if (m_pAnimatorCom->Get_AniInfo().eMode == CAnimator::STATE_ONCEEND)
		SetState(STATE_CHASE, m_eDir);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
	m_pColliderCom->Add_PushBoxCollsionGroup(CCollider::COLLSION_UI, this);
}
HRESULT CBlueGate::Render()
{
	if (FAILED(m_pTransformCom->Bind_WorldMatrix()))
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphic_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphic_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

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





void CBlueGate::Tick_Idle(_float fTimeDelta)
{
}
void CBlueGate::Tick_Move(_float fTimeDelta)
{
}
void CBlueGate::Tick_Hit(_float fTimeDelta)
{
}

void CBlueGate::Tick_Chase(_float fTimeDelta)
{
}



void CBlueGate::SetState(STATE eState, DIR eDir)
{
	if (m_eCurState == eState && m_eDir == eDir)
		return;

	m_eCurState = eState;
	m_eDir = eDir;
	SetAni();
}
void CBlueGate::SetAni()
{
	switch (m_eCurState)
	{
	case CBlueGate::STATE_IDLE:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_BlueGate"), 0.1f, CAnimator::STATE_LOOF);
		break;
	case CBlueGate::STATE_MOVE:
	{
	}
	break;
	case CBlueGate::STATE_HIT:
		break;
	case CBlueGate::STATE_CHASE:
		break;
	}
}

void CBlueGate::Damaged(CGameObject * pOther)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_ComponentPtr(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

	_float3 vPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);

	
	SetState(STATE_HIT,DIR_END);



	Safe_Release(pGameInstance);
}






CBlueGate * CBlueGate::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBlueGate*		pInstance = new CBlueGate(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CBlueGate"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
CGameObject * CBlueGate::Clone(void* pArg)
{
	CBlueGate*		pInstance = new CBlueGate(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CBlueGate"));
		Safe_Release(pInstance);
	}

	return pInstance;
}




void CBlueGate::Collision(CGameObject * pOther)
{
}




void CBlueGate::Free()
{
	__super::Free();

}

