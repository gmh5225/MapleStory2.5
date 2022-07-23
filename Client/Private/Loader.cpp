#include "stdafx.h"
#include "..\Public\Loader.h"

#include "GameInstance.h"
#include "Camera_Free.h"
#include "BackGround.h"
#include "Terrain.h"
#include "Monster.h"
#include "Player.h"
#include "Cube.h"
#include "Wood.h"




CLoader::CLoader(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

_uint APIENTRY LoadingMain(void* pArg)
{
	CLoader*		pLoader = (CLoader*)pArg;

	EnterCriticalSection(&pLoader->Get_CS());

	switch (pLoader->Get_NextLevelID())
	{
	case LEVEL_LOGO:
		pLoader->Loading_ForLogoLevel();
		break;
	case LEVEL_GAMEPLAY:
		pLoader->Loading_ForGamePlayLevel();
		break;
	}

	LeaveCriticalSection(&pLoader->Get_CS());

	return 0;
}

HRESULT CLoader::Initialize(LEVEL eNextLevelID)
{
	m_eNextLevelID = eNextLevelID;

	InitializeCriticalSection(&m_CriticalSection);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, LoadingMain, this, 0, nullptr);

	if (0 == m_hThread)
		return E_FAIL;

	return S_OK;
}

HRESULT CLoader::Loading_ForLogoLevel()
{
	lstrcpy(m_szLoadingText, TEXT("객체원형을 로딩중입니다. "));

	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	/* 개ㅑㄱ체원형 로드한다. */	

	/* For.Prototype_GameObject_BackGround */ 
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BackGround"), CBackGround::Create(m_pGraphic_Device))))
		return E_FAIL;	

	lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로딩중입니다. "));
	/* 텍스쳐를 로드한다. */

	/* For.Prototype_Component_Texture_Default */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_LOGO, TEXT("Prototype_Component_Texture_Default"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Default%d.jpg"), 2))))
		return E_FAIL;


	lstrcpy(m_szLoadingText, TEXT("모델을 로딩중입니다. "));	
	/* 모델를 로드한다. */


	lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니ㅏㄷ.  "));

	Safe_Release(pGameInstance);

	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::Loading_ForGamePlayLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);






	lstrcpy(m_szLoadingText, TEXT("객체원형을 로딩중입니다. "));

	/* 개ㅑㄱ체원형 로드한다. */
	/* For.Prototype_GameObject_Terrain*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Terrain"), 
		CTerrain::Create(m_pGraphic_Device))))
		return E_FAIL;

	/* For.Prototype_GameObject_Player*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Player"),
		CPlayer::Create(m_pGraphic_Device))))
		return E_FAIL;

	/* For.Prototype_GameObject_Monster */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Monster"),
		CMonster::Create(m_pGraphic_Device))))
		return E_FAIL;

	/* For.Prototype_GameObject_Camera_Free */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Camera_Free"),
		CCamera_Free::Create(m_pGraphic_Device))))
		return E_FAIL;


	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Cube"),
		CCube::Create(m_pGraphic_Device))))
		return E_FAIL;


	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Wood"),
		CWood::Create(m_pGraphic_Device))))
		return E_FAIL;








	lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로딩중입니다. "));
	/* 텍스쳐를 로드한다. */
	/* For.Prototype_Component_Texture_Terrain */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Terrain"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Terrain/Grass_%d.tga"), 2))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Sky */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Sky"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBEMAP, TEXT("../Bin/Resources/Textures/SkyBox/Sky_%d.dds"), 1))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Player */
	Load_Player_Texture();





	lstrcpy(m_szLoadingText, TEXT("컴포넌트를 로딩중입니다. "));


	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Animator"),
		CAnimator::Create(m_pGraphic_Device))))
		return E_FAIL;







	lstrcpy(m_szLoadingText, TEXT("모델을 로딩중입니다. "));
	/* 모델를 로드한다. */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Terrain"),
		CVIBuffer_Terrain::Create(m_pGraphic_Device, 100, 100))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Cube"),
		CVIBuffer_Cube::Create(m_pGraphic_Device))))
		return E_FAIL;



	vector<tagVertexColor> tempTest;
	tempTest.push_back(tagVertexColor{ _float3{ 0.f, 0.f, 0.f }, D3DCOLOR_XRGB(111, 79, 40) });
	tempTest.push_back(tagVertexColor{ _float3{ 0.f, 1.f, 0.f }, D3DCOLOR_XRGB(111, 79, 40) });
	tempTest.push_back(tagVertexColor{ _float3{ 0.f, 2.f, 0.f }, D3DCOLOR_XRGB(111, 79, 40) });
	tempTest.push_back(tagVertexColor{ _float3{ 0.f, 3.f, 0.f }, D3DCOLOR_XRGB(111, 79, 40) });

	tempTest.push_back(tagVertexColor{ _float3{ 1.f, 3.f, 0.f }, D3DCOLOR_XRGB(0, 255, 0) });
	tempTest.push_back(tagVertexColor{ _float3{ -1.f, 3.f, 0.f }, D3DCOLOR_XRGB(0, 255, 0) });
	tempTest.push_back(tagVertexColor{ _float3{ 0.f, 3.f, -1.f }, D3DCOLOR_XRGB(0, 255, 0) });
	tempTest.push_back(tagVertexColor{ _float3{ 0.f, 3.f, 1.f }, D3DCOLOR_XRGB(0, 255, 0) });
	tempTest.push_back(tagVertexColor{ _float3{ 0.f, 4.f, 0.f }, D3DCOLOR_XRGB(0, 255, 0) });


	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Tree"),
		CVIBuffer_Voxel::Create(m_pGraphic_Device, &tempTest))))
		return E_FAIL;







	lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니ㅏㄷ.  "));

	Safe_Release(pGameInstance);

	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::Load_Player_Texture()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);
	// Attack 12
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack_D"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Attack/G_Attack_D/Edit/Attack_D%d.png"), 12))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack_L"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Attack/G_Attack_L/Edit/Attack_L%d.png"), 13))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack_LD"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Attack/G_Attack_LD/Edit/Attack_LD%d.png"), 14))))
		return E_FAIL;

	/*if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack_LU"),
	CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Attack/G_Attack_LU/Edit/Attack_LU%d.png"), 12))))
	return E_FAIL;*/



	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack_R"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Attack/G_Attack_R/Edit/Attack_R%d.png"), 11))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack_RD"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Attack/G_Attack_RD/Edit/Attack_RD%d.png"), 13))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack_RU"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Attack/G_Attack_RU/Edit/Attack_RU%d.png"), 13))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Attack_U"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Attack/G_Attack_U/Edit/Attack_U%d.png"), 12))))
		return E_FAIL;

	//Idle

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_D"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Idle/G_Idle_D/Edit/Idle_D%d.png"), 35))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_L"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Idle/G_Idle_L/Edit/Idle_L%d.png"), 34))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_LD"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Idle/G_Idle_LD/Edit/Idle_LD%d.png"), 35))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_LU"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Idle/G_Idle_LU/Edit/Idle_LU%d.png"), 36))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_R"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Idle/G_Idle_R/Edit/Idle_R%d.png"), 36))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_RD"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Idle/G_Idle_RD/Edit/Idle_RD%d.png"), 33))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_RU"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Idle/G_Idle_RU/Edit/Idle_RU%d.png"), 35))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Idle_U"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Idle/G_Idle_U/Edit/Idle_U%d.png"), 35))))
		return E_FAIL;

	//Move

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_D"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Move/G_Move_D/Edit/Move_D%d.png"), 10))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_L"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Move/G_Move_L/Edit/Move_L%d.png"), 8))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_LD"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Move/G_Move_LD/Edit/Move_LD%d.png"), 9))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_LU"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Move/G_Move_LU/Edit/Move_LU%d.png"), 8))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_R"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Move/G_Move_R/Edit/Move_R%d.png"), 9))))
		return E_FAIL;

	/*if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_RD"),
	CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Move/G_Move_RD/Edit/MoveRD%d.png"), 33))))
	return E_FAIL;*/

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_RU"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Move/G_Move_RU/Edit/Move_RU%d.png"), 10))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Move_U"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Move/G_Move_U/Edit/Move_U%d.png"), 10))))
		return E_FAIL;

	//Jump

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Jump_D"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Jump/G_Jump_D/Edit/Jump_D%d.png"), 18))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Jump_L"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Jump/G_Jump_L/Edit/Jump_L%d.png"), 16))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Jump_LD"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Jump/G_Jump_LD/Edit/Jump_LD%d.png"), 17))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Jump_LU"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Jump/G_Jump_LU/Edit/Jump_LU%d.png"), 16))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Jump_R"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Jump/G_Jump_R/Edit/Jump_R%d.png"), 17))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Jump_RD"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Jump/G_Jump_RD/Edit/Jump_RD%d.png"), 17))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Jump_RU"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Jump/G_Jump_RU/Edit/Jump_RU%d.png"), 18))))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Player_Jump_U"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Player/Jump/G_Jump_U/Edit/Jump_U%d.png"), 17))))
		return E_FAIL;


	Safe_Release(pGameInstance);

	return S_OK;
}

CLoader * CLoader::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevelID)
{
	CLoader*		pInstance = new CLoader(pGraphic_Device);

	if (FAILED(pInstance->Initialize(eNextLevelID)))
	{
		MSG_BOX(TEXT("Failed To Created : CLoader"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLoader::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);

	DeleteCriticalSection(&m_CriticalSection);

	CloseHandle(m_hThread);

	Safe_Release(m_pGraphic_Device);


}
