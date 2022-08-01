#pragma once
#include "Client_Defines.h"
#include "Base.h"
BEGIN(Client)
class CSkillInfo : public CBase
{
protected:
	CSkillInfo();
	virtual ~CSkillInfo() = default;

public:
	const _uint Get_SkillLevel() { return m_iSkillLevel; }
	void Set_SkillLevel(_uint iSkillLevel) { m_iSkillLevel += iSkillLevel; }
	const _uint Get_SkillDamage() { return m_iSkillDamage; }
	void Set_SkillDamage(_uint iSkillDamage) { m_iSkillDamage += iSkillDamage; }
	const wchar_t* Get_SkillName() { return m_cSkillName; }
	const _uint Get_IndexNum() { return m_iIndexNum; }

public:
	virtual void Free() override;

protected:
	const wchar_t* m_cSkillName;
	_uint m_iSkillDamage;
	_uint m_iSkillLevel;
	_uint m_iIndexNum;
};
END

