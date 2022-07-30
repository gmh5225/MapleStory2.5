#include "stdafx.h"
#include "..\Public\SkillUpBtn.h"
#include "GameInstance.h"
#include "SkillManager.h"
#include "SunCrossInfo.h"


CSkillUpBtn::CSkillUpBtn(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CSkillUpBtn::CSkillUpBtn(const CSkillUpBtn& rhs)
	: CUI(rhs)
{
}


HRESULT CSkillUpBtn::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CSkillUpBtn::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	memcpy(&m_UIInfo, pArg, sizeof(UIINFO));

	m_iSkillPoint = 0;
	m_iTexturenum = 0;
	__super::Initialize(pArg);

	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();

	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_SkillUpBtn"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	pSkillInstance->Add_SkillFrameImage(this);

	return S_OK;
}

void CSkillUpBtn::Tick(_float fTimeDelta)
{
	CGameInstance* pInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pInstance);
	
	if (pInstance->Key_Down(DIK_K))
	{
		m_bRender = !m_bRender;
	}


	if (pInstance->Mouse_Up(DIMK_LBUTTON))
	{

	}
	
	Check_Collision(DIMK_LBUTTON);
	Change_Texture();	
	

	Safe_Release(pInstance);
}

void CSkillUpBtn::LateTick(_float fTimeDelta)
{
	if (m_bRender)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);


	SetRect(&m_RectUI, m_UIInfo.fX - m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY - m_UIInfo.fSizeY * 0.5f, m_UIInfo.fX + m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY + m_UIInfo.fSizeY * 0.5f);
	
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_UIInfo.fX - g_iWinSizeX * 0.5f, -m_UIInfo.fY + g_iWinSizeY * 0.5f, 0.f));
	
	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();
	m_iSkillPoint = pSkillInstance->Get_SkillPoint();

}

HRESULT CSkillUpBtn::Render()
{
	if (FAILED(m_pTextureCom->Bind_Texture(m_iTexturenum)))
		return E_FAIL;

	m_pTransformCom->Bind_WorldMatrix();
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	Set_RenderState();

	m_pVIBufferCom->Render();

	Reset_RenderState();
	return S_OK;
}

void CSkillUpBtn::Change_Texture()
{
	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();
	if (pSkillInstance->Get_SkillPoint() == 0)
	{
		m_iTexturenum = 0;
		return;
	}

	switch (m_eCollision)
	{
	case Client::CUI::TYPE_NO:
		m_iTexturenum = 1;
		break;
	case Client::CUI::TYPE_ON:
		m_iTexturenum = 2;
		break;
	case Client::CUI::TYPE_DOWN:
		break;
	case Client::CUI::TYPE_UP:
		pSkillInstance->Set_SkillPoint(-1);
		pSkillInstance->Get_SkillInfo(TEXT("SunCrossInfo"), CSkillManager::GRADE_BEGENNER)->Set_SkillLevel(1);
		break;
	case Client::CUI::TYPE_PRESSING:
		m_iTexturenum = 3;
		break;
	case Client::CUI::TYPE_END:
		break;
	default:
		break;
	}
}

CSkillUpBtn* CSkillUpBtn::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSkillUpBtn*		pInstance = new CSkillUpBtn(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CSkillUpBtn"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CSkillUpBtn::Clone(void * pArg)
{
	CSkillUpBtn*		pInstance = new CSkillUpBtn(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CSkillUpBtn"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSkillUpBtn::Free()
{
	__super::Free();

}
