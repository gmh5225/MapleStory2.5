#include "stdafx.h"
#include "..\Public\GreenMushroomInfo.h"


CGreenMushroomInfo::CGreenMushroomInfo()
{
	Initialize();
}

void CGreenMushroomInfo::Initialize()
{
	m_iNowNum = 0;
	m_iMaxNum = 99;
	m_iTextNum = 3;
	m_pItemName = L"GreenMushroomInfo";
	m_pItemNotice = L"�ʷԹ����ǰ�";
}

void CGreenMushroomInfo::Free()
{
}


