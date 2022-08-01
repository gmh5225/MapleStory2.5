#pragma once
#include "Client_Defines.h"
#include "Base.h"

BEGIN(Client)

class CQuickSlotSkill;

class CQuickSlotManager final : public CBase
{
	DECLARE_SINGLETON(CQuickSlotManager)
public:
	CQuickSlotManager();
	virtual ~CQuickSlotManager() = default;

public:
	list<CQuickSlotManager*> m_QuickSlotSkill;

public:
	virtual void Free() override;

};
END

