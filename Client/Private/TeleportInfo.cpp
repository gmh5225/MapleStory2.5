#include "stdafx.h"
#include "..\Public\TeleportInfo.h"


CTeleportInfo::CTeleportInfo()
{
	Initialize();
}

void CTeleportInfo::Initialize()
{
	m_iNowNum = 0;
	m_iMaxNum = 999;
	m_iTextNum = 2;
	m_pItemName = L"TeleportInfo";
	m_pItemNotice = L"������ ��ȯ�մϴ�";
}

void CTeleportInfo::Free()
{
}


