#include "stdafx.h"
#include "..\Public\SpearPullingInfo.h"


CSpearPullingInfo::CSpearPullingInfo()
{
	Initialize();
}

void CSpearPullingInfo::Initialize()
{
	m_iSkillLevel = 0;
	m_iSkillDamage = 0;
	m_iTextNum = 3;
	m_cSkillName = L"���Ǿ� Ǯ��";
	m_cSkillNotice = L"Ÿ�� : ������\n����� : 30\nŸ��Ƚ�� : 5\n�Ҹ� ���� : 70";
}

void CSpearPullingInfo::Free()
{
	__super::Free();
}

