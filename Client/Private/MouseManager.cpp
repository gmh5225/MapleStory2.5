#include "stdafx.h"
#include "..\Public\MouseManager.h"
#include "MouseSkillIcon.h"
#include "SkillManager.h"
#include "SkillInfo.h"

IMPLEMENT_SINGLETON(CMouseManager)

CMouseManager::CMouseManager()
{
	m_pSkillInfoTag = L"SunCrossInfo";
	m_eGrade = CSkillManager::GRADE_BEGENNER;
}

HRESULT CMouseManager::Add_pMouseSkillIcon(CMouseSkillIcon* pMouseSkillIcon)
{
	if (pMouseSkillIcon == nullptr)
		return E_FAIL;

	m_pMouseSkillIcon = pMouseSkillIcon;

	Safe_AddRef(pMouseSkillIcon);

	return S_OK;
}

void CMouseManager::Set_SkillIconIndex(const _tchar* pSkillInfoTag, CSkillManager::SkillGrade eGrade, _uint iText, const wchar_t* pNotice, _uint iIndex)
{
	
	m_pSkillInfoTag = pSkillInfoTag;
	m_eGrade = eGrade;
	m_pMouseSkillIcon->Set_TextureNum(iText);
	m_cSkillNotice = pNotice;
	m_iIndexNum = iIndex;
	

}

_uint CMouseManager::Get_SkillIconTextnum()
{
	return m_pMouseSkillIcon->Get_TextNum();
}


CSkillInfo * CMouseManager::Get_SkillInfo()
{
	m_pSkillInfoTag;
	m_eGrade;
	
	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();
	CSkillInfo* a = pSkillInstance->Get_SkillInfo(m_pSkillInfoTag, m_eGrade);
	
	return a;
}

void CMouseManager::Free()
{
	Safe_Release(m_pMouseSkillIcon);
}
