#pragma once

#include "Client_Defines.h"
#include "Base.h"

BEGIN(Client)

class CInvenManager final : CBase
{
	DECLARE_SINGLETON(CInvenManager)

public:
	CInvenManager();
	virtual ~CInvenManager() = default;



public:
	virtual void Free() override;
};

END