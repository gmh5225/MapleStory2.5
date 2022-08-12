#include "stdafx.h"
#include "..\Public\GAS.h"

#include "GameInstance.h"
#include "QuestManager.h"
#include "UIManager.h"
#include "BlueMushmom.h"
#include "QuestManager.h"
#include "Spawner.h"

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
	m_iHp = 10;
	m_iIndexNum = -1;
	m_fCountDead = 0;

	m_iRandomPattern = 0;

	m_bPatterStart = false;

	m_fPatternCycle = 2;

	m_fJump = 0;
	m_fDJump = 0;
	m_fAttack = 0;
	m_fDash = 0;
	m_fEnd = 0;

	m_bTest = false;

	m_fColRad = 1.f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(5.f, 5.f, -5.f));
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

		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_DJump"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_DJumpR"), nullptr);

		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_TP"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_TPR"), nullptr);

		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_TPA"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GAS_TPAR"), nullptr);

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

	if (fabs(m_pTransformCom->Get_State(CTransform::STATE_POSITION).x - vPlayerPos.x) < 1.f)
		m_bPatterStart = true;


	CUIManager::Get_Instance()->Get_GASHp(m_iHp);

	if (m_bPatterStart)
		m_fPatternCycle += fTimeDelta;

	if (m_fPatternCycle > 5.f)
	{
		m_iRandomPattern = CGameInstance::Get_Instance()->Get_Random(1, 3);
		m_fPatternCycle = 0;
	}


	if (m_eCurState != STATE_HIT && m_eCurState != STATE_DIE)
	{

		if (m_iRandomPattern == 0)
		{
			if (vPlayerPos.x > m_pTransformCom->Get_State(CTransform::STATE_POSITION).x)
				SetState(STATE_CHASE, DIR_R);
			else
				SetState(STATE_CHASE, DIR_L);
		}

		else if (m_iRandomPattern == 1) // ��������
		{
			if (m_eDir == DIR_R)
				SetState(STATE_JUMP, DIR_R);
			else
				SetState(STATE_JUMP, DIR_L);
		}

		else if (m_iRandomPattern == 2) // �Ϲݰ���
		{
			if (m_eDir == DIR_R)
				SetState(STATE_ATTACK, DIR_R);
			else
				SetState(STATE_ATTACK, DIR_L);
		}

		else if (m_iRandomPattern == 3) // �ڷ���Ʈ
		{
			if (m_eDir == DIR_R)
				SetState(STATE_DASH, DIR_R);
			else
				SetState(STATE_DASH, DIR_L);
		}

		else if (m_iRandomPattern == 4) // ������ ��ȯ
		{
			if (m_eDir == DIR_R)
				SetState(STATE_DJUMP, DIR_R);
			else
				SetState(STATE_DJUMP, DIR_L);
		}


		else if (m_iRandomPattern == 100)	// ���� ����
		{
			if (vPlayerPos.x > m_pTransformCom->Get_State(CTransform::STATE_POSITION).x)
				SetState(STATE_END, DIR_R);
			else
				SetState(STATE_END, DIR_L);
		}

	}


	Safe_Release(pGameInstance);


	CUIManager::Get_Instance()->Get_GASHp(m_iHp);

	switch (m_eCurState)
	{
	case STATE_IDLE:
		Tick_Idle(fTimeDelta);
		break;
	case STATE_HIT:
		Tick_Hit(fTimeDelta);
		break;
	case STATE_CHASE:
		Tick_Chase(fTimeDelta);
		break;
	case STATE_DASH:
		Tick_Dash(fTimeDelta);
		break;
	case STATE_JUMP:
		Tick_Jump(fTimeDelta);
		break;
	case STATE_DJUMP:
		Tick_DJump(fTimeDelta);
		break;
	case STATE_ATTACK:
		Tick_Attack(fTimeDelta);
		break;
	case STATE_DIE:
		Tick_Die(fTimeDelta);
		break;
	case STATE_END:
		Tick_End(fTimeDelta);
		break;
	}

}

void CGAS::LateTick(_float fTimeDelta)
{
	m_pTransformCom->Go_Gravity(fTimeDelta);
	__super::BoxColCom_Tick(m_pTransformCom);

	_float3 Mushpos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	if (Mushpos.y < -1.f)
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(Mushpos.x, 3.5f, Mushpos.z));

	if (m_pAnimatorCom->Get_AniInfo().eMode == CAnimator::STATE_ONCEEND)
		if (m_eCurState != STATE_DIE && m_eCurState != STATE_ATTACK)
			SetState(STATE_CHASE, m_eDir);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_BOSS, this);
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


	m_pTransformCom->Chase(vPlayerPos + _float3(0.1f,0,0), fTimeDelta * 3);

	Safe_Release(pGameInstance);
}

