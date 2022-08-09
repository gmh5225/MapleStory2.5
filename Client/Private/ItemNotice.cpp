#include "stdafx.h"
#include "..\Public\ItemNotice.h"
#include "GameInstance.h"
#include "UIManager.h"



CItemNotice::CItemNotice(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CItemNotice::CItemNotice(const CItemNotice& rhs)
	: CUI(rhs)
{
}


HRESULT CItemNotice::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CItemNotice::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_UIInfo.fSizeX = 173.f;
	m_UIInfo.fSizeY = 87.f;
	m_iTexturenum = 99;
	
	__super::Initialize(pArg);
	m_bRender = false;
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Texture_ItemNotice"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;
	CUIManager* pUIInstance = CUIManager::Get_Instance();
	pUIInstance->Add_ItemNotice(this);

	return S_OK;
}

void CItemNotice::Tick(_float fTimeDelta)
{
}

void CItemNotice::LateTick(_float fTimeDelta)
{
	if (m_bRender)
	{
		POINT		ptMouse;
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);
		m_UIInfo.fX = ptMouse.x + 100.f;
		m_UIInfo.fY = ptMouse.y + 50.f;
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_UIInfo.fX - g_iWinSizeX * 0.5f, -m_UIInfo.fY + g_iWinSizeY * 0.5f, 0.f));
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);
	}
}

HRESULT CItemNotice::Render()
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


CItemNotice* CItemNotice::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CItemNotice*		pInstance = new CItemNotice(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CItemNotice"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CItemNotice::Clone(void * pArg)
{
	CItemNotice*		pInstance = new CItemNotice(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CItemNotice"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CItemNotice::Free()
{
	__super::Free();

}
