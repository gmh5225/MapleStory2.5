#pragma once

#include "Client_Defines.h"
#include "Base.h"

BEGIN(Client)

class CQuestManager final : CBase
{
	DECLARE_SINGLETON(CQuestManager)

public:
	CQuestManager();
	virtual ~CQuestManager() = default;



public:
	virtual void Free() override;
};

END