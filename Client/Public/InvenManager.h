#pragma once

#include "Client_Defines.h"
#include "Base.h"
#include "RedPortion.h"
//��� ������ �����Ͱ��� 
//����� UI���� �ϴ°��� 
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