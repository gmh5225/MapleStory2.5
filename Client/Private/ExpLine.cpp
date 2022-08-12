#include "stdafx.h"
#include "..\Public\ExpLine.h"
#include "GameInstance.h"
#include "UIManager.h"



CExpLine::CExpLine(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CExpLine::CExpLine(const CExpLine& rhs)
	: CUI(rhs)
{
}


HRESULT CExpLine::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CExpLine::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_UIInfo.fSizeX = 1280.f;
	m_UIInfo.fSizeY = 17.f;
	m_UIInfo.fX = g_iWinSizeX*0.5;
	m_UIInfo.fY = g_iWinSizeY - m_UIInfo.fSizeY*0.5f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_UIInfo.fX - g_iWinSizeX * 0.5f, -m_UIInfo.fY + g_iWinSizeY * 0.5f, 0.f));

	__super::Initialize(pArg);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Texture_ExpLine"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;


	return S_OK;
}

void CExpLine::Tick(_float fTimeDelta)
{
	if (CUIManager::Get_Instance()->Get_StartMove())
		Start_CutScene(fTimeDelta);
	else
		m_fStartAcc = 0.f;


	if (CUIManager::Get_Instance()->Get_EndMove())
		End_CutScene(fTimeDelta);
	else
		m_fEndAcc = 0.f;
}

void CExpLine::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);
}

HRESULT CExpLine::Render()
{
	if (FAILED(m_pTextureCom->Bind_Texture(0)))
		return E_FAIL;

	m_pTransformCom->Bind_WorldMatrix();
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	Set_RenderState();

	m_pVIBufferCom->Render();

	Reset_RenderState();
	return S_OK;
}


CExpLine* CExpLine::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CExpLine*		pInstance = new CExpLine(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CExpLine"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CExpLine::Clone(void * pArg)
{
	CExpLine*		pInstance = new CExpLine(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CExpLine"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CExpLine::Free()
{
	__super::Free();

}
