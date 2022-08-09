#pragma once

#include "Client_Defines.h"
#include "Base.h"
#include "ItemNotice.h"

BEGIN(Client)

class CUIManager final : CBase
{
	DECLARE_SINGLETON(CUIManager)

public:
	CUIManager();
	virtual ~CUIManager() = default;

public:
	HRESULT Add_ItemNotice(CItemNotice* pItemNotice);
	void Set_ItemNoticeTextNum(_uint iTextNum, bool bRender);
	bool Check_Change(_uint iTextNum);
	
private:
	CItemNotice* m_pItemNotice;
public:
	virtual void Free() override;
};

END