void CGAS::Tick_Jump(_float fTimeDelta)
{
	m_fJump += fTimeDelta;
	if (m_fJump > 2.0f)
	{
		m_iRandomPattern = 0;
		m_fJump = 0;
	}
}

void CGAS::Tick_DJump(_float fTimeDelta)
{
	m_fDJump += fTimeDelta;


	if (m_fDJump > 2.f && !m_bTest)
	{
		m_bTest = true;

		CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);

		CSpawner::SPAWNERINFO m_Slime;


		m_Slime.GAS = TEXT("GAS");
		m_Slime.Level = LEVEL_GAS;
		m_Slime.MonsterColRad = 1.f;

		m_Slime.MonsterPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

		float random = pGameInstance->Get_FloatRandom(-2, 2);
		float random2 = pGameInstance->Get_FloatRandom(-2, 2);
		float random3 = pGameInstance->Get_FloatRandom(0, 2);

		m_Slime.MonsterPos += _float3{ random, random3, random2 };

		if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Slime"), LEVEL_GAS, TEXT("Layer_Monster"), &m_Slime)))
			int a = 0;


		for (int i = 0; i < 7; ++i)
		{
			m_Slime.MonsterPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

			random = pGameInstance->Get_FloatRandom(-5, 5);
			random2 = pGameInstance->Get_FloatRandom(-5, 5);
			random3 = pGameInstance->Get_FloatRandom(3, 7);

			m_Slime.MonsterPos += _float3{ random, random3, random2 };

			if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Slime"), LEVEL_GAS, TEXT("Layer_Monster"), &m_Slime)))
				int a = 0;
		}

		Safe_Release(pGameInstance);
	}
	if (m_fDJump > 2.2f)
	{
		m_iRandomPattern = 0;
		m_fDJump = 0;
		m_bTest = false;
	}
}

void CGAS::Tick_Dash(_float fTimeDelta)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_ComponentPtr(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

	_float3 vPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);

	m_fDash += fTimeDelta;
	if (m_fDash > 1.6f)
	{
		m_iRandomPattern = 100;
		m_fDash = 0;
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPlayerPos + _float3(0.f,1.f,0.f));
	}

	Safe_Release(pGameInstance);
}

void CGAS::Tick_End(_float fTimeDelta)
{
	m_fEnd += fTimeDelta;
	if (m_fEnd > 0.8f)
	{
		m_iRandomPattern = 0;
		m_fEnd = 0;
	}
}

void CGAS::Tick_Attack(_float fTimeDelta)
{
	m_fAttack += fTimeDelta;
	if (m_fAttack > 2.0f)
	{
		m_iRandomPattern = 0;
		m_fAttack = 0;
	}
}


void CGAS::Tick_Die(_float fTimeDelta)
{
	m_fCountDead += fTimeDelta;
	if (m_fCountDead >= 10.0f)
	{
		Set_Dead();
	}
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
	case STATE_IDLE:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_Idle"), 0.1f, CAnimator::STATE_LOOF);
		break;
	case STATE_MOVE:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_MoveR"), 0.1f, CAnimator::STATE_LOOF);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_Move"), 0.1f, CAnimator::STATE_LOOF);
		break;
	case STATE_HIT:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_HitR"), 0.5f, CAnimator::STATE_ONCE);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_Hit"), 0.5f, CAnimator::STATE_ONCE);
		break;
	case STATE_CHASE:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_MoveR"), 0.1f, CAnimator::STATE_LOOF);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_Move"), 0.1f, CAnimator::STATE_LOOF);
		break;
	case STATE_DIE:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_DieR"), 0.1f, CAnimator::STATE_ONCE);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_Die"), 0.1f, CAnimator::STATE_ONCE);
		break;
	case STATE_JUMP:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_JumpR"), 0.1f, CAnimator::STATE_ONCE);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_Jump"), 0.1f, CAnimator::STATE_ONCE);
		break;

	case STATE_ATTACK:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_AttackR"), 0.1f, CAnimator::STATE_ONCE);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_Attack"), 0.1f, CAnimator::STATE_ONCE);
		break;

	case STATE_DASH:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_TPR"), 0.1f, CAnimator::STATE_ONCE);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_TP"), 0.1f, CAnimator::STATE_ONCE);
		break;

	case STATE_DJUMP:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_DJumpR"), 0.1f, CAnimator::STATE_ONCE);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_DJump"), 0.1f, CAnimator::STATE_ONCE);
		break;

	case STATE_END:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_TPAR"), 0.15f, CAnimator::STATE_ONCE);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_GAS_TPA"), 0.15f, CAnimator::STATE_ONCE);
		break;
	}
}

void CGAS::Damaged(CGameObject * pOther)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_ComponentPtr(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

	_float3 vPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);

	if (m_eCurState == STATE_CHASE || m_eCurState == STATE_IDLE)
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
		CQuestManager::Get_Instance()->Hunting(TEXT("GAS"));
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
