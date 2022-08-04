#include "stdafx.h"
#include "..\Public\OrangeMushroom.h"

#include "GameInstance.h"
#include "QuestManager.h"
#include "Spawner.h"
#include "SpawnerManager.h"

COrangeMushroom::COrangeMushroom(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCreature(pGraphic_Device)
{
}
COrangeMushroom::COrangeMushroom(const COrangeMushroom & rhs)
	: CCreature(rhs)
{
}

HRESULT COrangeMushroom::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}
HRESULT COrangeMushroom::Initialize(void * pArg)
{
	__super::Initialize(pArg);

	m_iIndexNum = -1;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_sTag = "Tag_Monster";
	m_iHp = 3;


	CSpawner::SPAWNERINFO* pMonsterDesc = (CSpawner::SPAWNERINFO*)pArg;

	m_iIndexNum = pMonsterDesc->SpawnerNum;

	m_fColRad = pMonsterDesc->MonsterColRad;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, pMonsterDesc->MonsterPos);
	m_pTransformCom->Set_Scaled(1.f);
	m_bDir = false;

	m_fStartPos = pMonsterDesc->MonsterPos;

	// �������� ����������� ���������� �Ÿ��� �����Ѵ�
	m_iMove = CGameInstance::Get_Instance()->Get_Random(0, 4);
	m_fDistance = _float(CGameInstance::Get_Instance()->Get_Random(1, 5));


	switch (m_iMove)
	{
	case MOVE_R:
		SetState(STATE_MOVE, DIR_R);
		m_fEndPos.x = m_fStartPos.x + m_fDistance;
		break;
	case MOVE_L:
		SetState(STATE_MOVE, DIR_L);
		m_fEndPos.x = m_fStartPos.x - m_fDistance;
		break;
	case MOVE_U:
		SetState(STATE_MOVE, DIR_R);
		m_fEndPos.z = m_fStartPos.z + m_fDistance;
		break;
	case MOVE_D:
		SetState(STATE_MOVE, DIR_L);
		m_fEndPos.z = m_fStartPos.z - m_fDistance;
		break;
	case MOVE_END:
		SetState(STATE_IDLE, DIR_END);
		break;
	}


	return S_OK;
}




HRESULT COrangeMushroom::SetUp_Components()
{
	if (FAILED(__super::Add_BoxColComponent(LEVEL_STATIC, TEXT("Prototype_Component_BoxCollider"))))
		return E_FAIL;


	CBoxCollider::BOXCOLCOMEDESC BoxColDesc;
	ZeroMemory(&BoxColDesc, sizeof(BoxColDesc));
	BoxColDesc.vScale = _float3{ 0.5f, 1.f, 0.5f };
	BoxColDesc.vPivot = _float3{ 0.f, 0.f, 0.f };
	if (FAILED(__super::Add_BoxColComponent(LEVEL_STATIC, TEXT("Prototype_Component_BoxCollider"), &BoxColDesc)))
		return E_FAIL;

	{
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_OrangeMushroom_Idle"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_OrangeMushroom_Move"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_OrangeMushroom_Hit"), nullptr);

		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_OrangeMushroom_MoveR"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_OrangeMushroom_HitR"), nullptr);
	}


	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(TransformDesc));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"), TEXT("Com_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;

	return S_OK;
}




