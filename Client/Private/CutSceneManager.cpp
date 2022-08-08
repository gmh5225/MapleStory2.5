#include "stdafx.h"
#include "..\Public\CutSceneManager.h"

#include "GameInstance.h"
#include "Camera_Free.h"

IMPLEMENT_SINGLETON(CCutSceneManager)

CCutSceneManager::CCutSceneManager()
{
}














CCamera_Free* CCutSceneManager::Get_MainCam()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CCamera_Free* pCam = (CCamera_Free*)CGameInstance::Get_Instance()->Get_ObjectPtr(LEVEL_STATIC, TEXT("Layer_Camera"), 0);
	
	Safe_Release(pGameInstance);

	return pCam;
}



void CCutSceneManager::Free()
{

}
