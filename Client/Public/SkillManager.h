#pragma once

#include "Client_Defines.h"
#include "Base.h"

BEGIN(Client)

class CSkillManager final : CBase
{
	DECLARE_SINGLETON(CSkillManager)

public:
	CSkillManager();
	virtual ~CSkillManager() = default;



public:
	virtual void Free() override;
};

END