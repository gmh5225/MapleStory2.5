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
	m_iIndexNum = 1;
	m_cSkillName = L"솔루나 슬래쉬";
}

void CSolunaSlashInfo::Free()
{
	__super::Free();
}

