#include "stdafx.h"
#include "..\Public\SkillManager.h"
#include "SkillFrame.h"
#include "UI.h"

IMPLEMENT_SINGLETON(CSkillManager)

CSkillManager::CSkillManager()
	: m_iSkillPoint(0)
{
}



HRESULT CSkillManager::Set_pSkillFrame(CSkillFrame* pSkillFrame)
{
	if (pSkillFrame == nullptr)
		return E_FAIL;

	m_pSkillFrame = pSkillFrame;

	Safe_AddRef(m_pSkillFrame);

	return S_OK;
}

HRESULT CSkillManager::Add_SkillFrameImage(CUI* pSkillFrameImage)
{
	if (pSkillFrameImage == nullptr)
		return E_FAIL;

	m_pSkillFrame->Add_SkillFrameImage(pSkillFrameImage);

	return S_OK;
}

void CSkillManager::Free()
{
	Safe_Release(m_pSkillFrame);
}


