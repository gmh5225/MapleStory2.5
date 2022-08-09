#include "stdafx.h"
#include "..\Public\BlackWizard.h"
#include "GameInstance.h"
#include "BlackWizardAttack1.h"


CBlackWizard::CBlackWizard(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CCreature(pGraphic_Device)
{
}

CBlackWizard::CBlackWizard(const CBlackWizard & rhs)
	:CCreature(rhs)
{
}

HRESULT CBlackWizard::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}

HRESULT CBlackWizard::Initialize(void * pArg)
{
	__super::Initialize(pArg);

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_sTag = "Tag_Monster";
	m_eCurState = STATE_APPEAR;
	SetAni();
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(-9.f, 4.f, -1.f));
	m_pTransformCom->Set_Scaled(6.f);

	SetShadow(LEVEL_GAMEPLAY, 1.5f);

	return S_OK;
}

void CBlackWizard::Tick(_float fTimeDelta)
{
}

void CBlackWizard::LateTick(_float fTimeDelta)
{
	if (m_pAnimatorCom->Get_AniInfo().eMode == CAnimator::STATE_ONCEEND)
	{
		Pattern();
		SetState();
	}
	Fix_Scale();

	__super::BoxColCom_Tick(m_pTransformCom);

	m_pColliderCom->Add_BoxCollsionGroup(CCollider::COLLSION_MONSTER, this);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_ALPHABLEND, this);

}

HRESULT CBlackWizard::Render()
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


	__super::BoxColCom_Render(m_pTransformCom);


	return S_OK;
}

void CBlackWizard::Collision(CGameObject * pOther)
{
}

void CBlackWizard::SetState()
{

	m_eCurState = (STATE)CGameInstance::Get_Instance()->Get_Random(STATE_STAND, STATE_END-1);
	SetAni();
}

void CBlackWizard::Pattern()
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	switch (m_eCurState)
	{
	case Client::CBlackWizard::STATE_APPEAR:
		break;
	case Client::CBlackWizard::STATE_STAND:
		break;
	case Client::CBlackWizard::STATE_SKILL1:
		pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_BlackWizardAttack1"), LEVEL_STATIC, TEXT("Layer_Monster_Skill"));
		break;
	case Client::CBlackWizard::STATE_END:
		break;
	default:
		break;
	}
	Safe_Release(pGameInstance);
}

void CBlackWizard::Fix_Scale()
{
	switch (m_eCurState)
	{
	case Client::CBlackWizard::STATE_APPEAR:
		m_pTransformCom->Set_Scaled(6.f);
		break;
	case Client::CBlackWizard::STATE_STAND:
		m_pTransformCom->Set_Scaled(_float3{ 5.f,6.f,5.f });
		break;
	case Client::CBlackWizard::STATE_SKILL1:
		m_pTransformCom->Set_Scaled(6.f);
		break;
	case Client::CBlackWizard::STATE_END:
		break;
	default:
		break;
	}
}

void CBlackWizard::SetAni()
{
	switch (m_eCurState)
	{
	case Client::CBlackWizard::STATE_APPEAR:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_BlackWizard_Appear"), 0.1f, CAnimator::STATE_ONCE);
		break;
	case Client::CBlackWizard::STATE_STAND:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_BlackWizard_Stand"), 0.1f, CAnimator::STATE_ONCE);
		break;
	case Client::CBlackWizard::STATE_SKILL1:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_BlackWizard_Skill1"), 0.1f, CAnimator::STATE_ONCE);
		break;
	case Client::CBlackWizard::STATE_END:
		break;
	default:
		break;
	}
}

void CBlackWizard::Damaged(CGameObject * pOther)
{
}

HRESULT CBlackWizard::Set_RenderState()
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

HRESULT CBlackWizard::Reset_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

HRESULT CBlackWizard::SetUp_Components()
{
	CBoxCollider::BOXCOLCOMEDESC BoxColDesc;
	ZeroMemory(&BoxColDesc, sizeof(BoxColDesc));
	BoxColDesc.vScale = _float3{ 0.5f, 0.8f, 0.5f };
	BoxColDesc.vPivot = _float3{ 0.f, 0.f, 0.f };
	if (FAILED(__super::Add_BoxColComponent(LEVEL_STATIC, TEXT("Prototype_Component_BoxCollider"), &BoxColDesc)))
		return E_FAIL;

	{
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_BlackWizard_Appear"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_BlackWizard_Stand"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_BlackWizard_Skill1"), nullptr);
	}

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"), TEXT("Com_Transform"), (CComponent**)&m_pTransformCom)))
		return E_FAIL;

	return S_OK;
}

CBlackWizard * CBlackWizard::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBlackWizard*	pInstance = new CBlackWizard(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CBlackWizard"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBlackWizard::Clone(void * pArg)
{
	CBlackWizard*	pInstance = new CBlackWizard(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CBlackWizard"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBlackWizard::Free()
{
	__super::Free();
}

