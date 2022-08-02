#include "..\Public\Collider.h"

#include "GameObject.h"
#include "Transform.h"
#include "BoxCollider.h"

CCollider::CCollider(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
}
HRESULT CCollider::Initialize_Prototype()
{
	return S_OK;
}
HRESULT CCollider::Initialize(void * pArg)
{
	return S_OK;
}

HRESULT CCollider::Add_SphereCollsionGroup(COLLSIONGROUP eCollsionGroup, CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	m_SphereCollisionObjects[eCollsionGroup].push_back(pGameObject);

	Safe_AddRef(pGameObject);

	return S_OK;
}
HRESULT CCollider::Add_BoxCollsionGroup(COLLSIONGROUP eCollsionGroup, CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	m_BoxCollisionObjects[eCollsionGroup].push_back(pGameObject);

	Safe_AddRef(pGameObject);

	return S_OK;
}
HRESULT CCollider::Add_PushBoxCollsionGroup(COLLSIONGROUP eCollsionGroup, CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	m_PhshBoxCollisionObjects[eCollsionGroup].push_back(pGameObject);

	Safe_AddRef(pGameObject);

	return S_OK;
}
HRESULT CCollider::End_Collsion()
{


	for (_int i = 0; i < COLLSION_END; ++i)
	{
		for (auto& pObject : m_PhshBoxCollisionObjects[i])
		{
			if (nullptr != pObject)
				Safe_Release(pObject);
		}

		m_PhshBoxCollisionObjects[i].clear();
	}

	for (_int i = 0; i < COLLSION_END; ++i)
	{
		for (auto& pObject : m_SphereCollisionObjects[i])
		{
			if (nullptr != pObject)
				Safe_Release(pObject);
		}

		m_SphereCollisionObjects[i].clear();
	}

	for (_int i = 0; i < COLLSION_END; ++i)
	{
		for (auto& pObject : m_BoxCollisionObjects[i])
		{
			if (nullptr != pObject)
				Safe_Release(pObject);
		}

		m_BoxCollisionObjects[i].clear();
	}



	return S_OK;
}




HRESULT CCollider::Set_SectionCubes()
{
	list<CGameObject*> Sections = m_PhshBoxCollisionObjects[COLLSION_SECTION];
	list<CGameObject*> Cubes= m_PhshBoxCollisionObjects[COLLSION_BLOCK];

	for (auto& Section : Sections)
	{
		m_Sections.push_back(Section);
		//Safe_AddRef(Section);
		for (auto& Cube : Cubes)
		{
			if (Check_Box(Section, Cube, false))
			{
				Section->Collision(Cube);
			}
		}
	}

	return S_OK;
}



HRESULT CCollider::Check_SphereCollsion(COLLSIONGROUP eCollsionGroup_L, COLLSIONGROUP eCollsionGroup_R)
{

	for (auto& pL_Object : m_SphereCollisionObjects[eCollsionGroup_L])
	{
		for (auto& pR_Object : m_SphereCollisionObjects[eCollsionGroup_R])
		{
			// �浹 �˻�
			if (Check_Sphere(pL_Object, pR_Object))
			{
				pL_Object->Collision(pR_Object);
				pR_Object->Collision(pL_Object);
			}
		}
	}

	return S_OK;
}
HRESULT CCollider::Check_BoxCollsion(COLLSIONGROUP eCollsionGroup_L, COLLSIONGROUP eCollsionGroup_R)
{
	for (auto& pL_Object : m_BoxCollisionObjects[eCollsionGroup_L])
	{
		for (auto& pR_Object : m_BoxCollisionObjects[eCollsionGroup_R])
		{
			// �浹 �˻�
			if (Check_Box(pL_Object, pR_Object))
			{
				pL_Object->Collision(pR_Object);
				pR_Object->Collision(pL_Object);
			}
		}
	}

	return S_OK;
}
HRESULT CCollider::Check_PushBoxCollsion(COLLSIONGROUP eCollsionGroup_L, COLLSIONGROUP eCollsionGroup_R)
{
	for (auto& pL_Object : m_PhshBoxCollisionObjects[eCollsionGroup_L])
	{
		pL_Object->Set_PushedX(false);
		pL_Object->Set_PushedY(false);

		for (auto& pR_Object : m_PhshBoxCollisionObjects[eCollsionGroup_R])
		{
			// �浹 �˻�
			if (Check_Box(pL_Object, pR_Object, true))
			{
				pL_Object->Collision(pR_Object);
				pR_Object->Collision(pL_Object);
			}
		}
	}

	return S_OK;
}



