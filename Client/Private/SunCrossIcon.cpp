#include "stdafx.h"
#include "..\Public\SunCrossIcon.h"
#include "GameInstance.h"
#include "SkillManager.h"
#include "SunCrossInfo.h"


CSunCrossIcon::CSunCrossIcon(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CSunCrossIcon::CSunCrossIcon(const CSunCrossIcon& rhs)
	: CUI(rhs)
{
}


HRESULT CSunCrossIcon::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CSunCrossIcon::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	memcpy(&m_UIInfo, pArg, sizeof(UIINFO));

	__super::Initialize(pArg);
	m_iTexturenum = 0;
	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();

	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_SunCrossIcon"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	pSkillInstance->Add_SkillFrameImage(this);

	return S_OK;
}

void CSunCrossIcon::Tick(_float fTimeDelta)
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

	Safe_Release(pInstance);
}

void CSunCrossIcon::LateTick(_float fTimeDelta)
{
	

	SetRect(&m_RectUI, m_UIInfo.fX - m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY - m_UIInfo.fSizeY * 0.5f, m_UIInfo.fX + m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY + m_UIInfo.fSizeY * 0.5f);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_UIInfo.fX - g_iWinSizeX * 0.5f, -m_UIInfo.fY + g_iWinSizeY * 0.5f, 0.f));

	Change_Texture();

	if (m_bRender)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);
	
}

HRESULT CSunCrossIcon::Render()
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

void CSunCrossIcon::Change_Texture()
{
	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();
	if (pSkillInstance->Get_SkillInfo(L"SunCrossInfo", CSkillManager::GRADE_BEGENNER)->Get_SkillLevel() < 1)
		m_iTexturenum = 0;
	else
		m_iTexturenum = 1;
	
}

CSunCrossIcon* CSunCrossIcon::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSunCrossIcon*		pInstance = new CSunCrossIcon(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CSunCrossIcon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CSunCrossIcon::Clone(void * pArg)
{
	CSunCrossIcon*		pInstance = new CSunCrossIcon(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CSunCrossIcon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSunCrossIcon::Free()
{
	__super::Free();

}
