#include "stdafx.h"
#include "..\Public\OrangeMushroom.h"

#include "GameInstance.h"
#include "QuestManager.h"

COrangeMushroom::COrangeMushroom(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCreature(pGraphic_Device)
{
}
COrangeMushroom::COrangeMushroom(const COrangeMushroom & rhs)
	: CCreature(rhs)
{
}

HRESULT COrangeMushroom::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}
HRESULT COrangeMushroom::Initialize(void * pArg)
{
	__super::Initialize(pArg);

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_sTag = "Tag_Monster";

	m_fColRad = 0.9f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(-2.f, -0.6f, -2.f));
	m_pTransformCom->Set_Scaled(1.3f);

	SetState(STATE_IDLE, DIR_END);



	return S_OK;
}




HRESULT COrangeMushroom::SetUp_Components()
{
	if (FAILED(__super::Add_BoxColComponent(LEVEL_STATIC, TEXT("Prototype_Component_BoxCollider"))))
		return E_FAIL;

	{
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_OrangeMushroom_Idle"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_OrangeMushroom_Move"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_OrangeMushroom_Hit"), nullptr);

		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_OrangeMushroom_MoveR"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_OrangeMushroom_HitR"), nullptr);
	}


	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(TransformDesc));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"), TEXT("Com_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;

	return S_OK;
}




void COrangeMushroom::Tick(_float fTimeDelta)
{

	switch (m_eCurState)
	{
	case Client::COrangeMushroom::STATE_IDLE:
		Tick_Idle(fTimeDelta);
		break;
	case Client::COrangeMushroom::STATE_MOVE:
		Tick_Move(fTimeDelta);
		break;
	case Client::COrangeMushroom::STATE_HIT:
		Tick_Hit(fTimeDelta);
		break;
	case Client::COrangeMushroom::STATE_CHASE:
		Tick_Chase(fTimeDelta);
		break;
	}

}
void COrangeMushroom::LateTick(_float fTimeDelta)
{
	if (m_pAnimatorCom->Get_AniInfo().eMode == CAnimator::STATE_ONCEEND)
		SetState(STATE_CHASE, m_eDir);


	__super::BoxColCom_Tick(m_pTransformCom);



	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
	m_pColliderCom->Add_CollsionGroup(CCollider::COLLSION_MONSTER, this);

	
}
HRESULT COrangeMushroom::Render()
{
	Set_Billboard();

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





void COrangeMushroom::Tick_Idle(_float fTimeDelta)
{

}
void COrangeMushroom::Tick_Move(_float fTimeDelta)
{
}
void COrangeMushroom::Tick_Hit(_float fTimeDelta)
{
}

void COrangeMushroom::Tick_Chase(_float fTimeDelta)
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




void COrangeMushroom::SetState(STATE eState, DIR eDir)
{
	if (m_eCurState == eState && m_eDir == eDir)
		return;

	m_eCurState = eState;
	m_eDir = eDir;
	SetAni();
}
void COrangeMushroom::SetAni()
{
	switch (m_eCurState)
	{
	case COrangeMushroom::STATE_IDLE:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_OrangeMushroom_Idle"), 1.f, CAnimator::STATE_LOOF);
	break;
	case COrangeMushroom::STATE_MOVE:
	{

	}
	break;
	case COrangeMushroom::STATE_HIT:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_OrangeMushroom_HitR"), 0.5f, CAnimator::STATE_ONCE);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_OrangeMushroom_Hit"), 0.5f, CAnimator::STATE_ONCE);
	break;
	case COrangeMushroom::STATE_CHASE:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_OrangeMushroom_MoveR"), 0.3f, CAnimator::STATE_LOOF);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_OrangeMushroom_Move"), 0.3f, CAnimator::STATE_LOOF);
	break;
	}
}




void COrangeMushroom::Damaged(CGameObject * pOther)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_ComponentPtr(LEVEL_GAMEPLAY, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

	_float3 vPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);

	if (m_pTransformCom->Get_State(CTransform::STATE_POSITION).x < vPlayerPos.x)
		SetState(STATE_HIT, DIR_R);
	else
		SetState(STATE_HIT, DIR_L);

	Safe_Release(pGameInstance);

	CQuestManager::Get_Instance()->Hunting(TEXT("OrangeMushroom"));
	Set_Dead();

}



COrangeMushroom * COrangeMushroom::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	COrangeMushroom*		pInstance = new COrangeMushroom(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : COrangeMushroom"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
CGameObject * COrangeMushroom::Clone(void* pArg)
{
	COrangeMushroom*		pInstance = new COrangeMushroom(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : COrangeMushroom"));
		Safe_Release(pInstance);
	}

	return pInstance;
}




void COrangeMushroom::Collision(CGameObject * pOther)
{

}




void COrangeMushroom::Free()
{
	__super::Free();

}

