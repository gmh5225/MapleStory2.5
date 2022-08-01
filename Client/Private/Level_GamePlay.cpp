#include "stdafx.h"
#include "..\Public\Level_GamePlay.h"

#include "GameInstance.h"
#include "Camera_Free.h"
#include "SkillInfo.h"
#include "SunCrossInfo.h"
#include "SolunaSlashInfo.h"
#include "SkillManager.h"
#include "UI.h"
#include "QuestManager.h"
#include "Maya.h"

CLevel_GamePlay::CLevel_GamePlay(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel(pGraphic_Device)
{
}

HRESULT CLevel_GamePlay::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	if (FAILED(Ready_SkillInfo()))
		return E_FAIL;

 	if (FAILED(Ready_Layer_Map(TEXT("Layer_Map"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Player(TEXT("Layer_Player"))))
		return E_FAIL;

	//if (FAILED(Ready_Layer_Monster(TEXT("Layer_Monster"))))
		//return E_FAIL;

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
	if (CQuestManager::Get_Instance()->Set_OrangeMushroom() >= 10)
		CQuestManager::Get_Instance()->QuestClear();
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


	CCreature::CRETUREDESC MonsterInfo;


	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_RedSnail"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Slime"), LEVEL_GAMEPLAY, pLayerTag)))
			return E_FAIL;
	

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_RibbonPig"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;


	for (int i = 0; i < 12; ++i)
	{
		MonsterInfo.vPos = _float3{_float( i - 6), -0.6f, -2.f };
		MonsterInfo.vScale = _float3{ 1.3f, 1.3f, 1.3f };
		MonsterInfo.fColRad = 1.f;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_OrangeMushroom"), LEVEL_GAMEPLAY, pLayerTag, &MonsterInfo)))
		return E_FAIL;
	}
	
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_StoneGolem"), LEVEL_GAMEPLAY, pLayerTag)))
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

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Maya"), LEVEL_GAMEPLAY, pLayerTag)))
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


	CUI::UIINFO SkillFrameiInfo;
	SkillFrameiInfo.fSizeX = 318.f;
	SkillFrameiInfo.fSizeY = 360.f;
	SkillFrameiInfo.fX = 900.f;
	SkillFrameiInfo.fY = 300.f;

	CUI::UIINFO MouseCursorInfo;
	MouseCursorInfo.fSizeX = 24.f;
	MouseCursorInfo.fSizeY = 28.f;

	

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Bulb"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuestUI"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Chat"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillFrame"), LEVEL_GAMEPLAY, pLayerTag, &SkillFrameiInfo)))
		return E_FAIL;

	Ready_SkillFrameBtn(pLayerTag);

	Ready_SkillIcon(pLayerTag);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_HpBarBase"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_HpBarHp"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_HpBarMp"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_HpBarIcon"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_ExpBase"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_ExpBar"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_ExpLine"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_MenuIcon"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	Ready_QuickSlot(pLayerTag);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_MouseCursor"), LEVEL_GAMEPLAY, pLayerTag, &MouseCursorInfo)))
		return E_FAIL;

	Safe_Release(pGameInstance);


	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_SkillFrameBtn(const _tchar * pLayerTag)
{
	//스킬Up Btn 간격 가로 144px 세로 40px
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CUI::UIINFO SkillUpBtnInfo1;
	SkillUpBtnInfo1.fSizeX = 16.f;
	SkillUpBtnInfo1.fSizeY = 14.f;
	SkillUpBtnInfo1.fMoveX = -16.f;
	SkillUpBtnInfo1.fMoveY = -60.f;
	SkillUpBtnInfo1.iNum = 1;

	CUI::UIINFO SkillUpBtnInfo2;
	SkillUpBtnInfo2.fSizeX = 16.f;
	SkillUpBtnInfo2.fSizeY = 14.f;
	SkillUpBtnInfo2.fMoveX = 128.f;
	SkillUpBtnInfo2.fMoveY = -60.f;
	SkillUpBtnInfo2.iNum = 2;

	CUI::UIINFO SkillUpBtnInfo3;
	SkillUpBtnInfo3.fSizeX = 16.f;
	SkillUpBtnInfo3.fSizeY = 14.f;
	SkillUpBtnInfo3.fMoveX = -16.f;
	SkillUpBtnInfo3.fMoveY = -20.f;
	SkillUpBtnInfo3.iNum = 3;

	CUI::UIINFO SkillUpBtnInfo4;
	SkillUpBtnInfo4.fSizeX = 16.f;
	SkillUpBtnInfo4.fSizeY = 14.f;
	SkillUpBtnInfo4.fMoveX = 128.f;
	SkillUpBtnInfo4.fMoveY = -20.f;
	SkillUpBtnInfo4.iNum = 4;

	CUI::UIINFO SkillUpBtnInfo5;
	SkillUpBtnInfo5.fSizeX = 16.f;
	SkillUpBtnInfo5.fSizeY = 14.f;
	SkillUpBtnInfo5.fMoveX = -16.f;
	SkillUpBtnInfo5.fMoveY = 20.f;
	SkillUpBtnInfo5.iNum = 5;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillUpBtn"), LEVEL_GAMEPLAY, pLayerTag, &SkillUpBtnInfo1)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillUpBtn"), LEVEL_GAMEPLAY, pLayerTag, &SkillUpBtnInfo2)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillUpBtn"), LEVEL_GAMEPLAY, pLayerTag, &SkillUpBtnInfo3)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillUpBtn"), LEVEL_GAMEPLAY, pLayerTag, &SkillUpBtnInfo4)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillUpBtn"), LEVEL_GAMEPLAY, pLayerTag, &SkillUpBtnInfo5)))
		return E_FAIL;

	

	CUI::UIINFO SkillGradeBtnInfo0;
	SkillGradeBtnInfo0.fSizeX = 25.f;
	SkillGradeBtnInfo0.fSizeY = 20.f;
	SkillGradeBtnInfo0.fMoveX = -135.f;
	SkillGradeBtnInfo0.fMoveY = -143.f;

	CUI::UIINFO SkillGradeBtnInfo1;
	SkillGradeBtnInfo1.fSizeX = 25.f;
	SkillGradeBtnInfo1.fSizeY = 20.f;
	SkillGradeBtnInfo1.fMoveX = -108.f;
	SkillGradeBtnInfo1.fMoveY = -143.f;

	CUI::UIINFO SkillGradeBtnInfo2;
	SkillGradeBtnInfo2.fSizeX = 25.f;
	SkillGradeBtnInfo2.fSizeY = 20.f;
	SkillGradeBtnInfo2.fMoveX = -81.f;
	SkillGradeBtnInfo2.fMoveY = -143.f;

	CUI::UIINFO SkillGradeBtnInfo3;
	SkillGradeBtnInfo3.fSizeX = 25.f;
	SkillGradeBtnInfo3.fSizeY = 20.f;
	SkillGradeBtnInfo3.fMoveX = -54.f;
	SkillGradeBtnInfo3.fMoveY = -143.f;

	CUI::UIINFO SkillGradeBtnInfo4;
	SkillGradeBtnInfo4.fSizeX = 25.f;
	SkillGradeBtnInfo4.fSizeY = 20.f;
	SkillGradeBtnInfo4.fMoveX = -27.f;
	SkillGradeBtnInfo4.fMoveY = -143.f;

	CUI::UIINFO SkillGradeBtnInfo5;
	SkillGradeBtnInfo5.fSizeX = 25.f;
	SkillGradeBtnInfo5.fSizeY = 20.f;
	SkillGradeBtnInfo5.fMoveX = 0.f;
	SkillGradeBtnInfo5.fMoveY = -143.f;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn0"), LEVEL_GAMEPLAY, pLayerTag, &SkillGradeBtnInfo0)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn1"), LEVEL_GAMEPLAY, pLayerTag, &SkillGradeBtnInfo1)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn2"), LEVEL_GAMEPLAY, pLayerTag, &SkillGradeBtnInfo2)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn3"), LEVEL_GAMEPLAY, pLayerTag, &SkillGradeBtnInfo3)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn4"), LEVEL_GAMEPLAY, pLayerTag, &SkillGradeBtnInfo4)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn5"), LEVEL_GAMEPLAY, pLayerTag, &SkillGradeBtnInfo5)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_SkillIcon(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CUI::UIINFO SunCrossInfo;
	SunCrossInfo.fSizeX = 32.f;
	SunCrossInfo.fSizeY = 32.f;
	SunCrossInfo.fMoveX = -129.f;
	SunCrossInfo.fMoveY = -69.f;

	CUI::UIINFO SolunaSlashInfo;
	SolunaSlashInfo.fSizeX = 32.f;
	SolunaSlashInfo.fSizeY = 32.f;
	SolunaSlashInfo.fMoveX = 15.f;
	SolunaSlashInfo.fMoveY = -69.f;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SunCrossIcon"), LEVEL_GAMEPLAY, pLayerTag, &SunCrossInfo)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SolunaSlashIcon"), LEVEL_GAMEPLAY, pLayerTag, &SolunaSlashInfo)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_SkillInfo()
{
	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();
	CSunCrossInfo* pSunCross = new CSunCrossInfo;
	CSolunaSlashInfo* pSolunaSlash = new CSolunaSlashInfo;
	
	if (FAILED(pSkillInstance->Add_SkillInfo(TEXT("SunCrossInfo"), CSkillManager::GRADE_BEGENNER, pSunCross)))
		return E_FAIL;
	
	if (FAILED(pSkillInstance->Add_SkillInfo(TEXT("SolunaSlashInfo"), CSkillManager::GRADE_BEGENNER, pSolunaSlash)))
		return E_FAIL;

	return S_OK;

	
}

