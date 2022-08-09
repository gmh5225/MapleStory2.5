#include "stdafx.h"
#include "..\Public\UIManager.h"

IMPLEMENT_SINGLETON(CUIManager)

CUIManager::CUIManager()
{
}

HRESULT CUIManager::Add_ItemNotice(CItemNotice * pItemNotice)
{
	if (pItemNotice == nullptr)
		return E_FAIL;

	m_pItemNotice = pItemNotice;

	return S_OK;
}

void CUIManager::Set_ItemNoticeTextNum(_uint iTextNum, bool bRender)
{
	m_pItemNotice->Set_TextureNum(iTextNum);
	m_pItemNotice->Set_Render(bRender);	
}

bool CUIManager::Check_Change(_uint iTextNum)
{		
	if (m_pItemNotice->Get_Render() && m_pItemNotice->Get_TextNum() == iTextNum)
		return true;

	return false;
}

void CUIManager::Free()
{
}


