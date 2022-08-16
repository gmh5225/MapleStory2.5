#include "stdafx.h"
#include "..\Public\ToolManager.h"

#include "GameInstance.h"
#include "Player.h"
#include "Level_Loading.h"
#include "SpawnerManager.h"


IMPLEMENT_SINGLETON(CToolManager)

CToolManager::CToolManager()
{

}




void CToolManager::SetDestLevel(LEVEL eLevel, _float3 vDestPos)
{

		m_eDestLevel = eLevel; m_vDestPos = vDestPos;	
}

void CToolManager::CheckDestLevel(CCollider* pColliderCom, LPDIRECT3DDEVICE9 pGraphic_Device)
{
	if (LEVEL_END == m_eDestLevel)
		return;

	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CPlayer* pPlayer = (CPlayer*)pGameInstance->Get_ObjectPtr(LEVEL_STATIC, TEXT("Layer_Player"), 0);;
	pPlayer->SetRespownPos(m_vDestPos);

	pColliderCom->ResetSection();


	if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(pGraphic_Device, m_eDestLevel))))
		return;

	m_eDestLevel = LEVEL_END;


	CSpawnerManager::Get_Instance()->Free_Spawner();

	Safe_Release(pGameInstance);

}

LEVEL CToolManager::Get_CurLevel()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);


	_uint iLevel = pGameInstance->Get_CurLevel();


	Safe_Release(pGameInstance);

	return (LEVEL)iLevel;
}

CGameObject* CToolManager::GetPlayer()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CGameObject* pObj = pGameInstance->Get_ObjectPtr(LEVEL_STATIC, TEXT("Layer_Player"), 0);

	Safe_Release(pGameInstance);

	return pObj;
}

void CToolManager::Free()
{

}


