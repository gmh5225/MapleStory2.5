#include "stdafx.h"
#include "..\Public\CardinalBlastInfo.h"


CCardinalBlastInfo::CCardinalBlastInfo()
{
	Initialize();
}

void CCardinalBlastInfo::Initialize()
{
	m_iSkillLevel = 0;
	m_iSkillDamage = 0;
	m_iTextNum = 5;
	m_cSkillName = L"ī��� ����Ʈ";
	m_cSkillNotice = L"Ÿ�� : ���Ÿ� ����\n����� : 20\nŸ��Ƚ�� : 1\n�Ҹ� ���� : 50";
}

void CCardinalBlastInfo::Free()
{
	__super::Free();
}

