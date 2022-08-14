#include "stdafx.h"
#include "..\Public\Bulb.h"

#include "GameInstance.h"
#include "QuestManager.h"
#include "CutSceneManager.h"

CBulb::CBulb(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCreature(pGraphic_Device),
	  m_iQuestState(0)
{
}
CBulb::CBulb(const CBulb & rhs)
	: CCreature(rhs)
{
}




HRESULT CBulb::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}
HRESULT CBulb::Initialize(void * pArg)
{
	__super::Initialize(pArg);

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_sTag = "Tag_UI";

	m_fColRad = 2.f;	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(9.1f, 7.0f, -0.6f));
	m_pTransformCom->Set_Scaled(1.2f);

	if (!g_bStaticClone)
	{
		// ����Ʈ false �ʱ�ȭ �� ����Ʈ �������� �ʱ�ȭ
		CQuestManager::Get_Instance()->Check_End_Quest();
		CQuestManager::Get_Instance()->QuestPrepare();
	}


	SetState(STATE_IDLE, DIR_END);

	return S_OK;
}




HRESULT CBulb::SetUp_Components()
{
	{
		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Bulb_Start"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Bulb_End"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Bulb_Progress"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Bulb_NoQuest"), nullptr);
	}

	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(TransformDesc));

	TransformDesc.fSpeedPerSec = 0.5f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"), TEXT("Com_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;




	return S_OK;
}




void CBulb::Tick(_float fTimeDelta)
{
}

void CBulb::LateTick(_float fTimeDelta)
{
	if (m_pAnimatorCom->Get_AniInfo().eMode == CAnimator::STATE_ONCEEND)
		SetState(STATE_IDLE, m_eDir);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
	m_pColliderCom->Add_SphereCollsionGroup(CCollider::COLLSION_UI, this);

	Set_Billboard();
}
HRESULT CBulb::Render()
{
	if (!(CCutSceneManager::Get_Instance()->Get_jangRander()))
		return S_OK;

	SetAni();
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


	SetState(STATE_IDLE, m_eDir);

	return S_OK;
}





void CBulb::Tick_Idle(_float fTimeDelta)
{
}
void CBulb::Tick_Move(_float fTimeDelta)
{
}
void CBulb::Tick_Hit(_float fTimeDelta)
{
}

void CBulb::Tick_Chase(_float fTimeDelta)
{
}



void CBulb::SetState(STATE eState, DIR eDir)
{
	if (m_eCurState == eState && m_eDir == eDir)
		return;

	m_eCurState = eState;
	m_eDir = eDir;
	SetAni();
}
void CBulb::SetAni()
{
	m_iQuestState = CQuestManager::Get_Instance()->Set_QuestState();
	switch (m_iQuestState)
	{
	case CQuestManager::QUEST_PREPARE:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Bulb_Start"), 0.3f, CAnimator::STATE_LOOF);
		break;
	case CQuestManager::QUEST_PROGRESS:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Bulb_Progress"), 0.3f, CAnimator::STATE_LOOF);
		break;
	case CQuestManager::QUEST_CLEAR:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Bulb_End"), 0.3f, CAnimator::STATE_LOOF);
		break;
	case CQuestManager::QUEST_END:
		m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Bulb_NoQuest"), 0.3f, CAnimator::STATE_ONCE);
		break;
	}
}

void CBulb::Damaged(CGameObject * pOther)
{
}






CBulb * CBulb::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBulb*		pInstance = new CBulb(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CBulb"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
CGameObject * CBulb::Clone(void* pArg)
{
	CBulb*		pInstance = new CBulb(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CBulb"));
		Safe_Release(pInstance);
	}

	return pInstance;
}




void CBulb::Collision(CGameObject * pOther)
{

		// �÷��̾�� �浹�� ���·� �����̽��ٸ� ������ ����Ʈ ���� ä���� ���
		if ((CGameInstance::Get_Instance()->Key_Down(DIKEYBOARD_SPACE)))
		{
			CQuestManager::Get_Instance()->Check_Start_Quest();
			if (CQuestManager::Get_Instance()->Get_QuestNum() == 0)
				CQuestManager::Get_Instance()->Set_First();

		}
}




void CBulb::Free()
{
	__super::Free();

}
