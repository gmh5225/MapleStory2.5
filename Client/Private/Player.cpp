#include "stdafx.h"
#include "..\Public\Player.h"

#include "GameInstance.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCreature(pGraphic_Device)
{
}
CPlayer::CPlayer(const CPlayer & rhs)
	: CCreature(rhs)
{
}




HRESULT CPlayer::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}
HRESULT CPlayer::Initialize(void * pArg)
{
	__super::Initialize(pArg);

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_sTag = "Tag_Player";

	m_fColRad = 0.5f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.f, 0.6f, 0.f));
	m_pTransformCom->Set_Scaled(2.0f);

	SetState(STATE_IDLE, DIR_D);
	
	return S_OK;
}




HRESULT CPlayer::SetUp_Components()
{
	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(TransformDesc));

	TransformDesc.fSpeedPerSec = 4.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"), TEXT("Com_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;


	{
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_U"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_D"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_L"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_R"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_LU"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_RU"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_LD"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_RD"), nullptr);
	}
	{
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_U"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_D"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_L"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_R"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_LU"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_RU"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_LD"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_RD"), nullptr);
	}
	{
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Jump_U"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Jump_D"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Jump_L"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Jump_R"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Jump_LU"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Jump_RU"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Jump_LD"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Jump_RD"), nullptr);
	}
	{
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack_U"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack_D"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack_L"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack_R"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack_LU"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack_RU"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack_LD"), nullptr);
		m_pAnimatorCom->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack_RD"), nullptr);
	}

	return S_OK;
}




void CPlayer::Tick(_float fTimeDelta)
{

	switch (m_eCurState)
	{
	case Client::CPlayer::STATE_IDLE:
		GetKeyInput(fTimeDelta);
		break;
	case Client::CPlayer::STATE_MOVE:
		GetKeyInput(fTimeDelta);
		break;
	case Client::CPlayer::STATE_JUMP:
		break;
	case Client::CPlayer::STATE_ATTACK:
		break;
	}
	
}
void CPlayer::LateTick(_float fTimeDelta)
{
	if (m_pAnimatorCom->Get_AniInfo().eMode == CAnimator::STATE_ONCEEND)
		SetState(STATE_IDLE, m_eDir);

	
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
	m_pColliderCom->Add_CollsionGroup(CCollider::COLLSION_PLAYER, this);
}
HRESULT CPlayer::Render()
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