HRESULT CLevel_GamePlay::Ready_QuickSlot(const _tchar* pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	//틀어진x 15 x간격 5 y간격 5

	CUI::UIINFO QuickSlot1;
	QuickSlot1.fSizeX = 50.f;
	QuickSlot1.fSizeY = 50.f;
	QuickSlot1.fX = 350.f;
	QuickSlot1.fY = 580.f;

	CUI::UIINFO QuickSlot2;
	QuickSlot2.fSizeX = 50.f;
	QuickSlot2.fSizeY = 50.f;
	QuickSlot2.fX = 365.f;
	QuickSlot2.fY = 635.f;

	CUI::UIINFO QuickSlot3;
	QuickSlot3.fSizeX = 50.f;
	QuickSlot3.fSizeY = 50.f;
	QuickSlot3.fX = 405.f;
	QuickSlot3.fY = 580.f;

	CUI::UIINFO QuickSlot4;
	QuickSlot4.fSizeX = 50.f;
	QuickSlot4.fSizeY = 50.f;
	QuickSlot4.fX = 420.f;
	QuickSlot4.fY = 635.f;

	CUI::UIINFO QuickSlot5;
	QuickSlot5.fSizeX = 50.f;
	QuickSlot5.fSizeY = 50.f;
	QuickSlot5.fX = 460.f;
	QuickSlot5.fY = 580.f;

	CUI::UIINFO QuickSlot6;
	QuickSlot6.fSizeX = 50.f;
	QuickSlot6.fSizeY = 50.f;
	QuickSlot6.fX = 475.f;
	QuickSlot6.fY = 635.f;

	CUI::UIINFO QuickSlot7;
	QuickSlot7.fSizeX = 50.f;
	QuickSlot7.fSizeY = 50.f;
	QuickSlot7.fX = 515.f;
	QuickSlot7.fY = 580.f;

	CUI::UIINFO QuickSlot8;
	QuickSlot8.fSizeX = 50.f;
	QuickSlot8.fSizeY = 50.f;
	QuickSlot8.fX = 530.f;
	QuickSlot8.fY = 635.f;

	CUI::UIINFO QuickSlot9;
	QuickSlot9.fSizeX = 50.f;
	QuickSlot9.fSizeY = 50.f;
	QuickSlot9.fX = 765.f;
	QuickSlot9.fY = 580.f;

	CUI::UIINFO QuickSlot10;
	QuickSlot10.fSizeX = 50.f;
	QuickSlot10.fSizeY = 50.f;
	QuickSlot10.fX = 750.f;
	QuickSlot10.fY = 635.f;

	CUI::UIINFO QuickSlot11;
	QuickSlot11.fSizeX = 50.f;
	QuickSlot11.fSizeY = 50.f;
	QuickSlot11.fX = 820.f;
	QuickSlot11.fY = 580.f;

	CUI::UIINFO QuickSlot12;
	QuickSlot12.fSizeX = 50.f;
	QuickSlot12.fSizeY = 50.f;
	QuickSlot12.fX = 805.f;
	QuickSlot12.fY = 635.f;

	CUI::UIINFO QuickSlot13;
	QuickSlot13.fSizeX = 50.f;
	QuickSlot13.fSizeY = 50.f;
	QuickSlot13.fX = 875.f;
	QuickSlot13.fY = 580.f;

	CUI::UIINFO QuickSlot14;
	QuickSlot14.fSizeX = 50.f;
	QuickSlot14.fSizeY = 50.f;
	QuickSlot14.fX = 860.f;
	QuickSlot14.fY = 635.f;

	CUI::UIINFO QuickSlot15;
	QuickSlot15.fSizeX = 50.f;
	QuickSlot15.fSizeY = 50.f;
	QuickSlot15.fX = 930.f;
	QuickSlot15.fY = 580.f;

	CUI::UIINFO QuickSlot16;
	QuickSlot16.fSizeX = 50.f;
	QuickSlot16.fSizeY = 50.f;
	QuickSlot16.fX = 915.f;
	QuickSlot16.fY = 635.f;
	
	

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_GAMEPLAY, pLayerTag, &QuickSlot1)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_GAMEPLAY, pLayerTag, &QuickSlot2)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_GAMEPLAY, pLayerTag, &QuickSlot3)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_GAMEPLAY, pLayerTag, &QuickSlot4)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_GAMEPLAY, pLayerTag, &QuickSlot5)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_GAMEPLAY, pLayerTag, &QuickSlot6)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_GAMEPLAY, pLayerTag, &QuickSlot7)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_GAMEPLAY, pLayerTag, &QuickSlot8)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_GAMEPLAY, pLayerTag, &QuickSlot9)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_GAMEPLAY, pLayerTag, &QuickSlot10)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_GAMEPLAY, pLayerTag, &QuickSlot11)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_GAMEPLAY, pLayerTag, &QuickSlot12)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_GAMEPLAY, pLayerTag, &QuickSlot13)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_GAMEPLAY, pLayerTag, &QuickSlot14)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_GAMEPLAY, pLayerTag, &QuickSlot15)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_GAMEPLAY, pLayerTag, &QuickSlot16)))
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