void COrangeMushroom::Tick(_float fTimeDelta)
{

	switch (m_eCurState)
	{
	case Client::COrangeMushroom::STATE_IDLE:
		Tick_Idle(fTimeDelta);
		break;
	case Client::COrangeMushroom::STATE_MOVE:
		Tick_Move(fTimeDelta);
		break;
	case Client::COrangeMushroom::STATE_HIT:
		Tick_Hit(fTimeDelta);
		break;
	case Client::COrangeMushroom::STATE_CHASE:
		Tick_Chase(fTimeDelta);
		break;
	}

	if (m_pTransformCom->Get_State(CTransform::STATE_POSITION).y < -10)
	{
		Set_Dead();
		CSpawnerManager::Get_Instance()->Check_MonsterIndex(m_iIndexNum);
	}

}
void COrangeMushroom::LateTick(_float fTimeDelta)
{
	if (m_pAnimatorCom->Get_AniInfo().eMode == CAnimator::STATE_ONCEEND)
		SetState(STATE_CHASE, m_eDir);


	m_pTransformCom->Go_Gravity(fTimeDelta);
	__super::BoxColCom_Tick(m_pTransformCom);
	m_pColliderCom->Add_PushBoxCollsionGroup(CCollider::COLLSION_MONSTER, this);
	m_pColliderCom->Add_SphereCollsionGroup(CCollider::COLLSION_MONSTER, this);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);

}
HRESULT COrangeMushroom::Render()
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

	
	if (CGameInstance::Get_Instance()->Key_Down(DIK_0))
	{
		if (temp)
			temp = false;
		else
			temp = true;
	}

	if (temp)
		__super::BoxColCom_Render(m_pTransformCom);


	return S_OK;
}





void COrangeMushroom::Tick_Idle(_float fTimeDelta)
{
	m_iMove = CGameInstance::Get_Instance()->Get_Random(0, 1000);

	switch (m_iMove)
	{
	case MOVE_R:
		SetState(STATE_MOVE, DIR_R);
		m_fEndPos.x = m_fStartPos.x + m_fDistance;
		break;
	case MOVE_L:
		SetState(STATE_MOVE, DIR_L);
		m_fEndPos.x = m_fStartPos.x - m_fDistance;
		break;
	case MOVE_U:
		SetState(STATE_MOVE, DIR_R);
		m_fEndPos.z = m_fStartPos.z + m_fDistance;
		break;
	case MOVE_D:
		SetState(STATE_MOVE, DIR_L);
		m_fEndPos.z = m_fStartPos.z - m_fDistance;
		break;
	}

}
void COrangeMushroom::Tick_Move(_float fTimeDelta)
{
	_float3 fPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	if (m_iMove == MOVE_R)
	{
		if (m_fEndPos.x <= fPos.x)		// ���� �Ÿ��� �̵� �Ÿ����� �۰ų� ��������
			m_bDir = true;
		else if (m_fStartPos.x > fPos.x)
			m_bDir = false;

		if (!m_bDir)
		{
			m_pTransformCom->Go_Right(fTimeDelta);
			SetState(STATE_MOVE, DIR_R);
		}
		else
		{
			m_pTransformCom->Go_Left(fTimeDelta);
			SetState(STATE_MOVE, DIR_L);
		}
	}
	else if (m_iMove == MOVE_L)
	{
		if (m_fEndPos.x >= fPos.x)		// ���� �Ÿ��� �̵� �Ÿ����� �۰ų� ��������
			m_bDir = true;
		else if (m_fStartPos.x < fPos.x)
			m_bDir = false;

		if (!m_bDir)
		{
			m_pTransformCom->Go_Left(fTimeDelta);
			SetState(STATE_MOVE, DIR_L);
		}
		else
		{
			m_pTransformCom->Go_Right(fTimeDelta);
			SetState(STATE_MOVE, DIR_R);
		}
	}
	else if (m_iMove == MOVE_U)
	{
		if (m_fEndPos.z <= fPos.z)		// ���� �Ÿ��� �̵� �Ÿ����� �۰ų� ��������
			m_bDir = true;
		else if (m_fStartPos.z > fPos.z)
			m_bDir = false;

		if (!m_bDir)
		{
			m_pTransformCom->Go_U(fTimeDelta);
			SetState(STATE_MOVE, DIR_R);
		}
		else
		{
			m_pTransformCom->Go_D(fTimeDelta);
			SetState(STATE_MOVE, DIR_L);
		}
	}
	else if (m_iMove == MOVE_D)
	{
		if (m_fEndPos.z >= fPos.z)		// ���� �Ÿ��� �̵� �Ÿ����� �۰ų� ��������
			m_bDir = true;
		else if (m_fStartPos.z < fPos.z)
			m_bDir = false;

		if (!m_bDir)
		{
			m_pTransformCom->Go_D(fTimeDelta);
			SetState(STATE_MOVE, DIR_R);
		}
		else
		{
			m_pTransformCom->Go_U(fTimeDelta);
			SetState(STATE_MOVE, DIR_L);
		}
	}
}
void COrangeMushroom::Tick_Hit(_float fTimeDelta)
{
}

