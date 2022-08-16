#include "stdafx.h"
#include "..\Public\Level_Elenya.h"

#include "GameInstance.h"
#include "Camera_Free.h"
#include "SkillInfo.h"
#include "SunCrossInfo.h"
#include "SolunaSlashInfo.h"
#include "SkillManager.h"
#include "UI.h"
#include "QuestManager.h"
#include "SpawnerManager.h"
#include "Maya.h"
#include "Level_Loading.h"
#include "Potal.h"
#include "CutSceneManager.h"
#include "Bandit.h"
#include "UIManager.h"
#include "Sky.h"

CLevel_Elenya::CLevel_Elenya(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel(pGraphic_Device)
{
}

HRESULT CLevel_Elenya::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;



	//if (FAILED(Ready_SkillInfo()))
	//	return E_FAIL;

	if (FAILED(Ready_Layer_Map(TEXT("Layer_Map"))))
		return E_FAIL;
	/*
	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Player(TEXT("Layer_Player"))))
		return E_FAIL;*/

	if (FAILED(Ready_Layer_Monster(TEXT("Layer_Monster"))))
		return E_FAIL;

	//if (FAILED(Ready_Layer_Npc(TEXT("Layer_Npc"))))
	//	return E_FAIL;

	////if (FAILED(Ready_Layer_UI(TEXT("Layer_UI"))))
	////	return E_FAIL;

	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
		return E_FAIL;

	//if (FAILED(Ready_Layer_Spawner(TEXT("Layer_Spawner"))))
	//	return E_FAIL;

	CGameInstance::Get_Instance()->StopAll();
	CGameInstance::Get_Instance()->PlayBGM(L"MissingYou.mp3", 1.f);

	CUIManager::Get_Instance()->End_Loading();
	CUIManager::Get_Instance()->PlayTitleCurMap(LEVEL_ELENYA);
	CCutSceneManager::Get_Instance()->Start_Enter_Elenya();
	
	return S_OK;
}

void CLevel_Elenya::Tick(_float fTimeDelta)
{
	if (CQuestManager::Get_Instance()->Set_OrangeMushroom() >= 10)
		CQuestManager::Get_Instance()->QuestClear();
	__super::Tick(fTimeDelta);

	if (GetKeyState('N') & 0x8000)
	{
		CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);

		m_pColliderCom->ResetSection();
		if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_GAMEPLAY))))
			return;

		
		Safe_Release(pGameInstance);

	}

}

HRESULT CLevel_Elenya::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("���� ����� ������"));

	return S_OK;
}

HRESULT CLevel_Elenya::Ready_Layer_Camera(const _tchar * pLayerTag)
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

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Camera_Free"), LEVEL_HENESYS, pLayerTag, &CameraDesc)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Elenya::Ready_Layer_Player(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Player"), LEVEL_GAMEPLAY, pLayerTag)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Elenya::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Terrain"), LEVEL_GAMEPLAY, pLayerTag)))
	//	return E_FAIL;

	CSky::SKYDESC SkyDesc;
	SkyDesc.iIndex = 6;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Sky"), LEVEL_GAMEPLAY, pLayerTag, &SkyDesc)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Elenya::Ready_Layer_Monster(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);



	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_KingSlime"), LEVEL_ELENYA, pLayerTag)))
		return E_FAIL;

	Safe_Release(pGameInstance);


	return S_OK;
}

HRESULT CLevel_Elenya::Ready_Layer_Npc(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);


	Safe_Release(pGameInstance);


	return S_OK;
}

