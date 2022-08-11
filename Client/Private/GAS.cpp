#include "stdafx.h"
#include "..\Public\GAS.h"

#include "GameInstance.h"
#include "QuestManager.h"
#include "UIManager.h"
#include "BlueMushmom.h"

CGAS::CGAS(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCreature(pGraphic_Device)
{
}
CGAS::CGAS(const CGAS & rhs)
	: CCreature(rhs)
{
}




HRESULT CGAS::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}
HRESULT CGAS::Initialize(void * pArg)
{
	__super::Initialize(pArg);

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_sTag = "Tag_Monster";
	m_iHp = 3;
	m_iIndexNum = -1;
	m_fCountDead = 0;
	m_fCountJump = 5.f;
	m_bAttack = false;
	m_fCountLanding = 0.f;
	m_bLanding = false;
	m_fCountLand = 0.f;

	CUIManager::Get_Instance()->Get_BlueMushmomHp(m_iHp);

	vPos.y = m_pTransformCom->Get_State(CTransform::STATE_POSITION).y;

	m_fColRad = 1.f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(37.f, 15.f, -9.f));
	m_pTransformCom->Set_Scaled(10.f);

	SetState(STATE_IDLE, DIR_END);

	SetShadow(LEVEL_HENESYS, 4.5f);

	return S_OK;
}




HRESULT CGAS::SetUp_Components()
{
	CBoxCollider::BOXCOLCOMEDESC BoxColDesc;
	ZeroMemory(&BoxColDesc, sizeof(BoxColDesc));
	BoxColDesc.vScale = _float3{ 3.f, 5.f, 3.f };
	BoxColDesc.vPivot = _float3{ 0.f, 0.f, 0.f };
	if (FAILED(__super::Add_BoxColComponent(LEVEL_STATIC, TEXT("Prototype_Component_BoxCollider"), &BoxColDesc)))
		return E_FAIL;


	{
		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_Move"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_MoveR"), nullptr);

		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_Hit"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_HitR"), nullptr);

		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_Die"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_DieR"), nullptr);

		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_Attack"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_AttackR"), nullptr);

		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_Jump"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_JumpR"), nullptr);

		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_Idle"), nullptr);

		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_Skill"), nullptr);
	}


	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(TransformDesc));

	TransformDesc.fSpeedPerSec = 0.3f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"), TEXT("Com_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;

	return S_OK;
}

void CGAS::Die()
{
	if (m_eDir == DIR_L)
	{
		SetState(STATE_DIE, DIR_L);
	}
	else if (m_eDir == DIR_R)
	{
		SetState(STATE_DIE, DIR_R);
	}
	//m_fColRad = 0;
}





void CGAS::Tick(_float fTimeDelta)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_ComponentPtr(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

	_float3 vPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);

	m_fCountJump += fTimeDelta;

	//if (vPlayerPos.x < 37.f)
	//{
	//	SetState(STATE_END, DIR_END);
	//	m_iHp = 3;
	//}

	if (fabs(m_pTransformCom->Get_State(CTransform::STATE_POSITION).x - vPlayerPos.x) < 2.f)
	{
		if (m_fCountJump >= 10.f && m_eCurState != STATE_ATTACK)
		{
			if (m_eCurState != STATE_HIT && m_eCurState != STATE_DIE)
			{
			/*	if (m_eDir == DIR_R)
					SetState(STATE_ATTACK, DIR_R);
				else
					SetState(STATE_ATTACK, DIR_L);*/
			}
		}
	}

	else if (fabs(m_pTransformCom->Get_State(CTransform::STATE_POSITION).x - vPlayerPos.x) < 2.f)
	{
		if (m_eCurState != STATE_HIT && m_eCurState != STATE_DIE &&  m_eCurState != STATE_ATTACK)
			if (m_eDir == DIR_R)
				SetState(STATE_CHASE, DIR_R);
			else
				SetState(STATE_CHASE, DIR_L);
	}

	Safe_Release(pGameInstance);


	CUIManager::Get_Instance()->Get_BlueMushmomHp(m_iHp);

	switch (m_eCurState)
	{
	case Client::CBlueMushmom::STATE_IDLE:
		Tick_Idle(fTimeDelta);
		break;
	case Client::CBlueMushmom::STATE_MOVE:
		Tick_Move(fTimeDelta);
		break;
	case Client::CBlueMushmom::STATE_HIT:
		Tick_Hit(fTimeDelta);
		break;
	case Client::CBlueMushmom::STATE_CHASE:
		Tick_Chase(fTimeDelta);
		break;
	case Client::CBlueMushmom::STATE_ATTACK:
		Tick_Attack(fTimeDelta);
		break;
	case Client::CBlueMushmom::STATE_DIE:
		Tick_Die(fTimeDelta);
		break;
	case Client::CBlueMushmom::STATE_END:
		Tick_End(fTimeDelta);
		break;
	}

}

void CGAS::LateTick(_float fTimeDelta)
{
	m_pTransformCom->Go_Gravity(fTimeDelta);
	__super::BoxColCom_Tick(m_pTransformCom);

	_float3 Mushpos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	if (Mushpos.y < 3.5f)
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(Mushpos.x, 3.5f, Mushpos.z));

	if (m_pAnimatorCom->Get_AniInfo().eMode == CAnimator::STATE_ONCEEND)
		if (m_eCurState != STATE_DIE && m_eCurState != STATE_ATTACK)
			SetState(STATE_CHASE, m_eDir);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_ALPHABLEND, this);
	m_pColliderCom->Add_PushBoxCollsionGroup(CCollider::COLLSION_MONSTER, this);
	m_pColliderCom->Add_BoxCollsionGroup(CCollider::COLLSION_MONSTER, this);

	Set_Billboard();
}
HRESULT CGAS::Render()
{
	if (FAILED(m_pTransformCom->Bind_WorldMatrix()))
		return E_FAIL;


	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphic_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphic_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	_float fDF = CGameInstance::Get_Instance()->Get_TimeDelta(TEXT("Timer_60"));
	if (FAILED(m_pAnimatorCom->Play_Ani(1.f * fDF)))
		return E_FAIL;

	//if (FAILED(Set_RenderState()))
	//	return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphic_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphic_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pVIBufferCom->Render();

	if (FAILED(Reset_RenderState()))
		return E_FAIL;

	return S_OK;
}





