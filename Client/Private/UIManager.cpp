#include "stdafx.h"
#include "..\Public\UIManager.h"
#include "GameInstance.h"
#include "Loading.h"

IMPLEMENT_SINGLETON(CUIManager)

CUIManager::CUIManager()
{
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

void CUIManager::Free()
{
	Safe_Release(m_pLoading);
}