void COrangeMushroom::Tick_Chase(_float fTimeDelta)
{
	if (GetKeyState('L') & 0x8000)
	{
		SetState(STATE_JUMP, m_eDir);
	}

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_ComponentPtr(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

	_float3 vPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);

	if (m_pTransformCom->Get_State(CTransform::STATE_POSITION).x < vPlayerPos.x)
	{
		SetState(STATE_CHASE, DIR_R);
		m_pTransformCom->Chase(vPlayerPos + _float3(-0.1f, 0.f, 0.1f), fTimeDelta);
	}
	else
	{
		SetState(STATE_CHASE, DIR_L);
		m_pTransformCom->Chase(vPlayerPos + _float3(0.1f, 0.f, 0.1f), fTimeDelta);
	}


	Safe_Release(pGameInstance);
}




void COrangeMushroom::SetState(STATE eState, DIR eDir)
{
	if (m_eCurState == eState && m_eDir == eDir)
		return;

	m_eCurState = eState;
	m_eDir = eDir;
	SetAni();

	if (m_eCurState == STATE_JUMP)
	{
		// *�߷� �ڵ�
		// Y�� ���� �ݴϴ�.
		m_pTransformCom->Set_Vel(4.0f);
	}
}
void COrangeMushroom::SetAni()
{
	switch (m_eCurState)
	{
	case COrangeMushroom::STATE_IDLE:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_OrangeMushroom_Idle"), 0.5f, CAnimator::STATE_LOOF);
	break;
	case COrangeMushroom::STATE_MOVE:
	{
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_OrangeMushroom_MoveR"), 0.3f, CAnimator::STATE_LOOF);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_OrangeMushroom_Move"), 0.3f, CAnimator::STATE_LOOF);
	}
	break;
	case COrangeMushroom::STATE_HIT:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_OrangeMushroom_HitR"), 0.5f, CAnimator::STATE_ONCE);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_OrangeMushroom_Hit"), 0.5f, CAnimator::STATE_ONCE);
	break;
	case COrangeMushroom::STATE_CHASE:
		if (m_eDir == DIR_R)
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_OrangeMushroom_MoveR"), 0.3f, CAnimator::STATE_LOOF);
		else
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_OrangeMushroom_Move"), 0.3f, CAnimator::STATE_LOOF);
	break;
	}
}




void COrangeMushroom::Damaged(CGameObject * pOther)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_ComponentPtr(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

	_float3 vPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);

	if (m_pTransformCom->Get_State(CTransform::STATE_POSITION).x < vPlayerPos.x)
		SetState(STATE_HIT, DIR_R);
	else
		SetState(STATE_HIT, DIR_L);

	Safe_Release(pGameInstance);

	--m_iHp;
	if (m_iHp == 0)
	{
		CQuestManager::Get_Instance()->Hunting(TEXT("OrangeMushroom"));
		CSpawnerManager::Get_Instance()->Check_MonsterIndex(m_iIndexNum);
		Set_Dead();
	}
	//
}



COrangeMushroom * COrangeMushroom::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	COrangeMushroom*		pInstance = new COrangeMushroom(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : COrangeMushroom"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
CGameObject * COrangeMushroom::Clone(void* pArg)
{
	COrangeMushroom*		pInstance = new COrangeMushroom(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : COrangeMushroom"));
		Safe_Release(pInstance);
	}

	return pInstance;
}




void COrangeMushroom::Collision(CGameObject * pOther)
{
	if (pOther->Get_Tag() == "Tag_Cube")
	{
		if (m_eCurState == STATE_JUMP)
		{
			if (Get_PushedY())
				SetState(STATE_IDLE, m_eDir);
		}
		//m_pTransformCom->Set_Vel(0.f);
	}
}




void COrangeMushroom::Free()
{
	__super::Free();

}

