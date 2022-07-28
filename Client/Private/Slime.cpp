#include "stdafx.h"
#include "..\Public\Slime.h"

#include "GameInstance.h"
#include "RedPortion.h"
CSlime::CSlime(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCreature(pGraphic_Device)
{
}
CSlime::CSlime(const CSlime & rhs)
	: CCreature(rhs)
{
}




HRESULT CSlime::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}
HRESULT CSlime::Initialize(void * pArg)
{
	__super::Initialize(pArg);

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_sTag = "Tag_Monster";

	m_fColRad = 0.9f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(3.f, 0.5f, 0.f));
	m_pTransformCom->Set_Scaled(1.3f);

	SetState(STATE_IDLE, DIR_END);



	return S_OK;
}




HRESULT CSlime::SetUp_Components()
{
	{
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Slime_Idle"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Slime_Move"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Slime_Hit"), nullptr);
	
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Slime_MoveR"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Slime_HitR"), nullptr);
	}


	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(TransformDesc));

	TransformDesc.fSpeedPerSec = 1.2f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"), TEXT("Com_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;

	return S_OK;
}




void CSlime::Tick(_float fTimeDelta)
{

	switch (m_eCurState)
	{
	case Client::CSlime::STATE_IDLE:
		Tick_Idle(fTimeDelta);
		break;
	case Client::CSlime::STATE_MOVE:
		Tick_Move(fTimeDelta);
		break;
	case Client::CSlime::STATE_HIT:
		Tick_Hit(fTimeDelta);
		break;
	case Client::CSlime::STATE_CHASE:
		Tick_Chase(fTimeDelta);
		break;
	}

}
void CSlime::LateTick(_float fTimeDelta)
{
	if (m_pAnimatorCom->Get_AniInfo().eMode == CAnimator::STATE_ONCEEND)
		SetState(STATE_CHASE, m_eDir);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
	m_pColliderCom->Add_CollsionGroup(CCollider::COLLSION_MONSTER, this);

	Set_Billboard();
}
HRESULT CSlime::Render()
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





void CSlime::Tick_Idle(_float fTimeDelta)
{
}
void CSlime::Tick_Move(_float fTimeDelta)
{
}
void CSlime::Tick_Hit(_float fTimeDelta)
{
}

void CSlime::Tick_Chase(_float fTimeDelta)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_ComponentPtr(LEVEL_GAMEPLAY, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

	_float3 vPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);

	if (m_pTransformCom->Get_State(CTransform::STATE_POSITION).x < vPlayerPos.x)
		SetState(STATE_CHASE, DIR_R);
	else
		SetState(STATE_CHASE, DIR_L);

	m_pTransformCom->Chase(vPlayerPos, fTimeDelta);

	Safe_Release(pGameInstance);

}



void CSlime::SetState(STATE eState, DIR eDir)
{
	if (m_eCurState == eState && m_eDir == eDir)
		return;

	m_eCurState = eState;
	m_eDir = eDir;
	SetAni();
}
void CSlime::SetAni()
{
	switch (m_eCurState)
	{
	case CSlime::STATE_IDLE:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Slime_Idle"), 0.3f, CAnimator::STATE_LOOF);
	break;
	case CSlime::STATE_MOVE:
	{

	}
	break;
	case CSlime::STATE_HIT:
		if(m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Slime_HitR"), 0.5f, CAnimator::STATE_ONCE);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Slime_Hit"), 0.5f, CAnimator::STATE_ONCE);
	break;
	case CSlime::STATE_CHASE:
		if(m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Slime_MoveR"), 0.2f, CAnimator::STATE_LOOF);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Slime_Move"), 0.2f, CAnimator::STATE_LOOF);
		break;
	}
}

void CSlime::Damaged(CGameObject * pOther)
{	
	
	
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	//je_test:redportion appearance
	CRedPortion::REDPORTIONDESC RedPortionDesc;
	RedPortionDesc.vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_RedPortion"), LEVEL_GAMEPLAY, TEXT("Layer_Item"), &RedPortionDesc);
	//test_end
	CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_ComponentPtr(LEVEL_GAMEPLAY, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

	_float3 vPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);

	if (m_pTransformCom->Get_State(CTransform::STATE_POSITION).x < vPlayerPos.x)
		SetState(STATE_HIT, DIR_R);
	else
		SetState(STATE_HIT, DIR_L);

	Safe_Release(pGameInstance);
}






CSlime * CSlime::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSlime*		pInstance = new CSlime(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CSlime"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
CGameObject * CSlime::Clone(void* pArg)
{
	CSlime*		pInstance = new CSlime(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CSlime"));
		Safe_Release(pInstance);
	}

	return pInstance;
}




void CSlime::Collision(CGameObject * pOther)
{

}




void CSlime::Free()
{
	__super::Free();

}

