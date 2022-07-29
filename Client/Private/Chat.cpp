#include "stdafx.h"
#include "..\Public\Chat.h"
#include "GameInstance.h"
#include "QuestManager.h"

CChat::CChat(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
	ZeroMemory(&m_UIInfo, sizeof(UIINFO));
}

CChat::CChat(const CChat & rhs)
	: CGameObject(rhs)
{
}

HRESULT CChat::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CChat::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_bChat = false;

	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinSizeX, g_iWinSizeY, 0, 1);

	m_UIInfo.fSizeX = 750.0f;
	m_UIInfo.fSizeY = 250.0f;
	m_UIInfo.fX = 650.0f;
	m_UIInfo.fY = 600.0f;

	m_pTransformCom->Set_Scaled(_float3(m_UIInfo.fSizeX, m_UIInfo.fSizeY, 1.f));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_UIInfo.fX - g_iWinSizeX * 0.5f, -m_UIInfo.fY + g_iWinSizeY * 0.5f, 0.f));





	return S_OK;
}

void CChat::Tick(_float fTimeDelta)
{
	POINT		ptMouse;
	GetCursorPos(&ptMouse);

	ScreenToClient(g_hWnd, &ptMouse);

	RECT		rcUI;
	SetRect(&rcUI, m_UIInfo.fX - m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY - m_UIInfo.fSizeY * 0.5f, m_UIInfo.fX + m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY + m_UIInfo.fSizeY * 0.5f);


	/*if (PtInRect(&rcUI, ptMouse))
	{
	MouseCollision();
	}*/
}

void CChat::LateTick(_float fTimeDelta)
{


	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);
}

HRESULT CChat::Render()
{

	_float4x4		Matrix;
	D3DXMatrixIdentity(&Matrix);



	//m_pGraphic_Device->SetTransform(D3DTS_WORLD, &Matrix);
	m_pTransformCom->Bind_WorldMatrix();
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &Matrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	CQuestManager* pInstance = CQuestManager::Get_Instance();

	m_bChat = pInstance->Check_Quest();

	// 퀘스트매니져를 통해 가져온 채팅값이 TRUE이면 채팅을 그림, W를 누르면 퀘스트 전구를 진행으로 바꾸고 채팅값을 FALSE로 만듦
	if (m_bChat && pInstance->Set_QuestState() == 0)
	{
		m_pTextureCom->Bind_Texture(0);
		m_pVIBufferCom->Render();
		if ((GetKeyState(VK_RETURN)& 0x8000))
		{
			pInstance->QuestPrepared();
			pInstance->Check_End_Quest();
		}
	}

	if (m_bChat && pInstance->Set_QuestState() == 2)
	{
		m_pTextureCom->Bind_Texture(1);
		m_pVIBufferCom->Render();
		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			pInstance->Reset_Hunt();
			pInstance->QuestStart();
			pInstance->Check_End_Quest();
		}
	}

	return S_OK;
}

HRESULT CChat::SetUp_Components()
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
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Chat"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;



	return S_OK;
}

void CChat::MouseCollision()
{
}

CChat * CChat::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CChat*		pInstance = new CChat(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CChat"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CChat::Clone(void* pArg)
{
	CChat*		pInstance = new CChat(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Created : CChat clone"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CChat::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
}