HRESULT CCollider::Check_PushCubeCollsion(COLLSIONGROUP eCollsionGroup_L)
{
	for (auto& pL_Object : m_PhshBoxCollisionObjects[eCollsionGroup_L])
	{
		pL_Object->Set_PushedX(false);
		pL_Object->Set_PushedY(false);

		for (auto& Section : m_Sections)
		{
			if (Check_Box(pL_Object, Section))
			{


				for (auto& pR_Object : *(Section->GetCubes()))
				{
					// �浹 �˻�
					if (Check_Box(pL_Object, pR_Object, true))
					{
						pL_Object->Collision(pR_Object);
						pR_Object->Collision(pL_Object);
					}
				}




			}
		}


	}

	return S_OK;
}




_bool CCollider::Check_Sphere(CGameObject * pObj_L, CGameObject * pObj_R)
{
	CTransform* pTranCom_L = (CTransform*)pObj_L->Get_ComponentPtr(TEXT("Com_Transform"));
	CTransform* pTranCom_R = (CTransform*)pObj_R->Get_ComponentPtr(TEXT("Com_Transform"));

	_float	ColRad_L = pObj_L->Get_ColRad();
	_float	ColRad_R = pObj_R->Get_ColRad();
	_float3 vPos_L = pTranCom_L->Get_State(CTransform::STATE_POSITION);
	_float3 vPos_R = pTranCom_R->Get_State(CTransform::STATE_POSITION);

	// 1. ���� �Ÿ��� ���Ѵ�
	_float3 fDisVec = vPos_L - vPos_R;
	_float fDis = D3DXVec3Length(&fDisVec);

	// 2. ���� ������ ���� ���Ѵ�
	_float fRadSum = ColRad_L + ColRad_R;

	// 3. ���Ѵ� >> ������ ���� ũ�� �浹�̴�
	if (fDis < fRadSum)
		return true;

	return false;
}
_bool CCollider::Check_Box(CGameObject * pObj_L, CGameObject * pObj_R, _bool bPush)
{
	list<CBoxCollider*>* pBoxColComs_L = pObj_L->Get_BoxColComList();
	list<CBoxCollider*>* pBoxColComs_R = pObj_R->Get_BoxColComList();

	for (auto& pBoxCol_L : *pBoxColComs_L)
	{

		for (auto& pBoxCol_R : *pBoxColComs_R)
		{
			_float3 vMax_L = pBoxCol_L->Get_WorldMax();
			_float3 vMin_L = pBoxCol_L->Get_WorldMin();
			_float3 vMax_R = pBoxCol_R->Get_WorldMax();
			_float3 vMin_R = pBoxCol_R->Get_WorldMin();


			_float fMax = 0.f;
			_float fMin = 0.f;
			_float3 fColDis = { -1.f, -1.f, -1.f };
			// 1.���� ū x�� x�� ���ؼ� ���� �༮�� ���Ѵ�.
			if (vMax_L.x < vMax_R.x)
				fMin = vMax_L.x;
			else
				fMin = vMax_R.x;

			// 2.���� ���� x�� x�� ���ؼ� ū �༮�� ���Ѵ�.
			if (vMin_L.x > vMin_R.x)
				fMax = vMin_L.x;
			else
				fMax = vMin_R.x;

			// 3.���� �༮���� ū �༮�� ũ�� ���ƴ�.
			if (fMin < fMax)
				continue;
			fColDis.x = fMin - fMax;


			// 1.���� ū x�� x�� ���ؼ� ���� �༮�� ���Ѵ�.
			if (vMax_L.y < vMax_R.y)
				fMin = vMax_L.y;
			else
				fMin = vMax_R.y;

			// 2.���� ���� x�� x�� ���ؼ� ū �༮�� ���Ѵ�.
			if (vMin_L.y > vMin_R.y)
				fMax = vMin_L.y;
			else
				fMax = vMin_R.y;

			// 3.���� �༮���� ū �༮�� ũ�� ���ƴ�.
			if (fMin < fMax)
				continue;

			fColDis.y = fMin - fMax;



			// 1.���� ū x�� x�� ���ؼ� ���� �༮�� ���Ѵ�.
			if (vMax_L.z < vMax_R.z)
				fMin = vMax_L.z;
			else
				fMin = vMax_R.z;

			// 2.���� ���� x�� x�� ���ؼ� ū �༮�� ���Ѵ�.
			if (vMin_L.z > vMin_R.z)
				fMax = vMin_L.z;
			else
				fMax = vMin_R.z;

			// 3.���� �༮���� ū �༮�� ũ�� ���ƴ�.
			if (fMin < fMax)
				continue;

			fColDis.z = fMin - fMax;

			if (bPush)
			{
				CTransform* vTran_L = (CTransform*)(pObj_L->Find_Component(TEXT("Com_Transform")));
				CTransform* vTran_R = (CTransform*)(pObj_R->Find_Component(TEXT("Com_Transform")));
				_float3 vPos_L = vTran_L->Get_State(CTransform::STATE_POSITION);
				_float3 vPos_R = vTran_R->Get_State(CTransform::STATE_POSITION);


				_float fRad_R = pBoxCol_R->Get_MaxRad();

				_float3 fDiferVec = vTran_L->Get_State(CTransform::STATE_POSITION) - vTran_R->Get_State(CTransform::STATE_POSITION);
				D3DXVec3Normalize(&fDiferVec, &fDiferVec);
				_float fDiferRadByL = D3DXVec3Dot(&fDiferVec, &_float3(0.f, 1.f, 0.f));


				// �� �浹�� ��
				if (fRad_R > fDiferRadByL)
				{
					if (fColDis.x < fColDis.z)
					{
						// ��
						if (vPos_L.x < vPos_R.x)
						{
							_float3 disPos = { vPos_L.x - fColDis.x - 0.05f , vPos_L.y, vPos_L.z };
							vTran_L->Set_State(CTransform::STATE_POSITION, disPos);
						}

						// ��
						else if (vPos_L.x > vPos_R.x)
						{
							_float3 disPos = { vPos_L.x + fColDis.x + 0.05f, vPos_L.y, vPos_L.z };
							vTran_L->Set_State(CTransform::STATE_POSITION, disPos);
						}
					}
					else
					{
						// ��
						if (vPos_L.z < vPos_R.z)
						{
							_float3 disPos = { vPos_L.x, vPos_L.y , vPos_L.z - fColDis.z -0.05f };
							vTran_L->Set_State(CTransform::STATE_POSITION, disPos);
						}

						// ��
						else if (vPos_L.z > vPos_R.z)
						{
							_float3 disPos = { vPos_L.x, vPos_L.y, vPos_L.z + fColDis.z + 0.05f };
							vTran_L->Set_State(CTransform::STATE_POSITION, disPos);
						}
					}
				}
				if(fRad_R < fDiferRadByL && -0.1f > vTran_L->Get_Vel())
				{
					if (vPos_L.y > vPos_R.y + 0.5f && !pObj_L->Get_PushedY())
					{
						_float3 disPos = { vPos_L.x, vPos_L.y + fColDis.y, vPos_L.z };
						vTran_L->Set_State(CTransform::STATE_POSITION, disPos);
						vTran_L->ReSet_Gravity();
						pObj_L->Set_PushedY(true);
					}

					// 2. ��
				}
			}

			return true;
		}

		return false;
	}
	return false;
}


CCollider * CCollider::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CCollider*			pInstance = new CCollider(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CRenderer"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
CComponent * CCollider::Clone(void * pArg)
{
	AddRef();

	return this;
}
void CCollider::Free()
{
	__super::Free();

	End_Collsion();

	//for (auto& Section : m_Sections)
	//	Safe_Release(Section);
}
