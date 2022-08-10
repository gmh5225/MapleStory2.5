#include "stdafx.h"
#include "..\Public\StuffBtn.h"
#include "GameInstance.h"
#include "InvenManager.h"



CStuffBtn::CStuffBtn(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CStuffBtn::CStuffBtn(const CStuffBtn& rhs)
	: CUI(rhs)
{
}


HRESULT CStuffBtn::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CStuffBtn::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	memcpy(&m_UIInfo, pArg, sizeof(UIINFO));
	m_iTexturenum = 0;
	__super::Initialize(pArg);
	m_bRender = false;
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Texture_StuffBtn"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	CInvenManager* pInvenInstance = CInvenManager::Get_Instance();
	pInvenInstance->Add_InvenImage(this);


	return S_OK;
}

void CStuffBtn::Tick(_float fTimeDelta)
{
	CGameInstance* pInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pInstance);

	if (pInstance->Key_Down(DIK_I))
	{
		m_bRender = !m_bRender;
	}

	Check_Collision(DIMK_LBUTTON);
	Change_Texture();


	Safe_Release(pInstance);
}

void CStuffBtn::LateTick(_float fTimeDelta)
{


	SetRect(&m_RectUI, m_UIInfo.fX - m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY - m_UIInfo.fSizeY * 0.5f, m_UIInfo.fX + m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY + m_UIInfo.fSizeY * 0.5f);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_UIInfo.fX - g_iWinSizeX * 0.5f, -m_UIInfo.fY + g_iWinSizeY * 0.5f, 0.f));

	if (m_bRender)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);


}

HRESULT CStuffBtn::Render()
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

void CStuffBtn::Change_Texture()
{

	CInvenManager* pInvenInstance = CInvenManager::Get_Instance();

	switch (m_eCollision)
	{
	case Client::CUI::TYPE_NO:
		break;
	case Client::CUI::TYPE_ON:
		break;
	case Client::CUI::TYPE_DOWN:
		pInvenInstance->Set_InvenType(CInvenManager::TYPE_STUFF);
		break;
	case Client::CUI::TYPE_UP:
		break;
	case Client::CUI::TYPE_PRESSING:
		break;
	case Client::CUI::TYPE_END:
		break;
	default:
		break;
	}
	if (pInvenInstance->Get_InvenType() == CInvenManager::TYPE_STUFF)
		m_iTexturenum = 1;
	else
		m_iTexturenum = 0;




}

CStuffBtn* CStuffBtn::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CStuffBtn*		pInstance = new CStuffBtn(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CStuffBtn"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CStuffBtn::Clone(void * pArg)
{
	CStuffBtn*		pInstance = new CStuffBtn(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CStuffBtn"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CStuffBtn::Free()
{
	__super::Free();

}
