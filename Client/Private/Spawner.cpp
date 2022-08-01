#include "stdafx.h"
#include "..\Public\Spawner.h"
#include "GameInstance.h"
#include "SpawnerManager.h"

CSpawner::CSpawner(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
	//ZeroMemory(&m_SpawnerInfo, sizeof(m_SpawnerInfo));

}

CSpawner::CSpawner(const CSpawner & rhs)
	: CGameObject(rhs)
{
}

HRESULT CSpawner::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CSpawner::Initialize(void * pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_fCount = 0;

	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	m_SpawnerInfo = *(CSpawner::SPAWNERINFO*)pArg;

	m_iOrangeMushroom = m_SpawnerInfo.MonsterNum;

	// monsternum값 만큼 생성시키면됨
	for (int i = 0; i < m_SpawnerInfo.MonsterNum; ++i)
	{
		m_SpawnerInfo.MonsterPos -= _float3{ _float(i) * 0.3f, 0.f, 0.f };


		if(FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_OrangeMushroom"), LEVEL_GAMEPLAY, TEXT("Layer_Monster"), pArg)))
			return E_FAIL;
 	}

	CSpawnerManager::Get_Instance()->Add_SpawnerInfo(this);

	Set_Index(m_SpawnerInfo.SpawnerNum);


	Safe_Release(pGameInstance);


	int i = m_SpawnerInfo.MonsterNum;

	return S_OK;
}

void CSpawner::Tick(_float fTimeDelta)
{

}

void CSpawner::LateTick(_float fTimeDelta)
{
	m_fCount += 1.f * fTimeDelta;



	if (m_SpawnerInfo.MonsterNum > m_iOrangeMushroom)
	{
		CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);

		int Num = m_SpawnerInfo.MonsterNum - m_iOrangeMushroom;

		if (5.f < m_fCount)
		{
			m_fCount = 0;

			for (int i = 0; i < Num; ++i)
			{
				_float Random = pGameInstance->Get_Random(0, 4);
				if(Random == 1)
					m_SpawnerInfo.MonsterPos += { 0.3f, 0.f, 0.5f};
				else if(Random == 2)
					m_SpawnerInfo.MonsterPos += {-0.3f, 0.f, 0.5f};
				else if (Random == 3)
					m_SpawnerInfo.MonsterPos += { 0.3f, 0.f, -0.5f};
				else if (Random == 4)
					m_SpawnerInfo.MonsterPos += {-0.3f, 0.f, -0.5f};

				if (FAILED(pGameInstance->Add_GameObjectToLayer(TEXT("Prototype_GameObject_OrangeMushroom"), LEVEL_GAMEPLAY, TEXT("Layer_Monster"), &m_SpawnerInfo)))
					int a = 0;
				Plus_Mushroom();
			}
			Num = 0;
		}

		
		Safe_Release(pGameInstance);
	}

}

HRESULT CSpawner::Render()
{


	return S_OK;
}

HRESULT CSpawner::SetUp_Components()
{

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), TEXT("Com_VIBuffer"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(TransformDesc));

	TransformDesc.fSpeedPerSec = 5.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"), TEXT("Com_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;




	
	return S_OK;
}


CSpawner * CSpawner::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSpawner*		pInstance = new CSpawner(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CSpawner"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CSpawner::Clone(void* pArg)
{
	CSpawner*		pInstance = new CSpawner(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Created : CSpawner clone"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSpawner::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}

