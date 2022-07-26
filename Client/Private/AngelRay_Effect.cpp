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
	CGameInstance* pInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pInstance);

	m_pTarget = (CTransform*)pInstance->Get_ComponentPtr(LEVEL_GAMEPLAY, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

	Safe_Release(pInstance);

	m_fColRad = 0.1f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTarget->Get_State(CTransform::STATE_POSITION));
	m_pTransformCom->Set_Scaled(5.f);
	
	m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_AngelRay_Effect"), 0.08f, CAnimator::STATE_LOOF);
	memcpy(&m_eDir, pArg, sizeof(DIR));
	SetDirection();
	//SetState(STATE_IDLE, DIR_END);
	//m_pTransformCom->Rotation(_float3(0.f, 1.f, 0.f), 45.f);
	/*m_pTransformCom->Rotation(_float3(0.f, 1.f, 0.f), 45.f);
	*/
	/*m_pTransformCom->Set_State(CTransform::STATE_LOOK, _float3(0.f,0.f,1.f)*5.f);
	m_pTransformCom->Set_State(CTransform::STATE_UP, _float3(0.f, 1.f, 0.f)*5.f);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, _float3(1.f, 0.f, 0.f)*5.f);*/
	//m_pTransformCom->Rotation(_float3(0.f, 1.f, 0.f), 180.f);

	







	/*_float3		vScale = m_pTransformCom->Get_Scaled();

	_float3		vRight = _float3(1.f, 0.f, 0.f) * 5.f;
	_float3		vUp = _float3(0.f, 1.f, 0.f) * 5.f;
	_float3		vLook = _float3(0.f, 0.f, 1.f) * 5.f;

	_float4x4	RotationMatrix;
	_float test = D3DXToRadian(180.f);
	D3DXMatrixRotationAxis(&RotationMatrix, &vUp, test);

	D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
	D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight);
	m_pTransformCom->Set_State(CTransform::STATE_UP, vUp);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, vLook);*/

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

	

	/*m_pTransformCom->Set_State(CTransform::STATE_LOOK, _float3(-1.f,0.f,1.f)*5.f);
	m_pTransformCom->Set_State(CTransform::STATE_UP, _float3(1.f, 1.f, 0.f)*5.f);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, _float3(-1.f, 0.f, 1.f)*5.f);*/

	

	/*m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_pTarget->Get_State(CTransform::STATE_LOOK)*10.f);
	m_pTransformCom->Set_State(CTransform::STATE_UP, m_pTarget->Get_State(CTransform::STATE_UP)*10.f);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, m_pTarget->Get_State(CTransform::STATE_RIGHT)*10.f);*/
	//m_pTransformCom->LookAt(m_pTarget->Get_State(CTransform::STATE_POSITION));
	//m_pTransformCom->Rotation(_float3(0.f, 1.f, 0.f), 45.f);
	//m_pTransformCom->Rotation(, 90.f);



}
void CAngelRay_Effect::LateTick(_float fTimeDelta)
{
	/*if (m_pAnimatorCom->Get_AniInfo().eMode == CAnimator::STATE_ONCEEND)
		SetState(STATE_IDLE, m_eDir);*/

	if(m_bRender)
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_ALPHABLEND, this);
	
	if (m_pAnimatorCom->Get_AnimCount() == 6 && m_bCreate == false)
	{
		CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);

		pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_AngelRay_Attack"), LEVEL_GAMEPLAY, TEXT("Layer_Player_Skill"),&m_eDir);
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
void CAngelRay_Effect::SetDirection()
{
	
	switch (m_eDir)
	{
	case Client::CCreature::DIR_L:
		m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 0.f, _float3(1.f, 0.f, 0.f), 90.f);
		break;
	case Client::CCreature::DIR_R:
		m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 180.f, _float3(-1.f, 0.f, 0.f), 90.f);
		break;
	case Client::CCreature::DIR_U:
		m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 90.f, _float3(0.f, 0.f, 1.f), 90.f);
		break;
	case Client::CCreature::DIR_D:
		m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 270.f, _float3(0.f, 0.f, -1.f), 90.f);
		break;
	case Client::CCreature::DIR_LU:
		m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 45.f, _float3(-1.f, 0.f, 1.f), 90.f);
		break;
	case Client::CCreature::DIR_RU:
		m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 135.f, _float3(1.f, 0.f, 1.f), 90.f);
		break;
	case Client::CCreature::DIR_LD:
		m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), -45.f, _float3(-1.f, 0.f, -1.f), 90.f);
		break;
	case Client::CCreature::DIR_RD:
		m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 225.f, _float3(1.f, 0.f, -1.f), 90.f);
		break;
	case Client::CCreature::DIR_END:
		break;
	default:
		break;
	}
	//U
	//m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 90.f, _float3(0.f, 0.f, 1.f), 90.f);

	//D
	//m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 270.f, _float3(0.f, 0.f, 1.f), 90.f);

	//L
	//m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 0.f, _float3(1.f, 0.f, 0.f), 90.f);

	//R
	//m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 180.f, _float3(1.f, 0.f, 0.f), 90.f);

	//RU
	//m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 135.f, _float3(1.f, 0.f, 1.f), 90.f);

	//RD
	//m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 225.f, _float3(1.f, 0.f, -1.f), 90.f);

	//LU
	//m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 45.f, _float3(-1.f, 0.f, 1.f), 90.f);

	//LD
	//m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), -45.f, _float3(-1.f, 0.f, -1.f), 90.f);

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

	m_pGraphic_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphic_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 1);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	

	return S_OK;

}

HRESULT CAngelRay_Effect::Reset_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_vLookTemp);
	return S_OK;
}




void CAngelRay_Effect::Free()
{
	__super::Free();
}

