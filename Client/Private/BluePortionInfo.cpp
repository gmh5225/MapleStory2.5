#include "stdafx.h"
#include "..\Public\BluePortionInfo.h"


CBluePortionInfo::CBluePortionInfo()
{
	Initialize();
}

void CBluePortionInfo::Initialize()
{
	m_iNowNum = 98;
	m_iMaxNum = 999;
	m_iTextNum = 1;
	m_pItemName = L"BluePortionInfo";
	m_pItemNotice = L"MP50ȸ��";
}

void CBluePortionInfo::Free()
{
}


