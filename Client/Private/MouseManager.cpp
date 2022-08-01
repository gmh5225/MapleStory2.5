#include "stdafx.h"
#include "..\Public\MouseManager.h"
#include "MouseSkillIcon.h"

IMPLEMENT_SINGLETON(CMouseManager)

CMouseManager::CMouseManager()
{
}

HRESULT CMouseManager::Add_pMouseSkillIcon(CMouseSkillIcon * pMouseSkillIcon)
{
	if (pMouseSkillIcon == nullptr)
		return E_FAIL;

	m_pMouseSkillIcon = pMouseSkillIcon;

	return S_OK;
}

void CMouseManager::Set_SkillIconIndex(const _tchar* pSkillInfoTag, CSkillManager::SkillGrade eGrade, _uint iIndex)
{
	m_pMouseSkillIcon->Set_TextureNum(iIndex);
	m_pSkillInfoTag = pSkillInfoTag;
	m_eGrade = eGrade;

}

void CMouseManager::Free()
{
	Safe_Release(m_pMouseSkillIcon);
}
