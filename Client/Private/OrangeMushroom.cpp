#include "stdafx.h"
#include "..\Public\OrangeMushroom.h"

#include "GameInstance.h"

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

	m_fColRad = 0.1f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(5.f, 0.4f, 0.f));
	m_pTransformCom->Set_Scaled(1.1f);

	SetState(STATE_IDLE, DIR_END);

	return S_OK;
}




HRESULT COrangeMushroom::SetUp_Components()
{
	{
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_OrangeMushroom_Idle"), nullptr);
	}


	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(TransformDesc));

	TransformDesc.fSpeedPerSec = 4.f;
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
	}

}
void COrangeMushroom::LateTick(_float fTimeDelta)
{
	if (m_pAnimatorCom->Get_AniInfo().eMode == CAnimator::STATE_ONCEEND)
		SetState(STATE_IDLE, m_eDir);


	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
	m_pColliderCom->Add_CollsionGroup(CCollider::COLLSION_MONSTER, this);
}
HRESULT COrangeMushroom::Render()
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





void COrangeMushroom::Tick_Idle(_float fTimeDelta)
{

}
void COrangeMushroom::Tick_Move(_float fTimeDelta)
{
}
void COrangeMushroom::Tick_Hit(_float fTimeDelta)
{
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
	{

	}
	break;
	}
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
	_float fDF = CGameInstance::Get_Instance()->Get_TimeDelta(TEXT("Timer_60"));
	m_pTransformCom->Go_Left(fDF);
}




void COrangeMushroom::Free()
{
	__super::Free();
}

