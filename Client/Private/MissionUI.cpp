#include "stdafx.h"
#include "..\Public\MissionUI.h"
#include "GameInstance.h"
#include "QuestManager.h"

CMissionUI::CMissionUI(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
	ZeroMemory(&m_UIInfo, sizeof(UIINFO));
}

CMissionUI::CMissionUI(const CMissionUI & rhs)
	: CGameObject(rhs)
{
}

HRESULT CMissionUI::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CMissionUI::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinSizeX, g_iWinSizeY, 0, 1);

	m_UIInfo.fSizeX = 150.0f;
	m_UIInfo.fSizeY = 150.0f;
	m_UIInfo.fX = 1200.0f;
	m_UIInfo.fY = 320.0f;

	m_pTransformCom->Set_Scaled(_float3(m_UIInfo.fSizeX, m_UIInfo.fSizeY, 1.f));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_UIInfo.fX - g_iWinSizeX * 0.5f, -m_UIInfo.fY + g_iWinSizeY * 0.5f, 0.f));

	
	


	return S_OK;
}

void CMissionUI::Tick(_float fTimeDelta)
{
	POINT		ptMouse;
	GetCursorPos(&ptMouse);

	ScreenToClient(g_hWnd, &ptMouse);

	RECT		rcUI;
	SetRect(&rcUI, m_UIInfo.fX - m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY - m_UIInfo.fSizeY * 0.5f, m_UIInfo.fX + m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY + m_UIInfo.fSizeY * 0.5f);

}

void CMissionUI::LateTick(_float fTimeDelta)
{
	

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);
}

HRESULT CMissionUI::Render()
{

	_float4x4		Matrix;
	D3DXMatrixIdentity(&Matrix);


	// ����ִ� ����Ʈ ui�� ���
	if (FAILED(m_pTextureCom->Bind_Texture(0)))
		return E_FAIL;



	//m_pGraphic_Device->SetTransform(D3DTS_WORLD, &Matrix);
	m_pTransformCom->Bind_WorldMatrix();
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &Matrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CMissionUI::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), TEXT("Com_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

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

	/* For.Com_Texture */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Quest"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;


	
	return S_OK;
}

void CMissionUI::MouseCollision()
{
}

CMissionUI * CMissionUI::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CMissionUI*		pInstance = new CMissionUI(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CMissionUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMissionUI::Clone(void* pArg)
{
	CMissionUI*		pInstance = new CMissionUI(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Created : CMissionUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMissionUI::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
}