HRESULT CLevel_Elenya::Ready_Layer_Map(const _tchar * pLayerTag)
{


	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CCreature::CRETUREDESC HarpInfo0;
	HarpInfo0.vPos = _float3(12.f, 20.f, 15.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Harp"), LEVEL_ELENYA, pLayerTag, &HarpInfo0)))
		return E_FAIL;
	//
	CCreature::CRETUREDESC SlimeStoneInfo0;
	SlimeStoneInfo0.vPos = _float3(20.5f, 28.9f, 6.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SlimeStone"), LEVEL_ELENYA, pLayerTag, &SlimeStoneInfo0)))
		return E_FAIL;
	CCreature::CRETUREDESC SlimeStoneInfo1;
	SlimeStoneInfo1.vPos = _float3(26.f, 28.9f, 12.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SlimeStone"), LEVEL_ELENYA, pLayerTag, &SlimeStoneInfo1)))
		return E_FAIL;
	CCreature::CRETUREDESC SlimeStoneInfo2;
	SlimeStoneInfo2.vPos = _float3(33.f, 28.9f, 6.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SlimeStone"), LEVEL_ELENYA, pLayerTag, &SlimeStoneInfo2)))
		return E_FAIL;
	CCreature::CRETUREDESC SlimeStoneInfo3;
	SlimeStoneInfo3.vPos = _float3(26.f, 28.9f, 1.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SlimeStone"), LEVEL_ELENYA, pLayerTag, &SlimeStoneInfo3)))
		return E_FAIL;
	//
	CCreature::CRETUREDESC GrassInfo0;
	GrassInfo0.vPos = _float3(1.f, 0.78f, 1.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Grass"), LEVEL_ELENYA, pLayerTag, &GrassInfo0)))
		return E_FAIL;
	CCreature::CRETUREDESC VineInfo0;
	VineInfo0.vPos = _float3(-2.f, 1.2f, 3.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Vine"), LEVEL_ELENYA, pLayerTag, &VineInfo0)))
		return E_FAIL;
	CCreature::CRETUREDESC WeedInfo7;
	WeedInfo7.vPos = _float3(-1.7f, 0.68f, 2.2f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Weed"), LEVEL_ELENYA, pLayerTag, &WeedInfo7)))
		return E_FAIL;
	CCreature::CRETUREDESC VineInfo1;
	VineInfo1.vPos = _float3(19.f, 15.2f, 7.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Vine"), LEVEL_ELENYA, pLayerTag, &VineInfo1)))
		return E_FAIL;

	CCreature::CRETUREDESC VineInfo2;
	VineInfo2.vPos = _float3(0.f, 13.2f, 14.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Vine"), LEVEL_ELENYA, pLayerTag, &VineInfo2)))
		return E_FAIL;

	CCreature::CRETUREDESC WeedInfo9;
	WeedInfo9.vPos = _float3(0.2f, 12.68f, 13.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Weed"), LEVEL_ELENYA, pLayerTag, &WeedInfo9)))
		return E_FAIL;
	//CCreature::CRETUREDESC GrassInfo1;
	//GrassInfo1.vPos = _float3(-2.f, 0.78f, 3.f);
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Grass"), LEVEL_GAMEPLAY, pLayerTag, &GrassInfo1)))
//		return E_FAIL;


	CCreature::CRETUREDESC GrassInfo2;
	GrassInfo2.vPos = _float3(-4.f, 0.78f, 0.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Grass"), LEVEL_ELENYA, pLayerTag, &GrassInfo2)))
		return E_FAIL;

	CCreature::CRETUREDESC GrassInfo3;
	GrassInfo3.vPos = _float3(1.f, 0.78f, -3.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Grass"), LEVEL_ELENYA, pLayerTag, &GrassInfo3)))
		return E_FAIL;

	CCreature::CRETUREDESC GrassInfo4;
	GrassInfo4.vPos = _float3(5.f, 4.78f, -5.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Grass"), LEVEL_ELENYA, pLayerTag, &GrassInfo4)))
		return E_FAIL;
	CCreature::CRETUREDESC GrassInfo5;
	GrassInfo5.vPos = _float3(-2.f, 12.78f, 12.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Grass"), LEVEL_ELENYA, pLayerTag, &GrassInfo5)))
		return E_FAIL;
	//
	CCreature::CRETUREDESC GrassInfo6;
	GrassInfo6.vPos = _float3(8.f, 19.78f, 19.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Grass"), LEVEL_ELENYA, pLayerTag, &GrassInfo6)))
		return E_FAIL;


	CCreature::CRETUREDESC GrassInfo8;
	GrassInfo8.vPos = _float3(9.f, 19.78f, 10.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Grass"), LEVEL_ELENYA, pLayerTag, &GrassInfo8)))
		return E_FAIL;
	CCreature::CRETUREDESC GrassInfo9;
	GrassInfo9.vPos = _float3(4.f, 19.78f, 16.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Grass"), LEVEL_ELENYA, pLayerTag, &GrassInfo9)))
		return E_FAIL;
	//
	CCreature::CRETUREDESC WeedInfo0;
	WeedInfo0.vPos = _float3(1.4f, 2.68f, -2.8f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Weed"), LEVEL_ELENYA, pLayerTag, &WeedInfo0)))
		return E_FAIL;
	CCreature::CRETUREDESC WeedInfo1;
	WeedInfo1.vPos = _float3(-1.f, 0.68f, -4.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Weed"), LEVEL_ELENYA, pLayerTag, &WeedInfo1)))
		return E_FAIL;

	CCreature::CRETUREDESC WeedInfo2;
	WeedInfo2.vPos = _float3(-3.8f, 0.68f, 0.7f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Weed"), LEVEL_ELENYA, pLayerTag, &WeedInfo2)))
		return E_FAIL;
	CCreature::CRETUREDESC WeedInfo3;
	WeedInfo3.vPos = _float3(4.f, 8.68f, 1.5f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Weed"), LEVEL_ELENYA, pLayerTag, &WeedInfo3)))
		return E_FAIL;
	CCreature::CRETUREDESC WeedInfo4;
	WeedInfo4.vPos = _float3(10.f, 8.68f, 2.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Weed"), LEVEL_ELENYA, pLayerTag, &WeedInfo4)))
		return E_FAIL;
	CCreature::CRETUREDESC WeedInfo5;
	WeedInfo5.vPos = _float3(4.f, 8.68f, -3.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Weed"), LEVEL_ELENYA, pLayerTag, &WeedInfo5)))
		return E_FAIL;
	CCreature::CRETUREDESC WeedInfo6;
	WeedInfo6.vPos = _float3(7.f, 8.68f, 3.5f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Weed"), LEVEL_ELENYA, pLayerTag, &WeedInfo6)))
		return E_FAIL;


	CCreature::CRETUREDESC WeedInfo8;
	WeedInfo8.vPos = _float3(12.7f, 19.68f, 14.5f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Weed"), LEVEL_ELENYA, pLayerTag, &WeedInfo8)))
		return E_FAIL;

	
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_RockEnter"), LEVEL_ELENYA, pLayerTag)))
		return E_FAIL;

	CPotal::POTALDESC PotalDesc;
	PotalDesc.eDestLevel = LEVEL_ELENYAENTER;
	PotalDesc.Pos =  _float3(-1.f, 1.f, 0.f);
	PotalDesc.DestPos = _float3(51.f, 17.f, -2.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Potal"), LEVEL_ELENYA, pLayerTag, &PotalDesc)))
		return E_FAIL;

	PotalDesc.eDestLevel = LEVEL_GAS;
	PotalDesc.Pos = _float3(27.f, 29.f, 6.f);
	PotalDesc.DestPos = _float3(0.f, 1.f, -2.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Potal"), LEVEL_ELENYA, pLayerTag, &PotalDesc)))
		return E_FAIL;




	/* �� ť�� �߰� > ���� ���� > �ݸ��� �Ŵ��� ������Ʈ ����Լ� ȣ��� ���ǿ� ť�� ä���*/

	list<CMap_Manager::CUBEDATA>* pMapData = pGameInstance->ReadMap(L"Map_Elenya");
	for (auto& Data : *pMapData)
	{
		if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Cube"), LEVEL_ELENYA, pLayerTag, &Data)))
			return E_FAIL;
	}


	list<CMap_Manager::MODELDESC>* pModelData = pGameInstance->ReadModel(L"Total_Elenya");
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

			if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Wood"), LEVEL_ELENYA, pLayerTag, &VoxDesc)))
				return E_FAIL;
		}

	}





	for (_int i = 0; i < 50; i++)
	{
		_float fScale = pGameInstance->Get_FloatRandom(0.5f, 1.5f);
		_float fTime = pGameInstance->Get_FloatRandom(0.1f, 0.3f);

		_float x = pGameInstance->Get_FloatRandom(-10.f, 20.f);
		_float y = pGameInstance->Get_FloatRandom(1.f, 60.f);
		_float z = pGameInstance->Get_FloatRandom(-5.f, 10.f);


		_float3 vPos = { x, y , z };

		CBandit::BANDITDESC BanditDesc;
		BanditDesc.vPos = vPos;
		BanditDesc.fScale = fScale;
		BanditDesc.fTime = fTime;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Bandit"), LEVEL_ELENYA, pLayerTag, &BanditDesc)))
			return E_FAIL;
	}





	Safe_Release(pGameInstance);

	if (FAILED(Ready_Layer_Section(TEXT("Layer_Section"))))
		return E_FAIL;

	return S_OK;

}

HRESULT CLevel_Elenya::Ready_Layer_Section(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	CComponent*			pComponent = pGameInstance->Clone_Component(LEVEL_STATIC, TEXT("Prototype_Component_Collider"));
	if (nullptr == pComponent)
		return E_FAIL;
	m_pColliderCom = (CCollider*)pComponent;


	CMap_Manager::CUBEDATA Data;
	ZeroMemory(&Data, sizeof(CMap_Manager::CUBEDATA));

	for (int y = 0; y < 6; y++)
	{
		for (int j = -5; j < 10; j++)
		{
			for (int i = -5; i < 10; i++)
			{
				_float XIndex = i*5.f;
				_float ZIndex = j*5.f;
				Data.vPos = _float3((-16.f + XIndex) + ZIndex, 2.f + y * 9.f, 7 - XIndex);
				if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Section"), LEVEL_ELENYA, pLayerTag, &Data)))
					return E_FAIL;
			}
		}
	}



	Safe_Release(pGameInstance);


	m_pColliderCom->Set_SectionCubes();

	return S_OK;
}

HRESULT CLevel_Elenya::Ready_Layer_UI(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);


	CUI::UIINFO SkillFrameiInfo;
	SkillFrameiInfo.fSizeX = 318.f;
	SkillFrameiInfo.fSizeY = 360.f;
	SkillFrameiInfo.fX = 900.f;
	SkillFrameiInfo.fY = 300.f;


	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuestUI"), LEVEL_HENESYS, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Chat"), LEVEL_HENESYS, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillFrame"), LEVEL_HENESYS, pLayerTag, &SkillFrameiInfo)))
		return E_FAIL;

	Ready_SkillFrameBtn(pLayerTag);

	Ready_SkillIcon(pLayerTag);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_HpBarBase"), LEVEL_HENESYS, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_HpBarHp"), LEVEL_HENESYS, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_HpBarMp"), LEVEL_HENESYS, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_HpBarIcon"), LEVEL_HENESYS, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_ExpBase"), LEVEL_HENESYS, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_ExpBar"), LEVEL_HENESYS, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_ExpLine"), LEVEL_HENESYS, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_MenuIcon"), LEVEL_HENESYS, pLayerTag)))
		return E_FAIL;

	Ready_QuickSlot(pLayerTag);

	Ready_QuickSlotSkill(pLayerTag);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_MouseSkillIcon"), LEVEL_HENESYS, pLayerTag)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_MouseCursor"), LEVEL_HENESYS, pLayerTag)))
		return E_FAIL;

	Safe_Release(pGameInstance);


	return S_OK;
}

HRESULT CLevel_Elenya::Ready_Layer_Spawner(const _tchar * pLayerTag)
{
	CSpawner::SPAWNERINFO MonsterInfo;
	MonsterInfo.MonsterName = TEXT("GoStump");
	MonsterInfo.MonsterPos = _float3{ 4.5f , 9.0f, 0.f };
	MonsterInfo.SpawnerNum = 30;
	MonsterInfo.MonsterNum = 2;
	MonsterInfo.MonsterColRad = 1.f;
	MonsterInfo.Level = LEVEL_ELENYA;
	MonsterInfo.LayerTag = TEXT("Layer_Spawner_Elenya");
	CSpawnerManager::Get_Instance()->Add_Spawner(&MonsterInfo);

	CSpawner::SPAWNERINFO MonsterInfo1;
	MonsterInfo1.MonsterName = TEXT("GoStump");
	MonsterInfo1.MonsterPos = _float3{ 8.5f , 10.0f, 0.f };
	MonsterInfo1.SpawnerNum = 31;
	MonsterInfo1.MonsterNum = 2;
	MonsterInfo1.MonsterColRad = 1.f;
	MonsterInfo1.Level = LEVEL_ELENYA;
	MonsterInfo1.LayerTag = TEXT("Layer_Spawner_Elenya");
	CSpawnerManager::Get_Instance()->Add_Spawner(&MonsterInfo1);

	CSpawner::SPAWNERINFO MonsterInfo2;
	MonsterInfo2.MonsterName = TEXT("GoStump");
	MonsterInfo2.MonsterPos = _float3{ 1.f , 13.f, 11.f };
	MonsterInfo2.SpawnerNum = 32;
	MonsterInfo2.MonsterNum = 2;
	MonsterInfo2.MonsterColRad = 1.f;
	MonsterInfo2.Level = LEVEL_ELENYA;
	MonsterInfo2.LayerTag = TEXT("Layer_Spawner_Elenya");
	CSpawnerManager::Get_Instance()->Add_Spawner(&MonsterInfo2);

	CSpawner::SPAWNERINFO MonsterInfo3;
	MonsterInfo3.MonsterName = TEXT("Slime");
	MonsterInfo3.MonsterPos = _float3{ 0.f , 13.f, 11.f };
	MonsterInfo3.SpawnerNum = 33;
	MonsterInfo3.MonsterNum = 2;
	MonsterInfo3.MonsterColRad = 1.f;
	MonsterInfo3.Level = LEVEL_ELENYA;
	MonsterInfo3.LayerTag = TEXT("Layer_Spawner_Elenya");
	CSpawnerManager::Get_Instance()->Add_Spawner(&MonsterInfo3);

	CSpawner::SPAWNERINFO MonsterInfo4;
	MonsterInfo4.MonsterName = TEXT("Slime");
	MonsterInfo4.MonsterPos = _float3{ 6.f , 22.f, 13.f };
	MonsterInfo4.SpawnerNum = 34;
	MonsterInfo4.MonsterNum = 2;
	MonsterInfo4.MonsterColRad = 1.f;
	MonsterInfo4.Level = LEVEL_ELENYA;
	MonsterInfo4.LayerTag = TEXT("Layer_Spawner_Elenya");
	CSpawnerManager::Get_Instance()->Add_Spawner(&MonsterInfo4);

	CSpawner::SPAWNERINFO MonsterInfo5;
	MonsterInfo5.MonsterName = TEXT("GreenMushroom");
	MonsterInfo5.MonsterPos = _float3{ 10.f , 22.f, 13.f };
	MonsterInfo5.SpawnerNum = 35;
	MonsterInfo5.MonsterNum = 2;
	MonsterInfo5.MonsterColRad = 1.f;
	MonsterInfo5.Level = LEVEL_ELENYA;
	MonsterInfo5.LayerTag = TEXT("Layer_Spawner_Elenya");
	CSpawnerManager::Get_Instance()->Add_Spawner(&MonsterInfo5);

	//CSpawner::SPAWNERINFO MonsterInfo6;
	//MonsterInfo6.MonsterName = TEXT("GreenMushroom");
	//MonsterInfo6.MonsterPos = _float3{ 20.f , 16.f, 4.f };
	//MonsterInfo6.SpawnerNum = 36;
	//MonsterInfo6.MonsterNum = 2;
	//MonsterInfo6.MonsterColRad = 1.f;
	//MonsterInfo6.Level = LEVEL_ELENYA;
	//MonsterInfo6.LayerTag = TEXT("Layer_Spawner_Elenya");
	//CSpawnerManager::Get_Instance()->Add_Spawner(&MonsterInfo6);

	return S_OK;
}

HRESULT CLevel_Elenya::Ready_SkillFrameBtn(const _tchar * pLayerTag)
{
	//��ųUp Btn ���� ���� 144px ���� 40px
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

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillUpBtn"), LEVEL_HENESYS, pLayerTag, &SkillUpBtnInfo1)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillUpBtn"), LEVEL_HENESYS, pLayerTag, &SkillUpBtnInfo2)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillUpBtn"), LEVEL_HENESYS, pLayerTag, &SkillUpBtnInfo3)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillUpBtn"), LEVEL_HENESYS, pLayerTag, &SkillUpBtnInfo4)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillUpBtn"), LEVEL_HENESYS, pLayerTag, &SkillUpBtnInfo5)))
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

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn0"), LEVEL_HENESYS, pLayerTag, &SkillGradeBtnInfo0)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn1"), LEVEL_HENESYS, pLayerTag, &SkillGradeBtnInfo1)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn2"), LEVEL_HENESYS, pLayerTag, &SkillGradeBtnInfo2)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn3"), LEVEL_HENESYS, pLayerTag, &SkillGradeBtnInfo3)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn4"), LEVEL_HENESYS, pLayerTag, &SkillGradeBtnInfo4)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SkillGradeBtn5"), LEVEL_HENESYS, pLayerTag, &SkillGradeBtnInfo5)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Elenya::Ready_SkillIcon(const _tchar * pLayerTag)
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

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SunCrossIcon"), LEVEL_HENESYS, pLayerTag, &SunCrossInfo)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_SolunaSlashIcon"), LEVEL_HENESYS, pLayerTag, &SolunaSlashInfo)))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Elenya::Ready_SkillInfo()
{
	//CSkillManager* pSkillInstance = CSkillManager::Get_Instance();
	//CSunCrossInfo* pSunCross = new CSunCrossInfo;
	//CSolunaSlashInfo* pSolunaSlash = new CSolunaSlashInfo;

	//if (FAILED(pSkillInstance->Add_SkillInfo(TEXT("SunCrossInfo"), CSkillManager::GRADE_BEGENNER, pSunCross)))
	//	return E_FAIL;

	//if (FAILED(pSkillInstance->Add_SkillInfo(TEXT("SolunaSlashInfo"), CSkillManager::GRADE_BEGENNER, pSolunaSlash)))
	//	return E_FAIL;

	return S_OK;


}

