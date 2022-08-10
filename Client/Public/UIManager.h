#pragma once

#include "Client_Defines.h"
#include "Base.h"

BEGIN(Client)

class CUIManager final : CBase
{
	DECLARE_SINGLETON(CUIManager)

public:
	CUIManager();
	virtual ~CUIManager() = default;


public:
	void Get_BlueMushmomHp(_uint iHp) { m_iBlueMushmomHp = iHp; };
	_uint Set_BlueMushmomHp() { return m_iBlueMushmomHp; };


public:
	virtual void Free() override;


private:
	_uint m_iBlueMushmomHp;
};

END