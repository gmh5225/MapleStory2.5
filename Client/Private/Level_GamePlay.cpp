#include "stdafx.h"
#include "..\Public\Level_GamePlay.h"

#include "GameInstance.h"
#include "Camera_Free.h"
#include "SkillInfo.h"
#include "SunCrossInfo.h"
#include "SolunaSlashInfo.h"
#include "WarriorReefInfo.h"
#include "ReefAttackInfo.h"
#include "SpearPullingInfo.h"
#include "SkillManager.h"
#include "UI.h"
#include "QuestManager.h"
#include "SpawnerManager.h"
#include "Maya.h"
#include "Level_Loading.h"
#include "MainApp.h"
#include "Potal.h"

CLevel_GamePlay::CLevel_GamePlay(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel(pGraphic_Device)
{
}

HRESULT CLevel_GamePlay::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	if (g_bStaticClone == false)
	{
		if (FAILED(Ready_SkillInfo()))
			return E_FAIL;

		if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
			return E_FAIL;

		if (FAILED(Ready_Layer_Player(TEXT("Layer_Player"))))
			return E_FAIL;

		if (FAILED(Ready_Layer_UI(TEXT("Layer_UI"))))
			return E_FAIL;
		g_bStaticClone = true;
	}


	if (FAILED(Ready_Layer_Map(TEXT("Layer_Map"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Monster(TEXT("Layer_Monster"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Npc(TEXT("Layer_Npc"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Spawner(TEXT("Layer_Spawner"))))
		return E_FAIL;

	return S_OK;
}

void CLevel_GamePlay::Tick(_float fTimeDelta)
{
	if (CQuestManager::Get_Instance()->Set_OrangeMushroom() >= 10)
		CQuestManager::Get_Instance()->QuestClear();
	else if (CQuestManager::Get_Instance()->Set_StoneGolem() >= 1)
		CQuestManager::Get_Instance()->QuestClear();
	//__super::Tick(fTimeDelta);
	
	__super::Tick(fTimeDelta);

	g_bGamePlay = true;
	if (GetKeyState('N') & 0x8000)
	{
		CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);

		m_pColliderCom->ResetSection();
		if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_HENESYS))))
			return;
		
		
		Safe_Release(pGameInstance);

	}
	else if (GetKeyState('B') & 0x8000)
	{
		CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);

		m_pColliderCom->ResetSection();
		if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_ELENYA))))
			return;


		Safe_Release(pGameInstance);

	}
	

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

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Camera_Free"), LEVEL_STATIC, pLayerTag, &CameraDesc)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Player(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Player"), LEVEL_STATIC, pLayerTag)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}



