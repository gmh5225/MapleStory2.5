#include "stdafx.h"
#include "..\Public\RedPortionInfo.h"


CRedPortionInfo::CRedPortionInfo()
{
	Initialize();
}

void CRedPortionInfo::Initialize()
{
	m_iNowNum = 98;
	m_iMaxNum = 999;
	m_iTextNum = 0;
	m_pItemName = L"RedPortionInfo";
	m_pItemNotice = L"HP50ȸ��";
}

void CRedPortionInfo::Free()
{
}


