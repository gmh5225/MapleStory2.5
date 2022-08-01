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
	HRESULT Add_QuickSlotSkill(CQuickSlotSkill* pQuickSlot);
	_bool Check_Texture(_uint iTextnum);
	HRESULT Change_Slot(_uint iIndexnum, CQuickSlotSkill* pQUickSlot);
private:
	list<CQuickSlotSkill*> m_QuickSlotSkill;

public:
	virtual void Free() override;

};
END

