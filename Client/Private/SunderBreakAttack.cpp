#include "stdafx.h"
#include "..\Public\SunderBreakAttack.h"

#include "GameInstance.h"

CSunderBreakAttack::CSunderBreakAttack(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCreature(pGraphic_Device)
{
}
CSunderBreakAttack::CSunderBreakAttack(const CSunderBreakAttack & rhs)
	: CCreature(rhs)
{
}




HRESULT CSunderBreakAttack::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}
HRESULT CSunderBreakAttack::Initialize(void * pArg)
{
	__super::Initialize(pArg);

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_fColRad = 0.1f;

	m_pTransformCom->Set_Scaled(_float3(3.f,4.f,1.f));
	m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_SunderBreak_Attack"), 0.08f, CAnimator::STATE_LOOF);

	memcpy(&m_Desc, pArg, sizeof(SUNDERBREAKATTACKDESC));
	m_eDir = m_Desc.eDir;

	SetDirection();
	SetPosition(m_eDir);
	m_fYDistance = m_pTransformCom->Get_State(CTransform::STATE_POSITION).y;
	return S_OK;
}




HRESULT CSunderBreakAttack::SetUp_Components()
{
	{
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_SunderBreak_Attack"), nullptr);
	}


	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(TransformDesc));

	TransformDesc.fSpeedPerSec = 10.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"), TEXT("Com_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;

	return S_OK;
}




void CSunderBreakAttack::Tick(_float fTimeDelta)
{


}
void CSunderBreakAttack::LateTick(_float fTimeDelta)
{

	Set_Billboard();
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_MOVEALPHABLEND, this);
	m_pColliderCom->Add_CollsionGroup(CCollider::COLLSION_PLAYER_SKILL, this);

	if (m_pAnimatorCom->Get_AnimCount() == 14)
	{
		Set_Dead();
	}
	
}
HRESULT CSunderBreakAttack::Render()
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





void CSunderBreakAttack::Tick_Idle(_float fTimeDelta)
{

}
void CSunderBreakAttack::Tick_Move(_float fTimeDelta)
{
}
void CSunderBreakAttack::Tick_Hit(_float fTimeDelta)
{
}




