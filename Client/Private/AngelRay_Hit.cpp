#include "stdafx.h"
#include "..\Public\AngelRay_Hit.h"

#include "GameInstance.h"

CAngelRay_Hit::CAngelRay_Hit(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCreature(pGraphic_Device)
{
}
CAngelRay_Hit::CAngelRay_Hit(const CAngelRay_Hit & rhs)
	: CCreature(rhs),m_bCreate(false),m_bRender(true)
{
}




HRESULT CAngelRay_Hit::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}
HRESULT CAngelRay_Hit::Initialize(void * pArg)
{
	__super::Initialize(pArg);

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_fColRad = 0.1f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.f, 0.4f, 1.f));
	m_pTransformCom->Set_Scaled(3.f);
	//m_pTransformCom->Set_State(CTransform::STATE_LOOK, _float3(1.f, 0.f, 0.f));
	//m_pTransformCom->Rotation(_float3{ 0.f,1.f,0.f }, 70.f);
	
	m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_AngelRay_Hit"), 0.08f, CAnimator::STATE_LOOF);
	//SetState(STATE_IDLE, DIR_END);

	return S_OK;
}




HRESULT CAngelRay_Hit::SetUp_Components()
{
	{
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_AngelRay_Hit"), nullptr);
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




void CAngelRay_Hit::Tick(_float fTimeDelta)
{
	//m_pTransformCom->Go_L(fTimeDelta);
	/*switch (m_eCurState)
	{
	case Client::CAngelRay_Hit::STATE_IDLE:
		Tick_Idle(fTimeDelta);
		break;
	case Client::CAngelRay_Hit::STATE_MOVE:
		Tick_Move(fTimeDelta);
		break;
	case Client::CAngelRay_Hit::STATE_HIT:
		Tick_Hit(fTimeDelta);
		break;
	}*/

}
void CAngelRay_Hit::LateTick(_float fTimeDelta)
{
	/*if (m_pAnimatorCom->Get_AniInfo().eMode == CAnimator::STATE_ONCEEND)
		SetState(STATE_IDLE, m_eDir);*/

	if(m_bRender)
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
	
	
	if (m_pAnimatorCom->Get_AnimCount() == 5)
		m_bRender = false;
		
	

	
}
HRESULT CAngelRay_Hit::Render()
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





void CAngelRay_Hit::Tick_Idle(_float fTimeDelta)
{

}
void CAngelRay_Hit::Tick_Move(_float fTimeDelta)
{
}
void CAngelRay_Hit::Tick_Hit(_float fTimeDelta)
{
}




void CAngelRay_Hit::SetState(STATE eState, DIR eDir)
{
	/*if (m_eCurState == eState && m_eDir == eDir)
		return;

	m_eCurState = eState;
	m_eDir = eDir;
	SetAni();*/
}
void CAngelRay_Hit::SetAni()
{
	/*switch (m_eCurState)
	{
	case CAngelRay_Hit::STATE_IDLE:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_AngelRay_Attack"), 1.f, CAnimator::STATE_LOOF);
		break;
	case CAngelRay_Hit::STATE_MOVE:
	{

	}
	break;
	case CAngelRay_Hit::STATE_HIT:
	{

	}
	break;
	}*/
}






CAngelRay_Hit * CAngelRay_Hit::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CAngelRay_Hit*		pInstance = new CAngelRay_Hit(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CAngelRay_Hit"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
CGameObject * CAngelRay_Hit::Clone(void* pArg)
{
	CAngelRay_Hit*		pInstance = new CAngelRay_Hit(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CAngelRay_Hit"));
		Safe_Release(pInstance);
	}

	return pInstance;
}




void CAngelRay_Hit::Collision(CGameObject * pOther)
{
	_float fDF = CGameInstance::Get_Instance()->Get_TimeDelta(TEXT("Timer_60"));
	m_pTransformCom->Go_Left(fDF);
}




void CAngelRay_Hit::Free()
{
	__super::Free();
}

