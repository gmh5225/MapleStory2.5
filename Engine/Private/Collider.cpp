#include "..\Public\Collider.h"

#include "GameObject.h"
#include "Transform.h"

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

HRESULT CCollider::Add_CollsionGroup(COLLSIONGROUP eCollsionGroup, CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	m_CollisionObjects[eCollsionGroup].push_back(pGameObject);

	Safe_AddRef(pGameObject);

	return S_OK;
}

HRESULT CCollider::Check_SphereCollsion(COLLSIONGROUP eCollsionGroup_L, COLLSIONGROUP eCollsionGroup_R)
{
	for (auto& pL_Object : m_CollisionObjects[eCollsionGroup_L])
	{
		for (auto& pR_Object : m_CollisionObjects[eCollsionGroup_R])
		{
			// 충돌 검사
			if (Check_Sphere(pL_Object, pR_Object))
			{
				pL_Object->Collision(pR_Object);
				pR_Object->Collision(pL_Object);
			}
		}
	}

	return S_OK;
}

HRESULT CCollider::End_Collsion()
{
	for (_int i = 0; i < COLLSION_END; ++i)
	{
		for (auto& pObject : m_CollisionObjects[i])
		{
			if (nullptr != pObject)
				Safe_Release(pObject);
		}

		m_CollisionObjects[i].clear();
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

	// 1. 둘의 거리를 구한다
	_float3 fDisVec = vPos_L - vPos_R;
	_float fDis = D3DXVec3Length(&fDisVec);

	// 2. 둘의 반지름 합을 구한다
	_float fRadSum = ColRad_L + ColRad_R;

	// 3. 비교한다 >> 반지름 합이 크면 충돌이다
	if (fDis < fRadSum)
		return true;

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

	for (auto& List : m_CollisionObjects)
	{
		for (auto& pGameObject : List)
		{
			Safe_Release(pGameObject);
		}
		List.clear();
	}	
}
