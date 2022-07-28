#include "stdafx.h"
#include "..\Public\RedPortion.h"

#include "GameInstance.h"


CRedPortion::CRedPortion(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCreature(pGraphic_Device)
{
}
CRedPortion::CRedPortion(const CRedPortion & rhs)
	: CCreature(rhs)
{
}

HRESULT CRedPortion::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}
HRESULT CRedPortion::Initialize(void * pArg)
{
	__super::Initialize(pArg);
	
	if (FAILED(SetUp_Components()))
		return E_FAIL;
	m_sTag = "Tag_Item";
	
	memcpy(&m_Desc, pArg, sizeof(REDPORTIONDESC));
	m_Desc.iNum = 0;
	m_fColRad = 0.1f;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION,m_Desc.vPos);
	
	m_pTransformCom->Set_Scaled(0.3f);
	m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_RedPortion"), 0.08f, CAnimator::STATE_ONCE);

	m_eDir = DIR_END;

	
	return S_OK;
}

HRESULT CRedPortion::SetUp_Components()
{
	{
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_RedPortion"), nullptr);
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

void CRedPortion::Tick(_float fTimeDelta)
{
	//몬스터에 생성돼서 터지는 모양
	//플레이어가 줍는 모양
	
}
void CRedPortion::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_MOVEALPHABLEND, this);
	m_pColliderCom->Add_CollsionGroup(CCollider::COLLISION_ITEM, this);
	SetDirection();
}

HRESULT CRedPortion::Render()
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

void CRedPortion::Collision(CGameObject * pOther)
{
	if (pOther->Get_Tag() == "Tag_Player")
	{	//플레이어와 충돌 시 Player 에서 z 키를 누르면 소지 갯수 증가시키기 
		CRedPortion::REDPORTIONDESC RedPortionDesc;
		RedPortionDesc.iNum += 1;
	}
}


void CRedPortion::Appearance(_float fTimeDelta)
{
	switch (m_eDir)
	{
	case Client::CCreature::DIR_L:
		break;
	case Client::CCreature::DIR_R:
		break;
	case Client::CCreature::DIR_U:
		break;
	case Client::CCreature::DIR_D:
		break;
	case Client::CCreature::DIR_LU:
		break;
	case Client::CCreature::DIR_RU:
		break;
	case Client::CCreature::DIR_LD:
		break;
	case Client::CCreature::DIR_RD:
		break;
	case Client::CCreature::DIR_END:
		break;
	default:
		break;
	}
}
void CRedPortion::Effect()
{
	/*CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CPlayer* pPlayer = (CPlayer*)pGameInstance->Get_ObjectPtr(LEVEL_GAMEPLAY, TEXT("Layer_Player"),0);
	*/
	//이건 아마 인벤토리메니저에서 
}
void CRedPortion::SetDirection()
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
void CRedPortion::SetPosition(DIR eDir)
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
		vPosFix = { -1.f,-0.01f,0.f };
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

void CRedPortion::SetAni()
{
	
}

CRedPortion * CRedPortion::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CRedPortion*		pInstance = new CRedPortion(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CRedPortion"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
CGameObject * CRedPortion::Clone(void* pArg)
{
	CRedPortion*		pInstance = new CRedPortion(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CRedPortion"));
		Safe_Release(pInstance);
	}

	return pInstance;
}



HRESULT CRedPortion::Set_RenderState()
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
HRESULT CRedPortion::Reset_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

void CRedPortion::Free()
{
	__super::Free();
}

