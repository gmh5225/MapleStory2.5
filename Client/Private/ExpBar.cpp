#include "stdafx.h"
#include "..\Public\ExpBar.h"
#include "GameInstance.h"



CExpBar::CExpBar(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CExpBar::CExpBar(const CExpBar& rhs)
	: CUI(rhs)
{
}


HRESULT CExpBar::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CExpBar::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_UIInfo.fSizeX = 1280.f;
	m_UIInfo.fSizeY = 17.f;
	m_UIInfo.fX = g_iWinSizeX*0.5f;
	m_UIInfo.fY = g_iWinSizeY - m_UIInfo.fSizeY*0.5f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_UIInfo.fX - g_iWinSizeX * 0.5f, -m_UIInfo.fY + g_iWinSizeY * 0.5f, 0.f));
	m_iTexturenum = 0;
	m_iExp = 0;
	m_iLevel = 25;
	m_iExpDigit = g_iWinSizeX*0.5f;
	__super::Initialize(pArg);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Texture_ExpBar"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	D3DXCreateFont(m_pGraphic_Device, 12, 0, FW_BOLD, 1, FALSE, HANGEUL_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"µ¸¿òÃ¼", &m_ExpFont);


	D3DXCreateFont(m_pGraphic_Device, 14, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"µ¸¿òÃ¼", &m_LevelFont);

	
	

	return S_OK;
}

void CExpBar::Tick(_float fTimeDelta)
{
	CGameInstance* pInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pInstance);

	if (pInstance->Key_Down(DIK_E))
	{
		if (m_iTexturenum < 51)
			m_iTexturenum += 1;

		if (m_iTexturenum == 51)
		{
			m_iTexturenum = 0;
			m_iLevel += 1;
		}
	}
	if (m_iExp < 10)	
		m_iExpDigit = g_iWinSizeX*0.5f;
	else if (m_iExp < 100)	
		m_iExpDigit = g_iWinSizeX*0.5f - 5.f;
	else
		m_iExpDigit = g_iWinSizeX*0.5f - 10.f;
	

	Safe_Release(pInstance);
}

void CExpBar::LateTick(_float fTimeDelta)
{
	m_iExp = m_iTexturenum * 2;
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);

	
}

HRESULT CExpBar::Render()
{
	if (FAILED(m_pTextureCom->Bind_Texture(m_iTexturenum)))
		return E_FAIL;

	m_pTransformCom->Bind_WorldMatrix();
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	Set_RenderState();

	m_pVIBufferCom->Render();

	Reset_RenderState();


	wchar_t Exp[10];
	_itow_s(m_iExp, Exp, 10);

	wchar_t Level[10];
	_itow_s(m_iLevel, Level, 10);

	RECT Exprt;
	SetRect(&Exprt, m_iExpDigit+10, 705, 0, 0);
	m_ExpFont->DrawText(NULL, Exp, -1, &Exprt, DT_NOCLIP, D3DXCOLOR(255.f, 255.f, 255.f, 1.0f));

	RECT Percentrt;
	SetRect(&Percentrt, g_iWinSizeX*0.5f + 20.f, 705, 0, 0);
	m_ExpFont->DrawText(NULL, L"%", -1, &Percentrt, DT_NOCLIP, D3DXCOLOR(255.f, 255.f, 255.f, 1.0f));

	RECT LVrt;
	SetRect(&LVrt, 595, 680, 0, 0);
	m_LevelFont->DrawText(NULL, L"LV", -1, &LVrt, DT_NOCLIP, D3DXCOLOR(255.f, 212, 0.f, 1.0f));

	RECT Levelrt;
	SetRect(&Levelrt, 615, 680, 0, 0);
	m_LevelFont->DrawText(NULL, Level, -1, &Levelrt, DT_NOCLIP, D3DXCOLOR(255.f, 212, 0.f, 1.0f));

	RECT Namert;
	SetRect(&Namert, 640, 680, 0, 0);
	m_LevelFont->DrawText(NULL, L"µéÁãÄá", -1, &Namert, DT_NOCLIP, D3DXCOLOR(255.f, 212, 0.f, 1.0f));


	return S_OK;
}


CExpBar* CExpBar::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CExpBar*		pInstance = new CExpBar(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CExpBar"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CExpBar::Clone(void * pArg)
{
	CExpBar*		pInstance = new CExpBar(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CExpBar"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CExpBar::Free()
{
	__super::Free();

}
