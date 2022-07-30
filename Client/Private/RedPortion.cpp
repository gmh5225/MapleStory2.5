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

	m_fColRad = 0.1f;

	//몬스터 pos 넣어주기
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CTransform* pMonsterTransform = (CTransform*)pGameInstance->Get_ComponentPtr(LEVEL_GAMEPLAY, TEXT("Layer_Monster"), TEXT("Com_Transform"), 0);

	Safe_Release(pGameInstance);
	_float3 vMonsterPos = pMonsterTransform->Get_State(CTransform::STATE_POSITION);

	m_sTag = "Tag_Item";
	
	memcpy(&m_Desc, pArg, sizeof(REDPORTIONDESC));
	m_Desc.iNum = 0;
	m_Desc.eItemState = ITEM_APPEAR;
	m_fColRad = 0.1f;

	 m_pTransformCom->Set_State(CTransform::STATE_POSITION,m_Desc.vPos);
	
	m_pTransformCom->Set_Scaled(0.3f);

	m_eDir = DIR_END;
	
	a = 0;
	bPlusY = true;
	return S_OK;
}

HRESULT CRedPortion::SetUp_Components()
{
	{
		if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_RedPortion"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
			return E_FAIL;
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

void CRedPortion::Tick(_float fTimeDelta)//틱은 1초에 60번 돈다
{	//APPEAR 튕겨나간 후에 상태 IDEL 로 바꿔주기 
	//IDLE
	//PICKED
		_float3 m_vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
		if (a < 60 && bPlusY)//a가 60 보다 작고 true 면
		{
			m_vPos.y += 0.3f* fTimeDelta;	 //pos를 위로 올려준다
			a++;//a를 1 올려준다.
		}
		else
			bPlusY = false;

		if (a > 0 && !bPlusY)//false가 돼서 여기로 들어온다
		{
			m_vPos.y -= 0.3f* fTimeDelta;
			a--;
		}
		else
			bPlusY = true;

		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vPos);
	}
	
	

void CRedPortion::LateTick(_float fTimeDelta)
{
	Compute_CamDistance(m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_MOVEALPHABLEND, this);
	m_pColliderCom->Add_SphereCollsionGroup(CCollider::COLLISION_ITEM, this);
	SetDirection();
}

HRESULT CRedPortion::Render()
{
	Set_Billboard();

	if (FAILED(m_pTransformCom->Bind_WorldMatrix()))
		return E_FAIL;

	if (FAILED(m_pTextureCom->Bind_Texture(1)))
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

