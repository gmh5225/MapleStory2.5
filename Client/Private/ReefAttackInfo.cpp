#include "stdafx.h"
#include "..\Public\ReefAttackInfo.h"


CReefAttackInfo::CReefAttackInfo()
{
	Initialize();
}

void CReefAttackInfo::Initialize()
{
	m_iSkillLevel = 0;
	m_iSkillDamage = 0;
	m_iTextNum = 2;
	m_cSkillName = L"���� ����";
	m_cSkillNotice = L"Ÿ�� : ���� ����\n����� : 10\nŸ��Ƚ�� : 2\n�Ҹ� ���� : 30";
}

void CReefAttackInfo::Free()
{
	__super::Free();
}

