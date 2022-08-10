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
	// For.Loading
	void Set_Loading();
	void Start_Loading();
	void End_Loading();

	void Tick(_float TimeDelta);
	void LateTick(_float TimeDelta);

private:
	class CLoading* m_pLoading = nullptr;


public:
	virtual void Free() override;
};

END