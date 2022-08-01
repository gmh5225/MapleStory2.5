#pragma once
#include "Client_Defines.h"
#include "Base.h"
#include "SkillManager.h"

BEGIN(Client)

class CMouseSkillIcon;
class CUI;


class CMouseManager final : CBase
{
	DECLARE_SINGLETON(CMouseManager)
public:
	CMouseManager();
	virtual ~CMouseManager() = default;


public:
	HRESULT Add_pMouseSkillIcon(CMouseSkillIcon* pMouseSkillIcon);
	void Set_SkillIconIndex(const _tchar* pSkillInfoTag, CSkillManager::SkillGrade eGrade , _uint iIndex);

private:
	CMouseSkillIcon* m_pMouseSkillIcon;
	const _tchar* m_pSkillInfoTag;
	CSkillManager::SkillGrade m_eGrade;
public:
	virtual void Free() override;

};
END