HRESULT CLevel_Elenya::Ready_QuickSlot(const _tchar* pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	//Ʋ����x 15 x���� 5 y���� 5

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



	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_HENESYS, pLayerTag, &QuickSlot1)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_HENESYS, pLayerTag, &QuickSlot2)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_HENESYS, pLayerTag, &QuickSlot3)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_HENESYS, pLayerTag, &QuickSlot4)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_HENESYS, pLayerTag, &QuickSlot5)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_HENESYS, pLayerTag, &QuickSlot6)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_HENESYS, pLayerTag, &QuickSlot7)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_HENESYS, pLayerTag, &QuickSlot8)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_HENESYS, pLayerTag, &QuickSlot9)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_HENESYS, pLayerTag, &QuickSlot10)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_HENESYS, pLayerTag, &QuickSlot11)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_HENESYS, pLayerTag, &QuickSlot12)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_HENESYS, pLayerTag, &QuickSlot13)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_HENESYS, pLayerTag, &QuickSlot14)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_HENESYS, pLayerTag, &QuickSlot15)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlot"), LEVEL_HENESYS, pLayerTag, &QuickSlot16)))
		return E_FAIL;


	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_Elenya::Ready_QuickSlotSkill(const _tchar * pLayerTag)
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
	QuickSlotSkill1.iNum = 1;

	CUI::UIINFO QuickSlotSkill3;
	QuickSlotSkill3.fSizeX = 40.f;
	QuickSlotSkill3.fSizeY = 40.f;
	QuickSlotSkill3.fX = 405.f;
	QuickSlotSkill3.fY = 580.f;
	QuickSlotSkill1.iNum = 2;

	CUI::UIINFO QuickSlotSkill4;
	QuickSlotSkill4.fSizeX = 40.f;
	QuickSlotSkill4.fSizeY = 40.f;
	QuickSlotSkill4.fX = 420.f;
	QuickSlotSkill4.fY = 635.f;
	QuickSlotSkill1.iNum = 3;

	CUI::UIINFO QuickSlotSkill5;
	QuickSlotSkill5.fSizeX = 40.f;
	QuickSlotSkill5.fSizeY = 40.f;
	QuickSlotSkill5.fX = 460.f;
	QuickSlotSkill5.fY = 580.f;
	QuickSlotSkill1.iNum = 4;

	CUI::UIINFO QuickSlotSkill6;
	QuickSlotSkill6.fSizeX = 40.f;
	QuickSlotSkill6.fSizeY = 40.f;
	QuickSlotSkill6.fX = 475.f;
	QuickSlotSkill6.fY = 635.f;
	QuickSlotSkill1.iNum = 5;

	CUI::UIINFO QuickSlotSkill7;
	QuickSlotSkill7.fSizeX = 40.f;
	QuickSlotSkill7.fSizeY = 40.f;
	QuickSlotSkill7.fX = 515.f;
	QuickSlotSkill7.fY = 580.f;
	QuickSlotSkill1.iNum = 6;

	CUI::UIINFO QuickSlotSkill8;
	QuickSlotSkill8.fSizeX = 40.f;
	QuickSlotSkill8.fSizeY = 40.f;
	QuickSlotSkill8.fX = 530.f;
	QuickSlotSkill8.fY = 635.f;
	QuickSlotSkill1.iNum = 7;


	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_HENESYS, pLayerTag, &QuickSlotSkill1)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_HENESYS, pLayerTag, &QuickSlotSkill2)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_HENESYS, pLayerTag, &QuickSlotSkill3)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_HENESYS, pLayerTag, &QuickSlotSkill4)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_HENESYS, pLayerTag, &QuickSlotSkill5)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_HENESYS, pLayerTag, &QuickSlotSkill6)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_HENESYS, pLayerTag, &QuickSlotSkill7)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_QuickSlotSkill"), LEVEL_HENESYS, pLayerTag, &QuickSlotSkill8)))
		return E_FAIL;

	Safe_Release(pGameInstance);
	return S_OK;
}

CLevel_Elenya * CLevel_Elenya::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_Elenya*		pInstance = new CLevel_Elenya(pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX(TEXT("Failed To Created : CLevel_Henesys_1"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Elenya::Free()
{
	__super::Free();

	Safe_Release(m_pColliderCom);
}


