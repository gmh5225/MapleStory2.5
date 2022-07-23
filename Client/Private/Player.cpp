#include "stdafx.h"
#include "..\Public\Player.h"

#include "GameInstance.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CPlayer::CPlayer(const CPlayer & rhs)
	: CGameObject(rhs)
{
}

HRESULT CPlayer::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPlayer::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.f, 0.5f, 0.f));
	
	m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_RIGHT), 45.f);

	return S_OK;
}

void CPlayer::Tick(_float fTimeDelta)
{
	if (GetKeyState(VK_UP) & 0x8000)
	{
		m_pAnimator->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Move_U"), 0.05f, CAnimator::STATE_LOOF);
	}

	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		m_pAnimator->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Move_D"), 0.05f, CAnimator::STATE_LOOF);
	}

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_pAnimator->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Move_L"), 0.05f, CAnimator::STATE_LOOF);
	}

	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_pAnimator->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Move_R"), 0.05f, CAnimator::STATE_LOOF);
	}

	if (GetKeyState('Z') & 0x8000)
	{
		m_pAnimator->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Attack_RU"), 0.05f, CAnimator::STATE_ONCE);
	}
	
}

void CPlayer::LateTick(_float fTimeDelta)
{
	
	if (m_pAnimator->Get_AniInfo().eMode == CAnimator::STATE_ONCEEND)
		m_pAnimator->Set_AniInfo(TEXT("Prototype_Component_Texture_Player_Idle_RU"), 0.05f, CAnimator::STATE_LOOF);

	
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CPlayer::Render()
{

	if (FAILED(m_pTransformCom->Bind_WorldMatrix()))
		return E_FAIL;	

	//if (FAILED(m_pAnimator->Bind_Texture(TEXT("Prototype_Component_Texture_Player"))))
	//	return E_FAIL;

	_float fDF = CGameInstance::Get_Instance()->Get_TimeDelta(TEXT("Timer_60"));

	if (FAILED(m_pAnimator->Play_Ani(1.f * fDF)))
		return E_FAIL;

	if (FAILED(Set_RenderState()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	if (FAILED(Reset_RenderState()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer::Set_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);	
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 254);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	return S_OK;
}

HRESULT CPlayer::Reset_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

HRESULT CPlayer::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), TEXT("Com_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), TEXT("Com_VIBuffer"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	//if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
	//	return E_FAIL;


	/* For.Com_Texture */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Animator"), TEXT("Com_Animator"), (CComponent**)&m_pAnimator)))
		return E_FAIL;

	m_pAnimator->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Jump_RU"), nullptr);
	m_pAnimator->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack_RU"), nullptr);
	m_pAnimator->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_RU"), nullptr);

	m_pAnimator->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_U"), nullptr);
	m_pAnimator->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_D"), nullptr);
	m_pAnimator->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_L"), nullptr);
	m_pAnimator->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_R"), nullptr);
	
	m_pAnimator->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_LU"), nullptr);
	m_pAnimator->Create_Texture(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_LD"), nullptr);


	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(TransformDesc));

	TransformDesc.fSpeedPerSec = 5.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"), TEXT("Com_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;


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

void CPlayer::Free()
{
	__super::Free();

	Safe_Release(m_pAnimator);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
}

