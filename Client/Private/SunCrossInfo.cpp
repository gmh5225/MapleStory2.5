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
	m_cSkillName = L"�� ũ�ν�";
}

void CSunCrossInfo::Free()
{
	__super::Free();
}