void CGAS::Tick_Idle(_float fTimeDelta)
{
}
void CGAS::Tick_Move(_float fTimeDelta)
{
}
void CGAS::Tick_Hit(_float fTimeDelta)
{
}

void CGAS::Tick_Chase(_float fTimeDelta)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_ComponentPtr(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

	_float3 vPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);

	if (m_pTransformCom->Get_State(CTransform::STATE_POSITION).x < vPlayerPos.x)
		SetState(STATE_CHASE, DIR_R);
	else
		SetState(STATE_CHASE, DIR_L);


	m_pTransformCom->Chase(vPlayerPos, fTimeDelta);

	Safe_Release(pGameInstance);
}

void CGAS::Tick_Attack(_float fTimeDelta)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_ComponentPtr(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

	_float3 vPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);


	// 내려오고 나서 상태를 바꾸는 시간
	m_fCountLand += fTimeDelta;

	//어느정도 시간이 지나고 점프를 시키는 시간
	if (!m_bLanding)
		m_fCountLanding += fTimeDelta;

	if (m_fCountLanding > 0.5f)
	{
		m_pTransformCom->Set_Vel(30.0f);
		m_fCountJump = 0;
		m_fCountLanding = 0;
		m_bLanding = true;
	}

	// 점프를 시작하고 5초 있다가 상태를 쫒아가게 바꿈
	if (m_fCountLand > 3.5f)
	{
		if (m_eDir == DIR_R)
			SetState(STATE_CHASE, DIR_R);
		else
			SetState(STATE_CHASE, DIR_L);
		m_bLanding = false;
		m_fCountLand = 0;
	}

	if (5.5f < m_pTransformCom->Get_State(CTransform::STATE_POSITION).y)
		m_pTransformCom->Chase(vPlayerPos, fTimeDelta * 5);

	Safe_Release(pGameInstance);
}


void CGAS::Tick_Die(_float fTimeDelta)
{
	m_fCountDead += fTimeDelta;
	if (m_fCountDead >= 20.0f)
		Set_Dead();
}

void CGAS::Tick_End(_float fTimeDelta)
{
	if (m_pTransformCom->Get_State(CTransform::STATE_POSITION).x >= 42.9f)
		SetState(STATE_IDLE, DIR_END);
	else
		m_pTransformCom->Chase(_float3(43.f, 10.f, -7.f), fTimeDelta * 5);
}



void CGAS::SetState(STATE eState, DIR eDir)
{
	if (m_eCurState == eState && m_eDir == eDir)
		return;

	m_eCurState = eState;
	m_eDir = eDir;
	SetAni();
}
void CGAS::SetAni()
{
	switch (m_eCurState)
	{
	case CBlueMushmom::STATE_IDLE:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_Skill"), 0.1f, CAnimator::STATE_LOOF);
		break;
	case CBlueMushmom::STATE_MOVE:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_MoveR"), 0.1f, CAnimator::STATE_LOOF);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_Move"), 0.1f, CAnimator::STATE_LOOF);
		break;
	case CBlueMushmom::STATE_HIT:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_HitR"), 0.5f, CAnimator::STATE_ONCE);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_Hit"), 0.5f, CAnimator::STATE_ONCE);
		break;
	case CBlueMushmom::STATE_CHASE:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_MoveR"), 0.1f, CAnimator::STATE_LOOF);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_Move"), 0.1f, CAnimator::STATE_LOOF);
		break;
	case CBlueMushmom::STATE_DIE:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_DieR"), 0.1f, CAnimator::STATE_ONCE);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_Die"), 0.1f, CAnimator::STATE_ONCE);
		break;

	case CBlueMushmom::STATE_ATTACK:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_AttackR"), 0.5f, CAnimator::STATE_ONCE);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_Attack"), 0.5f, CAnimator::STATE_ONCE);
		break;

	case CBlueMushmom::STATE_END:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_MoveR"), 0.1f, CAnimator::STATE_LOOF);
		break;
	}
}

void CGAS::Damaged(CGameObject * pOther)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_ComponentPtr(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

	_float3 vPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);

	if (m_eCurState != STATE_ATTACK)
	{
		if (m_pTransformCom->Get_State(CTransform::STATE_POSITION).x < vPlayerPos.x)
			SetState(STATE_HIT, DIR_R);
		else
			SetState(STATE_HIT, DIR_L);
	}


	Safe_Release(pGameInstance);

	--m_iHp;
	if (m_iHp <= 0)
	{
		CQuestManager::Get_Instance()->Hunting(TEXT("BlueMushmom"));
		Die();
	}

}






CGAS * CGAS::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CGAS*		pInstance = new CGAS(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CGAS"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
CGameObject * CGAS::Clone(void* pArg)
{
	CGAS*		pInstance = new CGAS(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CGAS"));
		Safe_Release(pInstance);
	}

	return pInstance;
}




void CGAS::Collision(CGameObject * pOther)
{
}




void CGAS::Free()
{
	__super::Free();

}

