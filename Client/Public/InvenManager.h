#pragma once

#include "Client_Defines.h"
#include "Base.h"
#include "RedPortion.h"
//모든 아이템 데이터관리 
//출력은 UI에서 하는것임 
BEGIN(Client)

class CInvenManager final : CBase
{
	DECLARE_SINGLETON(CInvenManager)

private:
	CInvenManager();
	virtual ~CInvenManager() = default;

public:
	HRESULT AddItemNum(void* pArg);

private:
	CRedPortion* m_pRedPortion;
	

public:
	virtual void Free() override;
};

END