void CSunderBreakAttack::SetState(STATE eState, DIR eDir)
{

}
void CSunderBreakAttack::SetDirection()
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
		m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 90.f, _float3(0.f, 0.f, -1.f), 90.f);
		break;
	case Client::CCreature::DIR_D:
		m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 270.f, _float3(0.f, 0.f, 1.f), 90.f);
		break;
	case Client::CCreature::DIR_LU:
		m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 45.f, _float3(1.f, 0.f, -1.f), 90.f);
		break;
	case Client::CCreature::DIR_RU:
		m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 135.f, _float3(-1.f, 0.f, -1.f), 90.f);
		break;
	case Client::CCreature::DIR_LD:
		m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), -45.f, _float3(1.f, 0.f, 1.f), 90.f);
		break;
	case Client::CCreature::DIR_RD:
		m_pTransformCom->RotationTwo(_float3(0.f, 1.f, 0.f), 225.f, _float3(-1.f, 0.f, 1.f), 90.f);
		break;
	case Client::CCreature::DIR_END:
		break;
	default:
		break;
	}
}
void CSunderBreakAttack::SetPosition(DIR eDir)
{
	CGameInstance* pInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pInstance);

	CTransform* m_pTarget = (CTransform*)pInstance->Get_ComponentPtr(LEVEL_GAMEPLAY, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

	Safe_Release(pInstance);

	Safe_Release(pInstance);
	_float3 vPosFix;
	switch (eDir)
	{
	case Client::CCreature::DIR_L:
		vPosFix = { -1.f,1.f,0.f };
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTarget->Get_State(CTransform::STATE_POSITION) + vPosFix);
		break;
	case Client::CCreature::DIR_R:
		vPosFix = { 1.f,-0.01f,0.f };
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTarget->Get_State(CTransform::STATE_POSITION) + vPosFix);
		break;
	case Client::CCreature::DIR_U:
		vPosFix = { 0.f,-0.01f,1.f };
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTarget->Get_State(CTransform::STATE_POSITION) + vPosFix);
		break;
	case Client::CCreature::DIR_D:
		vPosFix = { 0.f,-0.01f,-0.5f };
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTarget->Get_State(CTransform::STATE_POSITION) + vPosFix);
		break;
	case Client::CCreature::DIR_LU:
		vPosFix = { -1.f,-0.01f,1.f };
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTarget->Get_State(CTransform::STATE_POSITION) + vPosFix);
		break;
	case Client::CCreature::DIR_RU:
		vPosFix = { 1.f,-0.01f,1.f };
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTarget->Get_State(CTransform::STATE_POSITION) + vPosFix);
		break;
	case Client::CCreature::DIR_LD:
		vPosFix = { -1.f,-0.3f,-0.5f };
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTarget->Get_State(CTransform::STATE_POSITION) + vPosFix);
		break;
	case Client::CCreature::DIR_RD:
		vPosFix = { 1.f,-0.01f,-1.f };
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTarget->Get_State(CTransform::STATE_POSITION) + vPosFix);
		break;
	case Client::CCreature::DIR_END:

		break;
	default:
		break;
	}
}
void CSunderBreakAttack::MoveAttack(_float fTimeDelta)
{
	switch (m_eDir)
	{
	case Client::CCreature::DIR_L:
		m_pTransformCom->Go_L(fTimeDelta);
		break;
	case Client::CCreature::DIR_R:
		m_pTransformCom->Go_R(fTimeDelta);
		break;
	case Client::CCreature::DIR_U:
		m_pTransformCom->Go_U(fTimeDelta);
		break;
	case Client::CCreature::DIR_D:
		m_pTransformCom->Go_D(fTimeDelta);
		break;
	case Client::CCreature::DIR_LU:
		m_pTransformCom->Go_LU(fTimeDelta);
		break;
	case Client::CCreature::DIR_RU:
		m_pTransformCom->Go_RU(fTimeDelta);
		break;
	case Client::CCreature::DIR_LD:
		m_pTransformCom->Go_LD(fTimeDelta);
		break;
	case Client::CCreature::DIR_RD:
		m_pTransformCom->Go_RD(fTimeDelta);
		break;
	case Client::CCreature::DIR_END:
		break;
	default:
		break;
	}
}
void CSunderBreakAttack::SetAni()
{

}






CSunderBreakAttack * CSunderBreakAttack::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSunderBreakAttack*		pInstance = new CSunderBreakAttack(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CSunderBreakAttack"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
CGameObject * CSunderBreakAttack::Clone(void* pArg)
{
	CSunderBreakAttack*		pInstance = new CSunderBreakAttack(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CSunderBreakAttack"));
		Safe_Release(pInstance);
	}

	return pInstance;
}




void CSunderBreakAttack::Collision(CGameObject * pOther)
{
	if (pOther->Get_Tag() == "Tag_Monster")
	{

		if (1 < m_pOther.size())
			return;

		for (auto& TempOther : m_pOther)
		{
			if (TempOther == pOther)
				return;
		}

	/*	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);

		CAngelRay_Hit::ANGELHITDESC AngelDesc;
		CTransform* pTransform = (CTransform*)pOther->Get_ComponentPtr(TEXT("Com_Transform"));
		AngelDesc.vPos = pTransform->Get_State(CTransform::STATE_POSITION);

		pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_AngelRay_Hit"), LEVEL_GAMEPLAY, TEXT("Layer_Player_Skill"), &AngelDesc);
		Safe_Release(pGameInstance);*/


		m_pOther.push_back(pOther);
		// Safe_AddRef(pOther);

		pOther->Damaged(this);

		Set_Dead();
	}
}

HRESULT CSunderBreakAttack::Set_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphic_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphic_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	return S_OK;
}

HRESULT CSunderBreakAttack::Reset_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}




void CSunderBreakAttack::Free()
{
	__super::Free();
}