HRESULT CLevel_GamePlay::Ready_Layer_Monster(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_StoneGolem"), LEVEL_HENESYS, pLayerTag)))
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



	CPotal::POTALDESC PotalDesc;
	PotalDesc.eDestLevel = LEVEL_HENESYS;
	PotalDesc.Pos = _float3(29.f, 4.f, -12.f);
	PotalDesc.DestPos = _float3(-2.f, 2.5f, 0.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Potal"), LEVEL_GAMEPLAY, pLayerTag, &PotalDesc)))
		return E_FAIL;





	list<CMap_Manager::CUBEDATA>* pMapData = pGameInstance->ReadMap(L"Map_Henesys");
	for (auto& Data : *pMapData)
	{
		if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Cube"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
			return E_FAIL;
	}


	list<CMap_Manager::MODELDESC>* pModelData = pGameInstance->ReadModel(L"Total_Henesys");
	if (nullptr != pModelData)
	{
		for (auto& Model : *pModelData)
		{
			CVIBuffer_Voxel::VOXELDESC VoxDesc;
			CopyMemory(VoxDesc.cFileName, Model.cModelName, sizeof(_tchar) * 256);
			VoxDesc.vPos = Model.vPos;

			_float4x4 Matrix;
			D3DXMatrixIdentity(&Matrix);

			D3DXMatrixRotationAxis(&Matrix, &_float3(0.f, 1.f, 0.f), D3DXToRadian(45.f));

			D3DXVec3TransformCoord((&VoxDesc.vPos), (&VoxDesc.vPos), &Matrix);


			VoxDesc.vScale = _float3{ Model.fScale, Model.fScale, Model.fScale };
			VoxDesc.vRotationAix = Model.vAix;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Wood"), LEVEL_GAMEPLAY, pLayerTag, &VoxDesc)))
				return E_FAIL;
		}

	}

	if (FAILED(Ready_Layer_Section(TEXT("Layer_Section"))))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Section(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	CComponent*			pComponent = pGameInstance->Clone_Component(LEVEL_STATIC, TEXT("Prototype_Component_Collider"));
	if (nullptr == pComponent)
		return E_FAIL;
	m_pColliderCom = (CCollider*)pComponent;



	CMap_Manager::CUBEDATA Data;
	ZeroMemory(&Data, sizeof(CMap_Manager::CUBEDATA));

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			_float XIndex = i*5.f;
			_float ZIndex = j*5.f;
			Data.vPos = _float3((-12.f + XIndex) + ZIndex, 2.f, -1 - XIndex);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
				return E_FAIL;
		}
	}
	Data.vPos = _float3(-10.f, 2.f, 4.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
		return E_FAIL;
	Data.vPos = _float3(-5.f, 2.f, 4.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
		return E_FAIL;
	Data.vPos = _float3(0.f, 2.f, 4.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
		return E_FAIL;
	Data.vPos = _float3(5.f, 2.f, 4.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
		return E_FAIL;
	Data.vPos = _float3(10.f, 2.f, 4.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
		return E_FAIL;

	Data.vPos = _float3(-5.f, 2.f, 9.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
		return E_FAIL;
	Data.vPos = _float3(0.f, 2.f, 9.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
		return E_FAIL;
	Data.vPos = _float3(5.f, 2.f, 9.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
		return E_FAIL;

	Data.vPos = _float3(9.f, 7.f, 4.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
		return E_FAIL;
	Data.vPos = _float3(9.f, 7.f, -1.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
		return E_FAIL;
	Data.vPos = _float3(9.f, 7.f, -6.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
		return E_FAIL;
	Data.vPos = _float3(14.f, 7.f, 4.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
		return E_FAIL;
	Data.vPos = _float3(14.f, 7.f, -1.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
		return E_FAIL;
	Data.vPos = _float3(14.f, 7.f, -6.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
		return E_FAIL;
	Data.vPos = _float3(19.f, 7.f, 4.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
		return E_FAIL;
	Data.vPos = _float3(19.f, 7.f, -1.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
		return E_FAIL;
	Data.vPos = _float3(19.f, 7.f, -6.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_GAMEPLAY, pLayerTag, &Data)))
		return E_FAIL;


	
	Safe_Release(pGameInstance);


	m_pColliderCom->Set_SectionCubes();
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

	

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Bulb"), LEVEL_HENESYS, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuestUI"), LEVEL_STATIC, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillFrame"), LEVEL_STATIC, pLayerTag, &SkillFrameiInfo)))
		return E_FAIL;

	Ready_SkillFrameBtn(pLayerTag);

	Ready_SkillIcon(pLayerTag);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_HpBarBase"), LEVEL_STATIC, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_HpBarHp"), LEVEL_STATIC, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_HpBarMp"), LEVEL_STATIC, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_HpBarIcon"), LEVEL_STATIC, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_ExpBase"), LEVEL_STATIC, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_ExpBar"), LEVEL_STATIC, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_ExpLine"), LEVEL_STATIC, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_MenuIcon"), LEVEL_STATIC, pLayerTag)))
		return E_FAIL;

	Ready_QuickSlot(pLayerTag);

	Ready_QuickSlotSkill(pLayerTag);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_MouseSkillIcon"), LEVEL_STATIC, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_MouseCursor"), LEVEL_STATIC, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Chat"), LEVEL_STATIC, pLayerTag)))
		return E_FAIL;

	Safe_Release(pGameInstance);


	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Spawner(const _tchar * pLayerTag)
{
	CSpawner::SPAWNERINFO MonsterInfo;

	MonsterInfo.MonsterName = TEXT("OrangeMushroom");
	MonsterInfo.MonsterPos = _float3{ 25.f , 5.1f, -3.f };
	MonsterInfo.SpawnerNum = 0;
	MonsterInfo.MonsterNum = 3;
	MonsterInfo.MonsterColRad = 1.f;

	CSpawnerManager::Get_Instance()->Add_Spawner(&MonsterInfo);

	MonsterInfo.MonsterName = TEXT("OrangeMushroom");
	MonsterInfo.MonsterPos = _float3{ 26.f , 5.1f, -11.f };
	MonsterInfo.SpawnerNum = 1;
	MonsterInfo.MonsterNum = 3;
	MonsterInfo.MonsterColRad = 1.f;

	CSpawnerManager::Get_Instance()->Add_Spawner(&MonsterInfo);

	MonsterInfo.MonsterName = TEXT("OrangeMushroom");
	MonsterInfo.MonsterPos = _float3{ 3.f , 2.1f, 1.f };
	MonsterInfo.SpawnerNum = 2;
	MonsterInfo.MonsterNum = 3;
	MonsterInfo.MonsterColRad = 1.f;

	CSpawnerManager::Get_Instance()->Add_Spawner(&MonsterInfo);

	MonsterInfo.MonsterName = TEXT("RibbonPig");
	MonsterInfo.MonsterPos = _float3{ 26.f , 5.1f, -11.f };
	MonsterInfo.SpawnerNum = 2;
	MonsterInfo.MonsterNum = 3;
	MonsterInfo.MonsterColRad = 1.f;

	CSpawnerManager::Get_Instance()->Add_Spawner(&MonsterInfo);


	MonsterInfo.MonsterName = TEXT("Slime");
	MonsterInfo.MonsterPos = _float3{ 25.f , 5.1f, -3.f };
	MonsterInfo.SpawnerNum = 3;
	MonsterInfo.MonsterNum = 3;
	MonsterInfo.MonsterColRad = 1.f;

	CSpawnerManager::Get_Instance()->Add_Spawner(&MonsterInfo);

	MonsterInfo.MonsterName = TEXT("RedSnail");
	MonsterInfo.MonsterPos = _float3{ 35.f , 5.f, -3.f };
	MonsterInfo.SpawnerNum = 4;
	MonsterInfo.MonsterNum = 3;
	MonsterInfo.MonsterColRad = 1.f;

	CSpawnerManager::Get_Instance()->Add_Spawner(&MonsterInfo);

	MonsterInfo.MonsterName = TEXT("BlueSnail");
	MonsterInfo.MonsterPos = _float3{ 35.f , 5.f, -3.f };
	MonsterInfo.SpawnerNum = 5;
	MonsterInfo.MonsterNum = 3;
	MonsterInfo.MonsterColRad = 1.f;

	CSpawnerManager::Get_Instance()->Add_Spawner(&MonsterInfo);

	MonsterInfo.MonsterName = TEXT("GreenMushroom");
	MonsterInfo.MonsterPos = _float3{ 28.f , 2.1f, -3.f };
	MonsterInfo.SpawnerNum = 6;
	MonsterInfo.MonsterNum = 3;
	MonsterInfo.MonsterColRad = 1.f;

	CSpawnerManager::Get_Instance()->Add_Spawner(&MonsterInfo);

	MonsterInfo.MonsterName = TEXT("GoStump");
	MonsterInfo.MonsterPos = _float3{ 28.f , 2.1f, -3.f };
	MonsterInfo.SpawnerNum = 7;
	MonsterInfo.MonsterNum = 3;
	MonsterInfo.MonsterColRad = 1.f;

	CSpawnerManager::Get_Instance()->Add_Spawner(&MonsterInfo);


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

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillUpBtn"), LEVEL_STATIC, pLayerTag, &SkillUpBtnInfo1)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillUpBtn"), LEVEL_STATIC, pLayerTag, &SkillUpBtnInfo2)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillUpBtn"), LEVEL_STATIC, pLayerTag, &SkillUpBtnInfo3)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillUpBtn"), LEVEL_STATIC, pLayerTag, &SkillUpBtnInfo4)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillUpBtn"), LEVEL_STATIC, pLayerTag, &SkillUpBtnInfo5)))
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

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn0"), LEVEL_STATIC, pLayerTag, &SkillGradeBtnInfo0)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn1"), LEVEL_STATIC, pLayerTag, &SkillGradeBtnInfo1)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn2"), LEVEL_STATIC, pLayerTag, &SkillGradeBtnInfo2)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn3"), LEVEL_STATIC, pLayerTag, &SkillGradeBtnInfo3)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn4"), LEVEL_STATIC, pLayerTag, &SkillGradeBtnInfo4)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn5"), LEVEL_STATIC, pLayerTag, &SkillGradeBtnInfo5)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_SkillIcon(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CUI::UIINFO ReefAttackInfo;
	ReefAttackInfo.fSizeX = 32.f;
	ReefAttackInfo.fSizeY = 32.f;
	ReefAttackInfo.fMoveX = -129.f;
	ReefAttackInfo.fMoveY = -69.f;

	CUI::UIINFO WarriorReefInfo;
	WarriorReefInfo.fSizeX = 32.f;
	WarriorReefInfo.fSizeY = 32.f;
	WarriorReefInfo.fMoveX = 15.f;
	WarriorReefInfo.fMoveY = -69.f;

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

	CUI::UIINFO SpearPullingInfo;
	SpearPullingInfo.fSizeX = 32.f;
	SpearPullingInfo.fSizeY = 32.f;
	SpearPullingInfo.fMoveX = -129.f;
	SpearPullingInfo.fMoveY = -69.f;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_ReefAttackIcon"), LEVEL_STATIC, pLayerTag, &ReefAttackInfo)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_WarriorReefIcon"), LEVEL_STATIC, pLayerTag, &WarriorReefInfo)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SunCrossIcon"), LEVEL_STATIC, pLayerTag, &SunCrossInfo)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SolunaSlashIcon"), LEVEL_STATIC, pLayerTag, &SolunaSlashInfo)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SpearPullingIcon"), LEVEL_STATIC, pLayerTag, &SpearPullingInfo)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_SkillInfo()
{
	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();
	CSunCrossInfo* pSunCross = new CSunCrossInfo;
	CSolunaSlashInfo* pSolunaSlash = new CSolunaSlashInfo;
	CReefAttackInfo* pReefAttack = new CReefAttackInfo;
	CSpearPullingInfo* pSpearPulling = new CSpearPullingInfo;
	CWarriorReefInfo* pWarriorReef = new CWarriorReefInfo;
		if (FAILED(pSkillInstance->Add_SkillInfo(TEXT("ReefAttackInfo"), CSkillManager::GRADE_BEGENNER, pReefAttack)))
		return E_FAIL;

	if (FAILED(pSkillInstance->Add_SkillInfo(TEXT("WarriorReefInfo"), CSkillManager::GRADE_BEGENNER, pWarriorReef)))
		return E_FAIL;

	if (FAILED(pSkillInstance->Add_SkillInfo(TEXT("SunCrossInfo"), CSkillManager::GRADE_FIRST, pSunCross)))
		return E_FAIL;
	
	if (FAILED(pSkillInstance->Add_SkillInfo(TEXT("SolunaSlashInfo"), CSkillManager::GRADE_FIRST, pSolunaSlash)))
		return E_FAIL;

	if (FAILED(pSkillInstance->Add_SkillInfo(TEXT("SpearPullingInfo"), CSkillManager::GRADE_SECOND, pSpearPulling)))
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
	QuickSlot1.iNum = 0;

	CUI::UIINFO QuickSlot2;
	QuickSlot2.fSizeX = 50.f;
	QuickSlot2.fSizeY = 50.f;
	QuickSlot2.fX = 365.f;
	QuickSlot2.fY = 635.f;
	QuickSlot2.iNum = 1;

	CUI::UIINFO QuickSlot3;
	QuickSlot3.fSizeX = 50.f;
	QuickSlot3.fSizeY = 50.f;
	QuickSlot3.fX = 405.f;
	QuickSlot3.fY = 580.f;
	QuickSlot3.iNum = 2;

	CUI::UIINFO QuickSlot4;
	QuickSlot4.fSizeX = 50.f;
	QuickSlot4.fSizeY = 50.f;
	QuickSlot4.fX = 420.f;
	QuickSlot4.fY = 635.f;
	QuickSlot4.iNum = 3;

	CUI::UIINFO QuickSlot5;
	QuickSlot5.fSizeX = 50.f;
	QuickSlot5.fSizeY = 50.f;
	QuickSlot5.fX = 460.f;
	QuickSlot5.fY = 580.f;
	QuickSlot5.iNum = 4;

	CUI::UIINFO QuickSlot6;
	QuickSlot6.fSizeX = 50.f;
	QuickSlot6.fSizeY = 50.f;
	QuickSlot6.fX = 475.f;
	QuickSlot6.fY = 635.f;
	QuickSlot6.iNum = 5;

	CUI::UIINFO QuickSlot7;
	QuickSlot7.fSizeX = 50.f;
	QuickSlot7.fSizeY = 50.f;
	QuickSlot7.fX = 515.f;
	QuickSlot7.fY = 580.f;
	QuickSlot7.iNum = 6;

	CUI::UIINFO QuickSlot8;
	QuickSlot8.fSizeX = 50.f;
	QuickSlot8.fSizeY = 50.f;
	QuickSlot8.fX = 530.f;
	QuickSlot8.fY = 635.f;
	QuickSlot8.iNum = 7;

	CUI::UIINFO QuickSlot9;
	QuickSlot9.fSizeX = 50.f;
	QuickSlot9.fSizeY = 50.f;
	QuickSlot9.fX = 735.f;
	QuickSlot9.fY = 580.f;
	QuickSlot9.iNum = 8;

	CUI::UIINFO QuickSlot10;
	QuickSlot10.fSizeX = 50.f;
	QuickSlot10.fSizeY = 50.f;
	QuickSlot10.fX = 750.f;
	QuickSlot10.fY = 635.f;
	QuickSlot10.iNum = 9;

	CUI::UIINFO QuickSlot11;
	QuickSlot11.fSizeX = 50.f;
	QuickSlot11.fSizeY = 50.f;
	QuickSlot11.fX = 790.f;
	QuickSlot11.fY = 580.f;
	QuickSlot11.iNum = 10;

	CUI::UIINFO QuickSlot12;
	QuickSlot12.fSizeX = 50.f;
	QuickSlot12.fSizeY = 50.f;
	QuickSlot12.fX = 805.f;
	QuickSlot12.fY = 635.f;
	QuickSlot12.iNum = 11;

	CUI::UIINFO QuickSlot13;
	QuickSlot13.fSizeX = 50.f;
	QuickSlot13.fSizeY = 50.f;
	QuickSlot13.fX = 845.f;
	QuickSlot13.fY = 580.f;
	QuickSlot13.iNum = 12;

	CUI::UIINFO QuickSlot14;
	QuickSlot14.fSizeX = 50.f;
	QuickSlot14.fSizeY = 50.f;
	QuickSlot14.fX = 860.f;
	QuickSlot14.fY = 635.f;
	QuickSlot14.iNum = 13;

	CUI::UIINFO QuickSlot15;
	QuickSlot15.fSizeX = 50.f;
	QuickSlot15.fSizeY = 50.f;
	QuickSlot15.fX = 900.f;
	QuickSlot15.fY = 580.f;
	QuickSlot15.iNum = 14;

	CUI::UIINFO QuickSlot16;
	QuickSlot16.fSizeX = 50.f;
	QuickSlot16.fSizeY = 50.f;
	QuickSlot16.fX = 915.f;
	QuickSlot16.fY = 635.f;
	QuickSlot16.iNum = 15;
	
	

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_STATIC, pLayerTag, &QuickSlot1)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_STATIC, pLayerTag, &QuickSlot2)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_STATIC, pLayerTag, &QuickSlot3)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_STATIC, pLayerTag, &QuickSlot4)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_STATIC, pLayerTag, &QuickSlot5)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_STATIC, pLayerTag, &QuickSlot6)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_STATIC, pLayerTag, &QuickSlot7)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_STATIC, pLayerTag, &QuickSlot8)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_STATIC, pLayerTag, &QuickSlot9)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_STATIC, pLayerTag, &QuickSlot10)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_STATIC, pLayerTag, &QuickSlot11)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_STATIC, pLayerTag, &QuickSlot12)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_STATIC, pLayerTag, &QuickSlot13)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_STATIC, pLayerTag, &QuickSlot14)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_STATIC, pLayerTag, &QuickSlot15)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_STATIC, pLayerTag, &QuickSlot16)))
		return E_FAIL;


	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_QuickSlotSkill(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CUI::UIINFO QuickSlotSkill1;
	QuickSlotSkill1.fSizeX = 40.f;
	QuickSlotSkill1.fSizeY = 40.f;
	QuickSlotSkill1.fX = 350.f;
	QuickSlotSkill1.fY = 580.f;
	QuickSlotSkill1.iNum = 0;

	CUI::UIINFO QuickSlotSkill2;
	QuickSlotSkill2.fSizeX = 40.f;
	QuickSlotSkill2.fSizeY = 40.f;
	QuickSlotSkill2.fX = 365.f;
	QuickSlotSkill2.fY = 635.f;
	QuickSlotSkill2.iNum = 1;

	CUI::UIINFO QuickSlotSkill3;
	QuickSlotSkill3.fSizeX = 40.f;
	QuickSlotSkill3.fSizeY = 40.f;
	QuickSlotSkill3.fX = 405.f;
	QuickSlotSkill3.fY = 580.f;
	QuickSlotSkill3.iNum = 2;

	CUI::UIINFO QuickSlotSkill4;
	QuickSlotSkill4.fSizeX = 40.f;
	QuickSlotSkill4.fSizeY = 40.f;
	QuickSlotSkill4.fX = 420.f;
	QuickSlotSkill4.fY = 635.f;
	QuickSlotSkill4.iNum = 3;

	CUI::UIINFO QuickSlotSkill5;
	QuickSlotSkill5.fSizeX = 40.f;
	QuickSlotSkill5.fSizeY = 40.f;
	QuickSlotSkill5.fX = 460.f;
	QuickSlotSkill5.fY = 580.f;
	QuickSlotSkill5.iNum = 4;

	CUI::UIINFO QuickSlotSkill6;
	QuickSlotSkill6.fSizeX = 40.f;
	QuickSlotSkill6.fSizeY = 40.f;
	QuickSlotSkill6.fX = 475.f;
	QuickSlotSkill6.fY = 635.f;
	QuickSlotSkill6.iNum = 5;

	CUI::UIINFO QuickSlotSkill7;
	QuickSlotSkill7.fSizeX = 40.f;
	QuickSlotSkill7.fSizeY = 40.f;
	QuickSlotSkill7.fX = 515.f;
	QuickSlotSkill7.fY = 580.f;
	QuickSlotSkill7.iNum = 6;

	CUI::UIINFO QuickSlotSkill8;
	QuickSlotSkill8.fSizeX = 40.f;
	QuickSlotSkill8.fSizeY = 40.f;
	QuickSlotSkill8.fX = 530.f;
	QuickSlotSkill8.fY = 635.f;
	QuickSlotSkill8.iNum = 7;

	CUI::UIINFO QuickSlotSkill9;
	QuickSlotSkill9.fSizeX = 40.f;
	QuickSlotSkill9.fSizeY = 40.f;
	QuickSlotSkill9.fX = 735.f;
	QuickSlotSkill9.fY = 580.f;
	QuickSlotSkill9.iNum = 8;
	
	CUI::UIINFO QuickSlotSkill10;
	QuickSlotSkill10.fSizeX = 40.f;
	QuickSlotSkill10.fSizeY = 40.f;
	QuickSlotSkill10.fX = 750.f;
	QuickSlotSkill10.fY = 635.f;
	QuickSlotSkill10.iNum = 9;

	CUI::UIINFO QuickSlotSkill11;
	QuickSlotSkill11.fSizeX = 40.f;
	QuickSlotSkill11.fSizeY = 40.f;
	QuickSlotSkill11.fX = 790.f;
	QuickSlotSkill11.fY = 580.f;
	QuickSlotSkill11.iNum = 10;
	
	CUI::UIINFO QuickSlotSkill12;
	QuickSlotSkill12.fSizeX = 40.f;
	QuickSlotSkill12.fSizeY = 40.f;
	QuickSlotSkill12.fX = 805.f;
	QuickSlotSkill12.fY = 635.f;
	QuickSlotSkill12.iNum = 11;

	CUI::UIINFO QuickSlotSkill13;
	QuickSlotSkill13.fSizeX = 40.f;
	QuickSlotSkill13.fSizeY = 40.f;
	QuickSlotSkill13.fX = 845.f;
	QuickSlotSkill13.fY = 580.f;
	QuickSlotSkill13.iNum = 12;

	CUI::UIINFO QuickSlotSkill14;
	QuickSlotSkill14.fSizeX = 40.f;
	QuickSlotSkill14.fSizeY = 40.f;
	QuickSlotSkill14.fX = 860.f;
	QuickSlotSkill14.fY = 635.f;
	QuickSlotSkill14.iNum = 13;

	CUI::UIINFO QuickSlotSkill15;
	QuickSlotSkill15.fSizeX = 40.f;
	QuickSlotSkill15.fSizeY = 40.f;
	QuickSlotSkill15.fX = 900.f;
	QuickSlotSkill15.fY = 580.f;
	QuickSlotSkill15.iNum = 14;

	CUI::UIINFO QuickSlotSkill16;
	QuickSlotSkill16.fSizeX = 40.f;
	QuickSlotSkill16.fSizeY = 40.f;
	QuickSlotSkill16.fX = 915.f;
	QuickSlotSkill16.fY = 635.f;
	QuickSlotSkill16.iNum = 15;

	


	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_STATIC, pLayerTag, &QuickSlotSkill1)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_STATIC, pLayerTag, &QuickSlotSkill2)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_STATIC, pLayerTag, &QuickSlotSkill3)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_STATIC, pLayerTag, &QuickSlotSkill4)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_STATIC, pLayerTag, &QuickSlotSkill5)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_STATIC, pLayerTag, &QuickSlotSkill6)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_STATIC, pLayerTag, &QuickSlotSkill7)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_STATIC, pLayerTag, &QuickSlotSkill8)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_STATIC, pLayerTag, &QuickSlotSkill9)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_STATIC, pLayerTag, &QuickSlotSkill10)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_STATIC, pLayerTag, &QuickSlotSkill11)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_STATIC, pLayerTag, &QuickSlotSkill12)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_STATIC, pLayerTag, &QuickSlotSkill13)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_STATIC, pLayerTag, &QuickSlotSkill14)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_STATIC, pLayerTag, &QuickSlotSkill15)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_STATIC, pLayerTag, &QuickSlotSkill16)))
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

	Safe_Release(m_pColliderCom);
}