void CPlayer::SetAni()
{
	switch (m_eCurState)
	{
	case CPlayer::STATE_IDLE:
	{
		switch (m_eDir)
		{
		case Client::CPlayer::DIR_L:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Idle_L"), 0.05f, CAnimator::STATE_LOOF);
			break;
		case Client::CPlayer::DIR_R:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Idle_R"), 0.05f, CAnimator::STATE_LOOF);
			break;
		case Client::CPlayer::DIR_U:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Idle_U"), 0.05f, CAnimator::STATE_LOOF);
			break;
		case Client::CPlayer::DIR_D:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Idle_D"), 0.05f, CAnimator::STATE_LOOF);
			break;
		case Client::CPlayer::DIR_LU:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Idle_LU"), 0.05f, CAnimator::STATE_LOOF);
			break;
		case Client::CPlayer::DIR_RU:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Idle_RU"), 0.05f, CAnimator::STATE_LOOF);
			break;
		case Client::CPlayer::DIR_LD:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Idle_LD"), 0.05f, CAnimator::STATE_LOOF);
			break;
		case Client::CPlayer::DIR_RD:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Idle_RD"), 0.05f, CAnimator::STATE_LOOF);
			break;
		}
	}
		break;
	case CPlayer::STATE_MOVE:
	{
		switch (m_eDir)
		{
		case Client::CPlayer::DIR_L:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Move_L"), 0.05f, CAnimator::STATE_LOOF);
			break;
		case Client::CPlayer::DIR_R:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Move_R"), 0.05f, CAnimator::STATE_LOOF);
			break;
		case Client::CPlayer::DIR_U:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Move_U"), 0.05f, CAnimator::STATE_LOOF);
			break;
		case Client::CPlayer::DIR_D:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Move_D"), 0.05f, CAnimator::STATE_LOOF);
			break;
		case Client::CPlayer::DIR_LU:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Move_LU"), 0.05f, CAnimator::STATE_LOOF);
			break;
		case Client::CPlayer::DIR_RU:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Move_RU"), 0.05f, CAnimator::STATE_LOOF);
			break;
		case Client::CPlayer::DIR_LD:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Move_LD"), 0.05f, CAnimator::STATE_LOOF);
			break;
		case Client::CPlayer::DIR_RD:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Move_RD"), 0.05f, CAnimator::STATE_LOOF);
			break;
		}
	}
		break;
	case CPlayer::STATE_JUMP:
	{
		switch (m_eDir)
		{
		case Client::CPlayer::DIR_L:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Jump_L"), 0.05f, CAnimator::STATE_ONCE);
			break;
		case Client::CPlayer::DIR_R:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Jump_R"), 0.05f, CAnimator::STATE_ONCE);
			break;
		case Client::CPlayer::DIR_U:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Jump_U"), 0.05f, CAnimator::STATE_ONCE);
			break;
		case Client::CPlayer::DIR_D:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Jump_D"), 0.05f, CAnimator::STATE_ONCE);
			break;
		case Client::CPlayer::DIR_LU:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Jump_LU"), 0.05f, CAnimator::STATE_ONCE);
			break;
		case Client::CPlayer::DIR_RU:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Jump_RU"), 0.05f, CAnimator::STATE_ONCE);
			break;
		case Client::CPlayer::DIR_LD:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Jump_LD"), 0.05f, CAnimator::STATE_ONCE);
			break;
		case Client::CPlayer::DIR_RD:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Jump_RD"), 0.05f, CAnimator::STATE_ONCE);
			break;
		}
	}
		break;
	case CPlayer::STATE_ATTACK:
	{
		switch (m_eDir)
		{
		case Client::CPlayer::DIR_L:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Attack_L"), 0.05f, CAnimator::STATE_ONCE);
			break;
		case Client::CPlayer::DIR_R:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Attack_R"), 0.05f, CAnimator::STATE_ONCE);
			break;
		case Client::CPlayer::DIR_U:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Attack_U"), 0.05f, CAnimator::STATE_ONCE);
			break;
		case Client::CPlayer::DIR_D:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Attack_D"), 0.05f, CAnimator::STATE_ONCE);
			break;
		case Client::CPlayer::DIR_LU:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Attack_LU"), 0.05f, CAnimator::STATE_ONCE);
			break;
		case Client::CPlayer::DIR_RU:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Attack_RU"), 0.05f, CAnimator::STATE_ONCE);
			break;
		case Client::CPlayer::DIR_LD:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Attack_LD"), 0.05f, CAnimator::STATE_ONCE);
			break;
		case Client::CPlayer::DIR_RD:
			m_pAnimatorCom->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Attack_RD"), 0.05f, CAnimator::STATE_ONCE);
			break;
		}
	}
		break;
	}
}
void CPlayer::GetKeyInput(_float fTimeDelta)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	if (GetKeyState(VK_UP) & 0x8000)
	{
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			SetState(STATE_MOVE, DIR_RU);
			m_pTransformCom->Go_RU(fTimeDelta);
		}
		else if (GetKeyState(VK_LEFT) & 0x8000)
		{
			SetState(STATE_MOVE, DIR_LU);
			m_pTransformCom->Go_LU(fTimeDelta);
		}
		else
		{
			SetState(STATE_MOVE, DIR_U);
			m_pTransformCom->Go_U(fTimeDelta);
		}
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			SetState(STATE_MOVE, DIR_RD);
			m_pTransformCom->Go_RD(fTimeDelta);
		}
		else if (GetKeyState(VK_LEFT) & 0x8000)
		{
			SetState(STATE_MOVE, DIR_LD);
			m_pTransformCom->Go_LD(fTimeDelta);
		}
		else
		{
			SetState(STATE_MOVE, DIR_D);
			m_pTransformCom->Go_D(fTimeDelta);
		}
	}
	else if (GetKeyState(VK_LEFT) & 0x8000)
	{
		if (GetKeyState(VK_UP) & 0x8000)
		{
			SetState(STATE_MOVE, DIR_LU);
			m_pTransformCom->Go_LU(fTimeDelta);

		}
		else if (GetKeyState(VK_DOWN) & 0x8000)
		{
			SetState(STATE_MOVE, DIR_LD);
			m_pTransformCom->Go_LD(fTimeDelta);
		}
		else
		{
			SetState(STATE_MOVE, DIR_L);
			m_pTransformCom->Go_L(fTimeDelta);
		}
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		if (GetKeyState(VK_UP) & 0x8000)
		{
			SetState(STATE_MOVE, DIR_RU);
			m_pTransformCom->Go_RU(fTimeDelta);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000)
		{
			SetState(STATE_MOVE, DIR_RD);
			m_pTransformCom->Go_RD(fTimeDelta);
		}
		else
		{
			SetState(STATE_MOVE, DIR_R);
			m_pTransformCom->Go_R(fTimeDelta);
		}
	}
	else
	{
		SetState(STATE_IDLE, m_eDir);
	}

	if (GetKeyState('Z') & 0x8000)
	{
		SetState(STATE_ATTACK, m_eDir);
	}

	if (GetKeyState('X') & 0x8000)
	{
		SetState(STATE_JUMP, m_eDir);
	}

	if (GetKeyState('A') & 0x8000)
	{
		CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);

		CAngelRay_Effect::ANGELEFFECTDESC AngelDECS;
		AngelDECS.eDir = m_eDir;
		
		pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_AngelRay_Effect"), LEVEL_GAMEPLAY, TEXT("Layer_Skill"), &AngelDECS);
		SetState(STATE_ATTACK, m_eDir);
		Safe_Release(pGameInstance);
	}
}




HRESULT CPlayer::Set_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);	
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 50);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	return S_OK;
}
HRESULT CPlayer::Reset_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	m_pTransformCom->CulRUByLook(m_vLookTemp);
	//m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_vLookTemp);

	return S_OK;
}






CPlayer * CPlayer::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CPlayer*		pInstance = new CPlayer(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CPlayer"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
CGameObject * CPlayer::Clone(void* pArg)
{
	CPlayer*		pInstance = new CPlayer(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Created : CPlayer"));
		Safe_Release(pInstance);
	}

	return pInstance;
}




void CPlayer::Collision(CGameObject * pOther)
{
	if (pOther->Get_Tag() == "Tag_Monster")
	{

	}
}





void CPlayer::Free()
{
	__super::Free();
}

