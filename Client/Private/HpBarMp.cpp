#include "stdafx.h"
#include "..\Public\HpBarMp.h"
#include "GameInstance.h"
#include "UIManager.h"


CHpBarMp::CHpBarMp(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CHpBarMp::CHpBarMp(const CHpBarMp& rhs)
	: CUI(rhs)
{
}


HRESULT CHpBarMp::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CHpBarMp::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_UIInfo.fSizeX = 150.f;
	m_UIInfo.fSizeY = 150.f;
	m_UIInfo.fX = g_iWinSizeX*0.5;
	m_UIInfo.fY = 600.f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_UIInfo.fX - g_iWinSizeX * 0.5f, -m_UIInfo.fY + g_iWinSizeY * 0.5f, 0.f));
	m_iTexturenum = 0;
	__super::Initialize(pArg);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Texture_HpBarMp"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;


	return S_OK;
}

void CHpBarMp::Tick(_float fTimeDelta)
{
	CGameInstance* pInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pInstance);

	if (pInstance->Key_Down(DIK_A))
	{
		if (m_iTexturenum + 3 >= 22)
			m_iTexturenum = 22;
		else
		m_iTexturenum += 3;
	}

	if (pInstance->Key_Down(DIK_D))
	{
		if (m_iTexturenum + 2 >= 22)
			m_iTexturenum = 22;
		else
		m_iTexturenum += 2;
	}

	if (pInstance->Key_Down(DIK_S))
	{
		if (m_iTexturenum + 4 >= 22)
			m_iTexturenum = 22;
		else
		m_iTexturenum += 4;
	}

	if (pInstance->Key_Down(DIK_F))
	{
		if (m_iTexturenum + 5 >= 22)
			m_iTexturenum = 22;
		else
		m_iTexturenum += 5;
	}

	if (pInstance->Key_Down(DIK_C))
	{
		if (m_iTexturenum + 2 >= 22)
			m_iTexturenum = 22;
		else
		m_iTexturenum += 2;

	}

	if (pInstance->Key_Down(DIK_NUMPAD2))
	{
		if (m_iTexturenum < 2)
			m_iTexturenum = 0;
		else
			m_iTexturenum -= 2;

		CUIManager::Get_Instance()->Set_StartMove(true);
	}

	if (pInstance->Key_Down(DIK_NUMPAD3))
	{
		CUIManager::Get_Instance()->Set_EndMove(true);
	}




	if (m_iTexturenum == 21)
		m_iTexturenum = 0;

	Safe_Release(pInstance);
	if (CUIManager::Get_Instance()->Get_StartMove())
		Start_CutScene(fTimeDelta);
	else
		m_fStartAcc = 0.f;


	if (CUIManager::Get_Instance()->Get_EndMove())
		End_CutScene(fTimeDelta);
	else
		m_fEndAcc = 0.f;
}

void CHpBarMp::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);
}

HRESULT CHpBarMp::Render()
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


CHpBarMp* CHpBarMp::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CHpBarMp*		pInstance = new CHpBarMp(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CHpBarMp"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CHpBarMp::Clone(void * pArg)
{
	CHpBarMp*		pInstance = new CHpBarMp(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CHpBarMp"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CHpBarMp::Free()
{
	__super::Free();

}
