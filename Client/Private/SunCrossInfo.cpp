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
	m_cSkillName = L"½ã Å©·Î½º";
}

void CSunCrossInfo::Free()
{
	__super::Free();
}

