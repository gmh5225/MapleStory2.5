#include "stdafx.h"
#include "..\Public\UIManager.h"
#include "GameInstance.h"
#include "Loading.h"

IMPLEMENT_SINGLETON(CUIManager)

CUIManager::CUIManager()
{
	m_iBlueMushmomHp = 3;
}

HRESULT CUIManager::Add_ItemNotice(CItemNotice * pItemNotice)
{
	if (pItemNotice == nullptr)
		return E_FAIL;
	Safe_AddRef(pItemNotice);
	m_pItemNotice = pItemNotice;

	return S_OK;
}

void CUIManager::Set_ItemNoticeTextNum(_uint iTextNum, bool bRender)
{
	m_pItemNotice->Set_TextureNum(iTextNum);
	m_pItemNotice->Set_Render(bRender);	
}

bool CUIManager::Check_Change(_uint iTextNum)
{
	if (m_pItemNotice->Get_Render() && m_pItemNotice->Get_TextNum() == iTextNum)
		return true;

	return false;
}
void CUIManager::Set_Loading()
{
	if (nullptr != m_pLoading)
		return;

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);


	CGameObject* pObj = nullptr;
	if (FAILED(pGameInstance->Add_GameObject(TEXT("Prototype_GameObject_Loading"), &pObj, nullptr)))
		return;

	m_pLoading = (CLoading*)pObj;


	Safe_Release(pGameInstance);
}

void CUIManager::Start_Loading()
{
	if (nullptr == m_pLoading)
		return;

	m_pLoading->StartLoading();
}
void CUIManager::End_Loading()
{
	if (nullptr == m_pLoading)
		return;

	m_pLoading->EndLoading();
}

void CUIManager::Tick(_float TimeDelta)
{
	m_pLoading->Tick(TimeDelta);
}

void CUIManager::LateTick(_float TimeDelta)
{
	m_pLoading->LateTick(TimeDelta);
}

HRESULT CUIManager::Add_BlackWizardPatternUI(CBlackWizardPatternUI * pInstance)
{
	if (pInstance == nullptr)
		return E_FAIL;
	Safe_AddRef(pInstance);
	m_pBlackWizardPatternUI = pInstance;

	return S_OK;
}

void CUIManager::Free()
{
	Safe_Release(m_pItemNotice);
	Safe_Release(m_pBlackWizardPatternUI);
	Safe_Release(m_pLoading);
}


