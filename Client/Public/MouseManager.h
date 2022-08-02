#pragma once
#include "Client_Defines.h"
#include "Base.h"
#include "SkillManager.h"

BEGIN(Client)

class CMouseSkillIcon;
class CUI;
class CSkillInfo;

class CMouseManager final : public CBase
{
	DECLARE_SINGLETON(CMouseManager)
public:
	enum PickType {TYPE_SKILL, TYPE_ITEM, TYPE_QUICK, TYPE_INVENTORY, TYPE_END};
public:
	CMouseManager();
	virtual ~CMouseManager() = default;


public:
	HRESULT Add_pMouseSkillIcon(CMouseSkillIcon* pMouseSkillIcon);
	void Set_SkillIconIndex(PickType ePick, const _tchar* pSkillInfoTag, CSkillManager::SkillGrade eGrade , _uint iText, const wchar_t* pNotice, _uint iIndex = 99);
	_uint Get_SkillIconTextnum();
	const _tchar* Get_SkillInfoTag() { return m_pSkillInfoTag; }
	CSkillManager::SkillGrade Get_Grade() { return m_eGrade; }
	CSkillInfo* Get_SkillInfo();
	_uint Get_Indexnum() { return m_iIndexNum; }
	const wchar_t* Get_SkillNotice() { return m_cSkillNotice; }
	PickType Get_PickType() { return m_ePick; }
	void Set_PrickType(PickType ePick) { m_ePick = ePick; }
	

private:
	CMouseSkillIcon* m_pMouseSkillIcon;
	const _tchar* m_pSkillInfoTag;
	CSkillManager::SkillGrade m_eGrade;
	_uint m_iIndexNum;
	const wchar_t* m_cSkillNotice;
	PickType m_ePick;
public:
	virtual void Free() override;

};
END

