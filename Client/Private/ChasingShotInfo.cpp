#include "stdafx.h"
#include "..\Public\ChasingShotInfo.h"


CChasingShotInfo::CChasingShotInfo()
{
	Initialize();
}

void CChasingShotInfo::Initialize()
{
	m_iSkillLevel = 0;
	m_iSkillDamage = 0;
	m_iTextNum = 6;
	m_cSkillName = L"ü�̽� ��";
	m_cSkillNotice = L"Ÿ�� : ���Ÿ� ����\n����� : 100\nŸ��Ƚ�� : 1\n�Ҹ� ���� : 200";
}

void CChasingShotInfo::Free()
{
	__super::Free();
}

