#include "..\Public\Picking.h"
#include "Transform.h"

IMPLEMENT_SINGLETON(CPicking)

CPicking::CPicking()
{
}


HRESULT CPicking::Initialize(HWND hWnd, _uint iWinCX, _uint iWinCY, LPDIRECT3DDEVICE9 pGraphic_Device)
{
	m_pGraphic_Device = pGraphic_Device;

	Safe_AddRef(m_pGraphic_Device);

	m_hWnd = hWnd;

	m_iWinCX = iWinCX;

	m_iWinCY = iWinCY;

	return S_OK;
}

void CPicking::Tick()
{
	POINT			ptMouse;

	GetCursorPos(&ptMouse);

	ScreenToClient(m_hWnd, &ptMouse);

	_float3			vMousePos;

	/* ������������ ���콺 ��ǥ�� ���Ѵ�. */
	vMousePos.x = _float(ptMouse.x / (m_iWinCX * 0.5f) - 1);
	vMousePos.y = _float(ptMouse.y / (m_iWinCY * -0.5f) + 1);
	vMousePos.z = 0.f;


	/* �佺���̽� ���� ��ǥ�� ���Ѵ�. */
	_float4x4		ProjMatrixInv;
	m_pGraphic_Device->GetTransform(D3DTS_PROJECTION, &ProjMatrixInv);
	D3DXMatrixInverse(&ProjMatrixInv, nullptr, &ProjMatrixInv);
	D3DXVec3TransformCoord(&vMousePos, &vMousePos, &ProjMatrixInv);

	/* �佺���̽� ���� ���콺 ���̿� ���������� ������. */
	m_vRayPos = _float3(0.f, 0.f, 0.f);
	m_vRayDir = vMousePos - m_vRayPos;

	/* ���彺���̽� ���� ���콺 ���̿� ���������� ������. */
	_float4x4		ViewMatrixInv;
	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &ViewMatrixInv);
	D3DXMatrixInverse(&ViewMatrixInv, nullptr, &ViewMatrixInv);
	D3DXVec3TransformCoord(&m_vRayPos, &m_vRayPos, &ViewMatrixInv);
	D3DXVec3TransformNormal(&m_vRayDir, &m_vRayDir, &ViewMatrixInv);

}

void CPicking::Compute_LocalRayInfo(_float3 * pRayDir, _float3 * pRayPos, CTransform * pTransform)
{
	_float4x4		WorldMatrixInv = pTransform->Get_WorldMatrixInverse();

	D3DXVec3TransformCoord(pRayPos, &m_vRayPos, &WorldMatrixInv);
	D3DXVec3TransformNormal(pRayDir, &m_vRayDir, &WorldMatrixInv);
}

void CPicking::Free()
{
	Safe_Release(m_pGraphic_Device);
}
