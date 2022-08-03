#include "stdafx.h"
#include "..\Public\Level_Static.h"
#include "GameInstance.h"
#include "Level_Loading.h"


CLevel_Static::CLevel_Static(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel(pGraphic_Device)
{
}


HRESULT CLevel_Static::Initialize()
{
	
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	

	Safe_Release(pGameInstance);

	return S_OK;
	
}

void CLevel_Static::Tick(_float fTimeDelta)
{

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);

		if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_GAMEPLAY))))
			return;

		Safe_Release(pGameInstance);

	}

}

CLevel_Static * CLevel_Static::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_Static*		pInstance = new CLevel_Static(pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX(TEXT("Failed To Created : CLevel_Static"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Static::Free()
{
	__super::Free();
}
