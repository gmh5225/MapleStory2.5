#include "stdafx.h"
#include "..\Public\InvenManager.h"

IMPLEMENT_SINGLETON(CInvenManager)

CInvenManager::CInvenManager()
{
	m_pRedPortion = nullptr;
}

HRESULT CInvenManager::AddItemNum(void * pArg)
{
	return S_OK;
}

void CInvenManager::Free()
{
}


