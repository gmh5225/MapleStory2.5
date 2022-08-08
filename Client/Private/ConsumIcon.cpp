#include "stdafx.h"
#include "..\Public\ConsumIcon.h"
#include "GameInstance.h"
#include "InvenManager.h"
#include "MouseManager.h"


CConsumIcon::CConsumIcon(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CConsumIcon::CConsumIcon(const CConsumIcon& rhs)
	: CUI(rhs)
{
}


HRESULT CConsumIcon::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CConsumIcon::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	memcpy(&m_UIInfo, pArg, sizeof(UIINFO));

	__super::Initialize(pArg);
	m_iTexturenum = m_UIInfo.iTextNum;
	m_iIndexNum = m_UIInfo.iNum;
	m_pTag = m_UIInfo.pTag;
	CInvenManager* pInvenInstance = CInvenManager::Get_Instance();

	m_pItemInfo = pInvenInstance->Get_ItemInfo(m_pTag, CInvenManager::TYPE_CONSUM);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Texture_ConsumIcon"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	D3DXCreateFont(m_pGraphic_Device, 11, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"µ¸¿òÃ¼", &m_NumFont);

	D3DXCreateFont(m_pGraphic_Device, 13, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"µ¸¿òÃ¼", &m_NoticeFont);

	pInvenInstance->Add_InvenIcon(CInvenManager::TYPE_CONSUM, this);

	return S_OK;
}

void CConsumIcon::Tick(_float fTimeDelta)
{
	CGameInstance* pInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pInstance);

	if (pInstance->Key_Down(DIK_I))
	{
		m_bRender = !m_bRender;
	}
	CInvenManager* pInvenInstance = CInvenManager::Get_Instance();
	if (pInstance->Mouse_Up(DIMK_RBUTTON) && m_eCollision == TYPE_ON && pInvenInstance->Get_InvenType() == CInvenManager::TYPE_CONSUM)
	{
		if(m_pItemInfo->Get_NowNum() != 0)
			m_pItemInfo->Set_NowNum(-1);	
		if (m_pItemInfo->Get_NowNum() == 0)
		{
			
			m_pItemInfo = pInvenInstance->Find_ItemInfo(TEXT("DefaultInfo"), CInvenManager::TYPE_CONSUM);
			m_pTag = m_pItemInfo->Get_ItemName();
		}
	}
	Check_Collision(DIMK_LBUTTON);

	Safe_Release(pInstance);
}

void CConsumIcon::LateTick(_float fTimeDelta)
{
	SetRect(&m_RectUI, m_UIInfo.fX - m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY - m_UIInfo.fSizeY * 0.5f, m_UIInfo.fX + m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY + m_UIInfo.fSizeY * 0.5f);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_UIInfo.fX - g_iWinSizeX * 0.5f, -m_UIInfo.fY + g_iWinSizeY * 0.5f, 0.f));

	Change_Texture();
	CInvenManager* pInvenInstance = CInvenManager::Get_Instance();
	if (m_bRender&& pInvenInstance->Get_InvenType() == CInvenManager::TYPE_CONSUM)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);


}

HRESULT CConsumIcon::Render()
{
	if (FAILED(m_pTextureCom->Bind_Texture(m_iTexturenum)))
		return E_FAIL;

	m_pTransformCom->Bind_WorldMatrix();
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	Set_RenderState();

	m_pVIBufferCom->Render();

	Reset_RenderState();

	wchar_t NowNum[10];
	_itow_s(m_pItemInfo->Get_NowNum(), NowNum, 10);

	RECT ItemNum;
	SetRect(&ItemNum, m_UIInfo.fX-12.f, m_UIInfo.fY+2.f, 0, 0);
	m_NoticeFont->DrawText(NULL, NowNum, -1, &ItemNum, DT_NOCLIP, D3DXCOLOR(0.f, 0.f, 0.f, 1.0f));

	if (m_eCollision == TYPE_ON)
	{
		RECT ReefAttackNotice;
		SetRect(&ReefAttackNotice, m_UIInfo.fX, m_UIInfo.fY, 0, 0);
		m_NoticeFont->DrawText(NULL, m_pItemInfo->Get_ItemNotice(), -1, &ReefAttackNotice, DT_NOCLIP, D3DXCOLOR(0.f, 0.f, 255.0f, 1.0f));
	}

	return S_OK;
}

HRESULT CConsumIcon::Set_ItemInfo(const _tchar * pTag)
{
	if (pTag == nullptr)
		return E_FAIL;
	CInvenManager* pInvenInstance = CInvenManager::Get_Instance();
	
	m_pItemInfo = pInvenInstance->Get_ItemInfo(pTag, CInvenManager::TYPE_CONSUM);
	m_pTag = m_pItemInfo->Get_ItemName();
	
	return S_OK;
}

void CConsumIcon::Set_NowNum(_uint iNum)
{
	m_pItemInfo->Set_NowNum(iNum);
}

void CConsumIcon::Change_Texture()
{
	CInvenManager* pInvenInstance = CInvenManager::Get_Instance();
	if (pInvenInstance->Get_InvenType() == CInvenManager::TYPE_CONSUM)
	{
		if (pInvenInstance->Get_ItemInfo(m_pTag, CInvenManager::TYPE_CONSUM)->Get_NowNum() < 1)
		{
			m_iTexturenum = 99;
		}
		else
			m_iTexturenum = m_pItemInfo->Get_TextNum();


		CMouseManager* pMouseInstance = CMouseManager::Get_Instance();
		if (m_eCollision == TYPE_DOWN)
		{
			pMouseInstance->Set_ItemIconIndex(CMouseManager::TYPE_ITEM, m_pTag, CInvenManager::TYPE_CONSUM, m_iTexturenum, m_pItemInfo->Get_ItemNotice(), m_UIInfo.iNum);
		}

		if (m_eCollision == TYPE_UP)
		{
			CItemInfo* pTemp = pMouseInstance->Get_ItemInfo();
			pInvenInstance->Change_Info(m_pTag, pMouseInstance->Get_Indexnum(), CInvenManager::TYPE_CONSUM);
			m_pItemInfo = pTemp;
			m_pTag = pTemp->Get_ItemName();
		}
	}
}

CConsumIcon* CConsumIcon::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CConsumIcon*		pInstance = new CConsumIcon(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CConsumIcon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CConsumIcon::Clone(void * pArg)
{
	CConsumIcon*		pInstance = new CConsumIcon(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CConsumIcon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CConsumIcon::Free()
{
	__super::Free();
}
