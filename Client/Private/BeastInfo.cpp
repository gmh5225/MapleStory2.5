#include "stdafx.h"
#include "..\Public\BeastInfo.h"


CBeastInfo::CBeastInfo()
{
	Initialize();
}

void CBeastInfo::Initialize()
{
	m_iSkillLevel = 0;
	m_iSkillDamage = 0;
	m_iTextNum = 7;
	m_cSkillName = L"���Ʈ";
	m_cSkillNotice = L"Ÿ�� : ���� ����\n����� : 500\nŸ��Ƚ�� : 1\n�Ҹ� ���� : 300";
}

void CBeastInfo::Free()
{
	__super::Free();
}

