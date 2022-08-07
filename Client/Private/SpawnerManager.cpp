#include "stdafx.h"
#include "..\Public\SpawnerManager.h"
#include "GameInstance.h"
#include "Spawner.h"

IMPLEMENT_SINGLETON(CSpawnerManager)


CSpawnerManager::CSpawnerManager()
{
	m_iIndexNum = 0;
}



void CSpawnerManager::Tick(_float fTimeDelta)
{

}

void CSpawnerManager::LateTick(_float fTimeDelta)
{
}

void CSpawnerManager::Add_Spawner(void* pArg)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CSpawner::SPAWNERINFO* pSpawnerInfo = (CSpawner::SPAWNERINFO*)pArg;


	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Spawner"), pSpawnerInfo->Level, TEXT("Layer_Spawner"), pArg)))
		int a = 0;

	Safe_Release(pGameInstance);
}

void CSpawnerManager::Check_MonsterIndex(_int index)
{
	m_iIndexNum = index;

	for (auto& iter : m_SpawnerList)
	{
		if (iter->Get_Index() == index)
			iter->Minus_Mushroom();
	}

}
void CSpawnerManager::Free()
{
	//Safe_Release(m_SpawnerList);
	for (auto& Spawner : m_SpawnerList)
	{
		Safe_Release(Spawner);
	}
}


