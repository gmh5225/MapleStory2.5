#include "stdafx.h"
#include "..\Public\AngelRay_Effect.h"

#include "GameInstance.h"

CAngelRay_Effect::CAngelRay_Effect(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCreature(pGraphic_Device)
{
}
CAngelRay_Effect::CAngelRay_Effect(const CAngelRay_Effect & rhs)
	: CCreature(rhs),m_bCreate(false),m_bRender(true)
{
}




HRESULT CAngelRay_Effect::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}
HRESULT CAngelRay_Effect::Initialize(void * pArg)
{
	__super::Initialize(pArg);

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_fColRad = 0.1f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.f, 2.4f, 1.f));
	m_pTransformCom->Set_Scaled(5.f);
	//m_pTransformCom->Set_State(CTransform::STATE_LOOK, _float3(1.f, 0.f, 0.f));
	//m_pTransformCom->Rotation(_float3{ 0.f,1.f,0.f }, 70.f);
	
	m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_AngelRay_Effect"), 0.08f, CAnimator::STATE_LOOF);
	//SetState(STATE_IDLE, DIR_END);

	return S_OK;
}




HRESULT CAngelRay_Effect::SetUp_Components()
{
	{
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_AngelRay_Effect"), nullptr);
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




void CAngelRay_Effect::Tick(_float fTimeDelta)
{
	//m_pTransformCom->Go_L(fTimeDelta);
	/*switch (m_eCurState)
	{
	case Client::CAngelRay_Effect::STATE_IDLE:
		Tick_Idle(fTimeDelta);
		break;
	case Client::CAngelRay_Effect::STATE_MOVE:
		Tick_Move(fTimeDelta);
		break;
	case Client::CAngelRay_Effect::STATE_HIT:
		Tick_Hit(fTimeDelta);
		break;
	}*/

}
void CAngelRay_Effect::LateTick(_float fTimeDelta)
{
	/*if (m_pAnimatorCom->Get_AniInfo().eMode == CAnimator::STATE_ONCEEND)
		SetState(STATE_IDLE, m_eDir);*/

	if(m_bRender)
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
	
	if (m_pAnimatorCom->Get_AnimCount() == 6 && m_bCreate == false)
	{
		CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);

		pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_AngelRay_Attack"), LEVEL_GAMEPLAY, TEXT("Layer_Player_Skill"));
		m_bCreate = true;
		Safe_Release(pGameInstance);
	}

	if (m_pAnimatorCom->Get_AnimCount() == 12)
	{
		m_bRender = false;
	}
		
	

	
}
HRESULT CAngelRay_Effect::Render()
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





void CAngelRay_Effect::Tick_Idle(_float fTimeDelta)
{

}
void CAngelRay_Effect::Tick_Move(_float fTimeDelta)
{
}
void CAngelRay_Effect::Tick_Hit(_float fTimeDelta)
{
}




void CAngelRay_Effect::SetState(STATE eState, DIR eDir)
{
	/*if (m_eCurState == eState && m_eDir == eDir)
		return;

	m_eCurState = eState;
	m_eDir = eDir;
	SetAni();*/
}
void CAngelRay_Effect::SetAni()
{
	/*switch (m_eCurState)
	{
	case CAngelRay_Effect::STATE_IDLE:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_AngelRay_Attack"), 1.f, CAnimator::STATE_LOOF);
		break;
	case CAngelRay_Effect::STATE_MOVE:
	{

	}
	break;
	case CAngelRay_Effect::STATE_HIT:
	{

	}
	break;
	}*/
}






CAngelRay_Effect * CAngelRay_Effect::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CAngelRay_Effect*		pInstance = new CAngelRay_Effect(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CAngelRay_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
CGameObject * CAngelRay_Effect::Clone(void* pArg)
{
	CAngelRay_Effect*		pInstance = new CAngelRay_Effect(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CAngelRay_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}




void CAngelRay_Effect::Collision(CGameObject * pOther)
{

}

HRESULT CAngelRay_Effect::Set_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 100);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	return S_OK;
}

HRESULT CAngelRay_Effect::Reset_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}




void CAngelRay_Effect::Free()
{
	__super::Free();
}

