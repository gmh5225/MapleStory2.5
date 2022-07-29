#include "stdafx.h"
#include "..\Public\Level_GamePlay.h"

#include "GameInstance.h"
#include "Camera_Free.h"
#include "UI.h"


CLevel_GamePlay::CLevel_GamePlay(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel(pGraphic_Device)
{
}

HRESULT CLevel_GamePlay::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

 	if (FAILED(Ready_Layer_Map(TEXT("Layer_Map"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Player(TEXT("Layer_Player"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Monster(TEXT("Layer_Monster"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Npc(TEXT("Layer_Npc"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_UI(TEXT("Layer_UI"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
		return E_FAIL;


	return S_OK;
}

void CLevel_GamePlay::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

HRESULT CLevel_GamePlay::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("게임플레이레벨임"));

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Camera(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CCamera::CAMERADESC			CameraDesc;

	CameraDesc.vEye = _float3(0.f, 10.f, -10.f);
	CameraDesc.vAt = _float3(0.f, 0.f, 0.f);
	CameraDesc.fFovy = D3DXToRadian(45.0f);
	CameraDesc.fAspect = (_float)g_iWinSizeX / g_iWinSizeY;
	CameraDesc.fNear = 0.2f;
	CameraDesc.fFar = 300.0f;

	CameraDesc.TransformDesc.fSpeedPerSec = 5.f;
	CameraDesc.TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Camera_Free"), LEVEL_GAMEPLAY, pLayerTag, &CameraDesc)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Player(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Player"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Terrain"), LEVEL_GAMEPLAY, pLayerTag)))
	//	return E_FAIL;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_OrangeMushroom"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;


	CVIBuffer_Voxel::VOXELDESC VoxDesc;
	VoxDesc.vPos = _float3{ 8.f, 2.f, 2.f };
	VoxDesc.vScale = _float3{ 0.3f, 0.3f, 0.3f };
	VoxDesc.vRotationAix = _float3{ 0.f, 1.f, 0.f };
	VoxDesc.fAngle = 40.f;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Wood"), LEVEL_GAMEPLAY, pLayerTag, &VoxDesc)))
		return E_FAIL;

	VoxDesc.vPos = _float3{ 15.f, -.1f, 2.f };
	VoxDesc.vScale = _float3{ 0.6f, 0.6f, 0.6f };
	VoxDesc.vRotationAix = _float3{ 0.f, 1.f, 0.f };
	VoxDesc.fAngle = 60.f;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Wood"), LEVEL_GAMEPLAY, pLayerTag, &VoxDesc)))
		return E_FAIL;

	VoxDesc.vPos = _float3{ 2.f, -.1f, -6.f };
	VoxDesc.vScale = _float3{ 0.4f, 0.4f, 0.4f };
	VoxDesc.vRotationAix = _float3{ 0.f, 1.f, 0.f };
	VoxDesc.fAngle = 52.f;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Wood"), LEVEL_GAMEPLAY, pLayerTag, &VoxDesc)))
		return E_FAIL;

	VoxDesc.vPos = _float3{ 10.f, -.1f, -14.f };
	VoxDesc.vScale = _float3{ 0.4f, 0.4f, 0.4f };
	VoxDesc.vRotationAix = _float3{ 0.f, 1.f, 0.f };
	VoxDesc.fAngle = 52.f;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Wood"), LEVEL_GAMEPLAY, pLayerTag, &VoxDesc)))
		return E_FAIL;

	VoxDesc.vPos = _float3{ -10.f, -.1f, 7.f };
	VoxDesc.vScale = _float3{ 0.4f, 0.4f, 0.4f };
	VoxDesc.vRotationAix = _float3{ 0.f, 1.f, 0.f };
	VoxDesc.fAngle = 52.f;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Wood"), LEVEL_GAMEPLAY, pLayerTag, &VoxDesc)))
		return E_FAIL;

	VoxDesc.vPos = _float3{ 10.f, -.1f, -12.f };
	VoxDesc.vScale = _float3{ 0.4f, 0.4f, 0.4f };
	VoxDesc.vRotationAix = _float3{ 0.f, 1.f, 0.f };
	VoxDesc.fAngle = 22.f;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Wood"), LEVEL_GAMEPLAY, pLayerTag, &VoxDesc)))
		return E_FAIL;

	VoxDesc.vPos = _float3{ 5.f, 3.f, 10.f };
	VoxDesc.vScale = _float3{ 0.4f, 0.4f, 0.4f };
	VoxDesc.vRotationAix = _float3{ 1.f, 1.f, 0.f };
	VoxDesc.fAngle = 100.f;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Wood"), LEVEL_GAMEPLAY, pLayerTag, &VoxDesc)))
		return E_FAIL;

	VoxDesc.vPos = _float3{ -6.f, -.2f, 6.f };
	VoxDesc.vScale = _float3{ 0.3f, 0.3f, 0.3f };
	VoxDesc.vRotationAix = _float3{ 0.f, 1.f, 0.f };
	VoxDesc.fAngle = 35.f;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_MushHouse"), LEVEL_GAMEPLAY, pLayerTag, &VoxDesc)))
		return E_FAIL;
	


	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Monster(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_RedSnail"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Slime"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_RibbonPig"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;


	
	
	Safe_Release(pGameInstance);


	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Npc(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_ElderStan"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;


	Safe_Release(pGameInstance);


	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Map(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	list<CMap_Manager::CUBEDATA>* pMapData = pGameInstance->ReadMap(L"MapData");

	for (auto& Data : *pMapData)
	{
		if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Cube"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
			return E_FAIL;
	}


	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_UI(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);



	CUI::UIINFO uiInfo;
	uiInfo.fSizeX = 300.f;
	uiInfo.fSizeY = 300.f;
	uiInfo.fX = 300.f;
	uiInfo.fY = 300.f;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillFrame"), LEVEL_GAMEPLAY, pLayerTag), &uiInfo))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Bulb"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuestUI"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Chat"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	Safe_Release(pGameInstance);


	return S_OK;
}

CLevel_GamePlay * CLevel_GamePlay::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_GamePlay*		pInstance = new CLevel_GamePlay(pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX(TEXT("Failed To Created : CLevel_GamePlay"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_GamePlay::Free()
{
	__super::Free();

}


