#include "stdafx.h"
#include "..\Public\QuickSlotManager.h"
#include "QuickSlotSkill.h"

IMPLEMENT_SINGLETON(CQuickSlotManager)

CQuickSlotManager::CQuickSlotManager()
{
}

HRESULT CQuickSlotManager::Add_QuickSlotSkill(CQuickSlotSkill* pQuickSlot)
{
	if (pQuickSlot == nullptr)
		return E_FAIL;
	m_QuickSlotSkill.push_back(pQuickSlot);
	
	Safe_AddRef(pQuickSlot);

	return S_OK;
}

_bool CQuickSlotManager::Check_Texture(_uint iTextnum)
{
	for (auto iter : m_QuickSlotSkill)
	{
		if (iter->Get_TextNum() == iTextnum)
			return true;
	}
	return false;
}

HRESULT CQuickSlotManager::Change_Slot(_uint iIndexnum, CQuickSlotSkill* pQuickSlot)
{
	
	for (auto iter : m_QuickSlotSkill)
	{
		if (iter->Get_IndexNum() == iIndexnum)
		{
			if (iIndexnum == 99)
			{
				iter->Set_Data(5, nullptr, CSkillManager::GRADE_END, nullptr);
			}
			iter->Set_Data(pQuickSlot->Get_TextNum(), pQuickSlot->Get_Tag(), pQuickSlot->Get_Grade(), pQuickSlot->Get_Notice());
		}
	}
	return S_OK;
}

void CQuickSlotManager::Free()
{
	for (auto iter : m_QuickSlotSkill)
	{
		Safe_Release(iter);
	}
	m_QuickSlotSkill.clear();
}
