#include "stdafx.h"
#include "..\Public\SunCrossInfo.h"


CSunCrossInfo::CSunCrossInfo()
{
	Initialize();
}

void CSunCrossInfo::Initialize()
{
	m_iSkillLevel = 0;
	m_iSkillDamage = 0; 
	m_iTextNum = 0;
	m_cSkillName = L"�� ũ�ν�";
	m_cSkillNotice = L"Ÿ�� : ���� ����\n����� : 20\nŸ��Ƚ�� : 3\n�Ҹ� ���� : 50";
	int a = m_dwRefCnt;
}

void CSunCrossInfo::Free()
{
	__super::Free();
}

