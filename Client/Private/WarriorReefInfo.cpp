#include "stdafx.h"
#include "..\Public\WarriorReefInfo.h"


CWarriorReefInfo::CWarriorReefInfo()
{
	Initialize();
}

void CWarriorReefInfo::Initialize()
{
	m_iSkillLevel = 0;
	m_iSkillDamage = 0;
	m_iTextNum = 4;
	m_cSkillName = L"������ ����";
	m_cSkillNotice = L"\nŸ�� : �뽬\n �Ҹ� ���� : 10\n�̵� �Ÿ� : 200px";
}

void CWarriorReefInfo::Free()
{
	__super::Free();
}

