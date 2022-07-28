#include "..\Public\BoxCollider.h"

#include "GameObject.h"
#include "Transform.h"

CBoxCollider::CBoxCollider(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
}
CBoxCollider::CBoxCollider(const CBoxCollider & rhs)
	: CComponent(rhs)
	, m_vMax(rhs.m_vMax)
	, m_vMin(rhs.m_vMin)
	, m_vPivot(rhs.m_vPivot)
{

}

HRESULT CBoxCollider::Initialize_Prototype()
{
	m_vMax = { 0.5f, 0.5f, 0.5f };
	m_vMin = { -0.5f, -0.5f, -0.5f };
	m_vPivot = { 0.f, 0.f, 0.f };

	return S_OK;
}
HRESULT CBoxCollider::Initialize(void * pArg)
{
	if (nullptr == pArg)
		return S_OK;

	BOXCOLCOMEDESC* pDesc = (BOXCOLCOMEDESC*)pArg;

	m_vMax.x *= pDesc->vScale.x;
	m_vMax.y *= pDesc->vScale.y;
	m_vMax.z *= pDesc->vScale.z;

	m_vMin.x *= pDesc->vScale.x;
	m_vMin.y *= pDesc->vScale.y;
	m_vMin.z *= pDesc->vScale.z;

	m_vPivot = pDesc->vPivot;

	return S_OK;
}

void CBoxCollider::Tick(CTransform* pTrans)
{
	// 1.스케일을 보관
	_float3 vScale = pTrans->Get_Scaled();

	// 2.방향 1 1 1 * 스케일 짜리 포스있는 것만
	_float4x4 BoxMat;
	D3DXMatrixIdentity(&BoxMat);
	*(_float3*)(&BoxMat.m[0][0]) = _float3{ 1.f * vScale.x, 0.f, 0.f };
	*(_float3*)(&BoxMat.m[1][0]) = _float3{ 0.f, 1.f * vScale.y, 0.f };
	*(_float3*)(&BoxMat.m[2][0]) = _float3{ 0.f, 0.f, 1.f * vScale.z };
	*(_float3*)(&BoxMat.m[3][0]) = (pTrans->Get_State(CTransform::STATE_POSITION));

	// 3.vMax, vMin 월드를 구한다.
	D3DXVec3TransformCoord(&m_vWorldMax, &m_vMax, &BoxMat);
	D3DXVec3TransformCoord(&m_vWorldMin, &m_vMin, &BoxMat);
}










CBoxCollider * CBoxCollider::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBoxCollider*			pInstance = new CBoxCollider(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CBoxCollider"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
CComponent * CBoxCollider::Clone(void * pArg)
{
	CBoxCollider*			pInstance = new CBoxCollider(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CBoxCollider"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
void CBoxCollider::Free()
{
	__super::Free();


}
