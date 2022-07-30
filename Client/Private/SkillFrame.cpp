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
	memcpy(&m_UIInfo, pArg, sizeof(UIINFO));

	m_pSkillManager = CSkillManager::Get_Instance();

	m_pSkillManager->Set_pSkillFrame(this);

	__super::Initialize(pArg);
	
	D3DXCreateFont(m_pGraphic_Device, 13, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"µ¸¿òÃ¼", &m_FrameFont);


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

	if (pInstance->Key_Down(DIK_P))
	m_pSkillManager->Set_SkillPoint(1);

	if (pInstance->Mouse_Up(DIMK_LBUTTON))
	{
		
	}



	Safe_Release(pInstance);
}

void CSkillFrame::LateTick(_float fTimeDelta)
{
	if (m_bRender)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);

	for (auto list : m_SkillFrameImage)
	{
		list->Set_UIMovePos(m_UIInfo);
	}

	if (m_pSkillManager->Get_SkillPoint() < 10)
	{
		m_iSkillPointDigit = 440;
	}
	else if (m_pSkillManager->Get_SkillPoint() < 100)
	{
		m_iSkillPointDigit = 430;
	}
	else
	{
		m_iSkillPointDigit = 420;
	}

}

HRESULT CSkillFrame::Render()
{
	if (FAILED(m_pTextureCom->Bind_Texture(m_iTexturenum)))
		return E_FAIL;

	m_pTransformCom->Bind_WorldMatrix();
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	Set_RenderState();

	m_pVIBufferCom->Render();

	Reset_RenderState();
	
	RenderText();
	
	
	

	return S_OK;
}

HRESULT CSkillFrame::Add_SkillFrameImage(CUI * pSkillFrameImage)
{
	if (pSkillFrameImage == nullptr)
		return E_FAIL;

	m_SkillFrameImage.push_back(pSkillFrameImage);
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

void CSkillFrame::RenderText()
{


	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();

	wchar_t SkillPoint[10];
	_itow_s(m_pSkillManager->Get_SkillPoint(), SkillPoint, 10);

	wchar_t SunCrossLevel[10];
	_itow_s(pSkillInstance->Get_SkillInfo(TEXT("SunCrossInfo"), CSkillManager::GRADE_BEGENNER)->Get_SkillLevel(), SunCrossLevel, 10);
	

	RECT SkillPointrt;
	SetRect(&SkillPointrt, m_iSkillPointDigit, 150, 0, 0);
	m_FrameFont->DrawText(NULL, SkillPoint, -1, &SkillPointrt, DT_NOCLIP, D3DXCOLOR(0.f, 0.f, 0.f, 1.0f));

	RECT SuncrossName;
	SetRect(&SuncrossName, 192, 215, 0, 0);
	m_FrameFont->DrawText(NULL, pSkillInstance->Get_SkillInfo(TEXT("SunCrossInfo"), CSkillManager::GRADE_BEGENNER)->Get_SkillName(), -1, &SuncrossName, DT_NOCLIP, D3DXCOLOR(0.f, 0.f, 0.0f, 1.0f));


	RECT SuncrossLevel;
	SetRect(&SuncrossName, 193, 233, 0, 0);
	m_FrameFont->DrawText(NULL, SunCrossLevel, -1, &SuncrossName, DT_NOCLIP, D3DXCOLOR(0.f, 0.f, 0.0f, 1.0f));
}

void CSkillFrame::Free()
{
	__super::Free();

}


