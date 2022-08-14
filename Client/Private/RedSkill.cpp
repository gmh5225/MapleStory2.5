#include "stdafx.h"
#include "..\Public\RedSkill.h"

#include "GameInstance.h"


CRedSkill::CRedSkill(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCreature(pGraphic_Device)
{
}
CRedSkill::CRedSkill(const CRedSkill & rhs)
	: CCreature(rhs)
{
}




HRESULT CRedSkill::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}
HRESULT CRedSkill::Initialize(void * pArg)
{
	__super::Initialize(pArg);

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_sTag = "Tag_Npc";

	m_fColRad = 1.f;	
	
	_float a = CGameInstance::Get_Instance()->Get_FloatRandom(-10, 10);
	_float b = CGameInstance::Get_Instance()->Get_Random(-10, 10);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.f + a, 1.f, 0.f + b));
	m_pTransformCom->Set_Scaled(5.f);

	SetState(STATE_IDLE, DIR_END);



	return S_OK;
}




HRESULT CRedSkill::SetUp_Components()
{
	CBoxCollider::BOXCOLCOMEDESC BoxColDesc;
	ZeroMemory(&BoxColDesc, sizeof(BoxColDesc));
	BoxColDesc.vScale = _float3{ 0.3f, 0.6f, 0.3f };
	BoxColDesc.vPivot = _float3{ 0.f, 0.f, 0.f };
	if (FAILED(__super::Add_BoxColComponent(LEVEL_STATIC, TEXT("Prototype_Component_BoxCollider"), &BoxColDesc)))
		return E_FAIL;

	{
		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_RedSkill"), nullptr);
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




void CRedSkill::Tick(_float fTimeDelta)
{

	switch (m_eCurState)
	{
	case Client::CRedSkill::STATE_IDLE:
		Tick_Idle(fTimeDelta);
		break;
	case Client::CRedSkill::STATE_MOVE:
		Tick_Move(fTimeDelta);
		break;
	case Client::CRedSkill::STATE_HIT:
		Tick_Hit(fTimeDelta);
		break;
	case Client::CRedSkill::STATE_CHASE:
		Tick_Chase(fTimeDelta);
		break;
	}

}
void CRedSkill::LateTick(_float fTimeDelta)
{
	Set_Billboard();

	if (m_pAnimatorCom->Get_AniInfo().eMode == CAnimator::STATE_ONCEEND)
		SetState(STATE_CHASE, m_eDir);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
	m_pColliderCom->Add_PushBoxCollsionGroup(CCollider::COLLSION_NPC, this);
}
HRESULT CRedSkill::Render()
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





void CRedSkill::Tick_Idle(_float fTimeDelta)
{
}
void CRedSkill::Tick_Move(_float fTimeDelta)
{
}
void CRedSkill::Tick_Hit(_float fTimeDelta)
{
}

void CRedSkill::Tick_Chase(_float fTimeDelta)
{
}



void CRedSkill::SetState(STATE eState, DIR eDir)
{
	if (m_eCurState == eState && m_eDir == eDir)
		return;

	m_eCurState = eState;
	m_eDir = eDir;
	SetAni();
}
void CRedSkill::SetAni()
{
	switch (m_eCurState)
	{
	case CRedSkill::STATE_IDLE:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_RedSkill"), 0.1f, CAnimator::STATE_LOOF);
		break;
	case CRedSkill::STATE_MOVE:
	{
	}
	break;
	case CRedSkill::STATE_HIT:
		break;
	case CRedSkill::STATE_CHASE:
		break;
	}
}

void CRedSkill::Damaged(CGameObject * pOther)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_ComponentPtr(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

	_float3 vPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);


	SetState(STATE_HIT, DIR_END);


	Safe_Release(pGameInstance);
}






CRedSkill * CRedSkill::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CRedSkill*		pInstance = new CRedSkill(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CRedSkill"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
CGameObject * CRedSkill::Clone(void* pArg)
{
	CRedSkill*		pInstance = new CRedSkill(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CRedSkill"));
		Safe_Release(pInstance);
	}

	return pInstance;
}




void CRedSkill::Collision(CGameObject * pOther)
{
}




void CRedSkill::Free()
{
	__super::Free();

}

