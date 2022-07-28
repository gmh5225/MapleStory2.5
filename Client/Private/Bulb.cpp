#include "stdafx.h"
#include "..\Public\Bulb.h"

#include "GameInstance.h"

CBulb::CBulb(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCreature(pGraphic_Device)
{
}
CBulb::CBulb(const CBulb & rhs)
	: CCreature(rhs)
{
}




HRESULT CBulb::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}
HRESULT CBulb::Initialize(void * pArg)
{
	__super::Initialize(pArg);

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_sTag = "Tag_UI";

	m_fColRad = 1.f;	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(4.0f, 1.1f, 0.3f));
	m_pTransformCom->Set_Scaled(0.8f);

	SetState(STATE_IDLE, DIR_END);



	return S_OK;
}




HRESULT CBulb::SetUp_Components()
{
	{
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Bulb_Start"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Bulb_End"), nullptr);
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




void CBulb::Tick(_float fTimeDelta)
{

	switch (m_eCurState)
	{
	case Client::CBulb::STATE_IDLE:
		Tick_Idle(fTimeDelta);
		break;
	case Client::CBulb::STATE_MOVE:
		Tick_Move(fTimeDelta);
		break;
	case Client::CBulb::STATE_HIT:
		Tick_Hit(fTimeDelta);
		break;
	case Client::CBulb::STATE_CHASE:
		Tick_Chase(fTimeDelta);
		break;
	}

}
void CBulb::LateTick(_float fTimeDelta)
{
	if (m_pAnimatorCom->Get_AniInfo().eMode == CAnimator::STATE_ONCEEND)
		SetState(STATE_IDLE, m_eDir);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
	m_pColliderCom->Add_CollsionGroup(CCollider::COLLSION_UI, this);

	Set_Billboard();
}
HRESULT CBulb::Render()
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


	SetState(STATE_IDLE, m_eDir);

	return S_OK;
}





void CBulb::Tick_Idle(_float fTimeDelta)
{
}
void CBulb::Tick_Move(_float fTimeDelta)
{
}
void CBulb::Tick_Hit(_float fTimeDelta)
{
}

void CBulb::Tick_Chase(_float fTimeDelta)
{
}



void CBulb::SetState(STATE eState, DIR eDir)
{
	if (m_eCurState == eState && m_eDir == eDir)
		return;

	m_eCurState = eState;
	m_eDir = eDir;
	SetAni();
}
void CBulb::SetAni()
{
	switch (m_eCurState)
	{
	case CBulb::STATE_IDLE:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Bulb_Start"), 0.3f, CAnimator::STATE_LOOF);
		break;
	case CBulb::STATE_MOVE:
		break;
	case CBulb::STATE_HIT:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Bulb_End"), 0.3f, CAnimator::STATE_LOOF);
		break;
	case CBulb::STATE_CHASE:
		break;
	}
}

void CBulb::Damaged(CGameObject * pOther)
{
}






CBulb * CBulb::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBulb*		pInstance = new CBulb(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CBulb"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
CGameObject * CBulb::Clone(void* pArg)
{
	CBulb*		pInstance = new CBulb(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CBulb"));
		Safe_Release(pInstance);
	}

	return pInstance;
}




void CBulb::Collision(CGameObject * pOther)
{
	SetState(STATE_HIT, DIR_END);
}




void CBulb::Free()
{
	__super::Free();

}
