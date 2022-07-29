#include "stdafx.h"
#include "..\Public\SkillFrame.h"
#include "GameInstance.h"


CSkillFrame::CSkillFrame(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CSkillFrame::CSkillFrame(const CSkillFrame& rhs)
	:CUI(rhs)
{
}


HRESULT CSkillFrame::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CSkillFrame::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	//m_UIInfo = *(UIINFO*)pArg;
	//memcpy(&m_UIInfo, pArg, sizeof(UIINFO));

	m_UIInfo.fSizeX = 350.f;
	m_UIInfo.fSizeY = 350.f;
	m_UIInfo.fX = 900.f;
	m_UIInfo.fY = 300.f;

	__super::Initialize(pArg);
	
	//memcpy(&m_UIInfo, pArg, sizeof(UIINFO));
	//m_UIInfo = *(UIINFO*)pArg;


	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_SkillFrame"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

void CSkillFrame::Tick(_float fTimeDelta)
{
	CGameInstance* pInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pInstance);
	Check_Collision(DIMK_LBUTTON);
	if (pInstance->Key_Down(DIK_K))
		m_bRender = !m_bRender;

	if (pInstance->Mouse_Up(DIMK_LBUTTON))
	{
	
	}



	Safe_Release(pInstance);
}

void CSkillFrame::LateTick(_float fTimeDelta)
{
	if (m_bRender)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);

}

HRESULT CSkillFrame::Render()
{
	if (FAILED(m_pTextureCom->Bind_Texture(m_iTexturenum)))
		return E_FAIL;

	m_pTransformCom->Bind_WorldMatrix();
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	m_pVIBufferCom->Render();

	return S_OK;
}

CSkillFrame* CSkillFrame::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSkillFrame*		pInstance = new CSkillFrame(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CSkillFrame"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CSkillFrame::Clone(void * pArg)
{
	CSkillFrame*		pInstance = new CSkillFrame(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CSkillFrame"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSkillFrame::Free()
{
	__super::Free();

}
