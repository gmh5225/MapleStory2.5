#include "stdafx.h"
#include "..\Public\ToolManager.h"

#include "GameInstance.h"
#include "Player.h"
#include "Level_Loading.h"


IMPLEMENT_SINGLETON(CToolManager)

CToolManager::CToolManager()
{

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

	Safe_Release(pGameInstance);

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


