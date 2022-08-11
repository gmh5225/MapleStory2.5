#pragma once

#include "Client_Defines.h"
#include "Base.h"
#include "ItemNotice.h"
#include "BlackWizardPatternUI.h"

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

	// For.CutScreen
	void On_CutScreen();
	void Off_CutScreen();

	void Tick(_float TimeDelta);
	void LateTick(_float TimeDelta);

private:
	class CLoading* m_pLoading = nullptr;
	class CCutScreen* m_pCutScreen = nullptr;

public:
	void Get_BlueMushmomHp(_uint iHp) { m_iBlueMushmomHp = iHp; };
	_uint Set_BlueMushmomHp() { return m_iBlueMushmomHp; };
	void Set_BlackWizardHp(_uint iHp) { m_iBlackWizardHp = iHp; };
	_uint Get_BlackWizardHp() { return m_iBlackWizardHp; };
	HRESULT Add_BlackWizardPatternUI(CBlackWizardPatternUI* pInstance);
	CBlackWizardPatternUI* Get_BlackWizardPatternUI() { return m_pBlackWizardPatternUI; }
public:
	virtual void Free() override;


private:
	_uint m_iBlueMushmomHp;
	_uint m_iBlackWizardHp;
	CBlackWizardPatternUI* m_pBlackWizardPatternUI;
};

END