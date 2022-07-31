#pragma once
#include "Client_Defines.h"
#include "Base.h"

BEGIN(Client)

class CMouseManager final : CBase
{
	DECLARE_SINGLETON(CMouseManager)
public:
	CMouseManager();
	virtual ~CMouseManager() = default;

public:
	virtual void Free() override;
};
END

