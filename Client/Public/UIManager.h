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
	virtual void Free() override;
};

END