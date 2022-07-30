#pragma once
#include "Client_Defines.h"
#include "Base.h"
BEGIN(Client)
class CSkillInfo : public CBase
{
public:
	CSkillInfo();
	virtual ~CSkillInfo() = default;


public:
	virtual void Free() override;
};
END

