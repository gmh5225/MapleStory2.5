#include "stdafx.h"
#include "..\Public\SolunaSlashInfo.h"


CSolunaSlashInfo::CSolunaSlashInfo()
{
	Initialize();
}

void CSolunaSlashInfo::Initialize()
{
	m_iSkillLevel = 0;
	m_iSkillDamage = 0;
	m_iTextNum = 1;
	m_cSkillName = L"�ַ糪 ������";
	m_cSkillNotice = L"��ų ���� �׽�Ʈ\nŸ�� : �뽬\n �Ҹ� ���� : 30\n�̵� �Ÿ� : 300px";
}

void CSolunaSlashInfo::Free()
{
	__super::Free();
}

