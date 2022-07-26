#include "stdafx.h"
#include "..\Public\RedSnail.h"

#include "GameInstance.h"

CRedSnail::CRedSnail(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCreature(pGraphic_Device)
{
}
CRedSnail::CRedSnail(const CRedSnail & rhs)
	: CCreature(rhs)
{
}




HRESULT CRedSnail::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}
HRESULT CRedSnail::Initialize(void * pArg)
{
	__super::Initialize(pArg);

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_sTag = "Tag_Monster";

	m_fColRad = 0.5f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(4.f, 0.2f, 0.f));
	m_pTransformCom->Set_Scaled(1.1f);

	SetState(STATE_IDLE, DIR_END);



	return S_OK;
}




HRESULT CRedSnail::SetUp_Components()
{
	{
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_RedSnail_Idle"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_RedSnail_Hit"), nullptr);
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




void CRedSnail::Tick(_float fTimeDelta)
{

	switch (m_eCurState)
	{
	case Client::CRedSnail::STATE_IDLE:
		Tick_Idle(fTimeDelta);
		break;
	case Client::CRedSnail::STATE_MOVE:
		Tick_Move(fTimeDelta);
		break;
	case Client::CRedSnail::STATE_HIT:
		Tick_Hit(fTimeDelta);
		break;
	case Client::CRedSnail::STATE_CHASE:
		Tick_Chase(fTimeDelta);
		break;
	}

}
void CRedSnail::LateTick(_float fTimeDelta)
{
	if (m_pAnimatorCom->Get_AniInfo().eMode == CAnimator::STATE_ONCEEND)
		SetState(STATE_CHASE, m_eDir);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
	m_pColliderCom->Add_CollsionGroup(CCollider::COLLSION_MONSTER, this);

	Set_Billboard();
}
HRESULT CRedSnail::Render()
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





void CRedSnail::Tick_Idle(_float fTimeDelta)
{
}
void CRedSnail::Tick_Move(_float fTimeDelta)
{
}
void CRedSnail::Tick_Hit(_float fTimeDelta)
{
}

void CRedSnail::Tick_Chase(_float fTimeDelta)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_ComponentPtr(LEVEL_GAMEPLAY, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

	_float3 vPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);


	m_pTransformCom->Chase(vPlayerPos, fTimeDelta);

	Safe_Release(pGameInstance);
}



void CRedSnail::SetState(STATE eState, DIR eDir)
{
	if (m_eCurState == eState && m_eDir == eDir)
		return;

	m_eCurState = eState;
	m_eDir = eDir;
	SetAni();
}
void CRedSnail::SetAni()
{
	switch (m_eCurState)
	{
	case CRedSnail::STATE_IDLE:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_RedSnail_Idle"), 0.3f, CAnimator::STATE_LOOF);
	break;
	case CRedSnail::STATE_MOVE:
	{

	}
	break;
	case CRedSnail::STATE_HIT:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_RedSnail_Hit"), 0.5f, CAnimator::STATE_ONCE);
	break;
	case CRedSnail::STATE_CHASE:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_RedSnail_Idle"), 1.f, CAnimator::STATE_LOOF);
		break;
	}
}

void CRedSnail::Damaged(CGameObject * pOther)
{
	_float fDF = CGameInstance::Get_Instance()->Get_TimeDelta(TEXT("Timer_60"));

	SetState(STATE_HIT, DIR_END);
}






CRedSnail * CRedSnail::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CRedSnail*		pInstance = new CRedSnail(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CRedSnail"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
CGameObject * CRedSnail::Clone(void* pArg)
{
	CRedSnail*		pInstance = new CRedSnail(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CRedSnail"));
		Safe_Release(pInstance);
	}

	return pInstance;
}




void CRedSnail::Collision(CGameObject * pOther)
{

}




void CRedSnail::Free()
{
	__super::Free();

}

