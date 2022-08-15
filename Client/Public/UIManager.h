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
	void SetTaxiChatBox(class CGameObject* pTaxiChatBox) { m_pTaxiChatBox = (class CTaxiChatBox*)pTaxiChatBox; }
	
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

	// For.DomiScreen
	void On_DomiScreen();
	void Off_DomiScreen();

	// For.TaxiChatBox
	void On_TaxiChatBox();
	void Off_TaxiChatBox();

	// For.Title
	void PlayTitleCurMap(LEVEL eLevel);
	_bool GetTitle() { return m_bTitle; }
	void SetTitle() { m_bTitle = true; }

	void Tick(_float TimeDelta);
	void LateTick(_float TimeDelta);



private:
	class CLoading* m_pLoading = nullptr;
	class CCutScreen* m_pCutScreen = nullptr;
	class CDomiScreen* m_pDomiScreen = nullptr;
	class CTaxiChatBox* m_pTaxiChatBox = nullptr;
	class CTitle*	m_pTitle = nullptr;

public:
	void Get_BlueMushmomHp(_uint iHp) { m_iBlueMushmomHp = iHp; };
	_uint Set_BlueMushmomHp() { return m_iBlueMushmomHp; };
	void Set_BlackWizardHp(_uint iHp) { m_iBlackWizardMaxHp = iHp, m_iBlackWizardHp = iHp; };
	_uint Get_BlackWizardHp() { return m_iBlackWizardHp; };
	void Fix_BlackWizardHp(_int iHp);
	void Get_GASHp(_uint iHp) { m_iGASHp = iHp; };
	_uint Set_GASHp() { return m_iGASHp; };
	HRESULT Add_BlackWizardPatternUI(CBlackWizardPatternUI* pInstance);
	CBlackWizardPatternUI* Get_BlackWizardPatternUI() { return m_pBlackWizardPatternUI; }
	bool Get_StartMove() { return m_bStartMove; }
	void Set_StartMove(bool bMove) { m_bStartMove = bMove; }
	bool Get_EndMove() { return m_bEndMove; }
	void Set_EndMove(bool bMove) { m_bEndMove = bMove; }
	_uint Get_PlayerHp() { return m_iPlayerHp; }
	void Set_PlayerHp(_uint iHp) { m_iPlayerHp += iHp; }
	void Full_PlayerHp() { m_iPlayerHp = 0; }
	_uint Get_PlayerExp() { return m_iPlayerExp; }
	void Set_PlayerExp(_uint iExp) { m_iPlayerExp += iExp; }
	_uint Get_PlayerLevel() { return m_iPlayerLevel; }
	void Level_Up(_uint iLevel) { m_iPlayerLevel += iLevel; m_iPlayerExp = 0; }

public:
	virtual void Free() override;


private:
	_int m_iBlueMushmomHp;
	_uint m_iBlackWizardMaxHp;
	_uint m_iBlackWizardHp;
	_int m_iGASHp;
	_uint m_iPlayerHp;
	_uint m_iPlayerExp;
	_uint m_iPlayerLevel;
	bool m_bStartMove;
	bool m_bEndMove;
	CBlackWizardPatternUI* m_pBlackWizardPatternUI;
	_bool m_bTitle = false;
};

END