#include "stdafx.h"
#include "..\Public\QuestUI.h"
#include "GameInstance.h"
#include "QuestManager.h"

CQuestUI::CQuestUI(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
	ZeroMemory(&m_UIInfo, sizeof(UIINFO));
}

CQuestUI::CQuestUI(const CQuestUI & rhs)
	: CGameObject(rhs)
{
}

HRESULT CQuestUI::Initialize_Prototype()
{

	return S_OK;
}

HRESULT CQuestUI::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;


	D3DXCreateFont(m_pGraphic_Device, 15, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Arial"), &m_pFont);


	D3DXMatrixOrthoLH(&m_ProjMatrix, (_float)g_iWinSizeX, (_float)g_iWinSizeY, 0.f, 1.f);

	m_UIInfo.fSizeX = 170.0f;
	m_UIInfo.fSizeY = 150.0f;
	m_UIInfo.fX = 1180.0f;
	m_UIInfo.fY = 320.0f;

	m_pTransformCom->Set_Scaled(_float3(m_UIInfo.fSizeX, m_UIInfo.fSizeY, 1.f));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_UIInfo.fX - g_iWinSizeX * 0.5f, -m_UIInfo.fY + g_iWinSizeY * 0.5f, 0.f));

		D3DXCreateFont(m_pGraphic_Device, 15, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Arial"), &m_pFont);

	return S_OK;
}

void CQuestUI::Tick(_float fTimeDelta)
{
	POINT		ptMouse;
	GetCursorPos(&ptMouse);

	ScreenToClient(g_hWnd, &ptMouse);

	RECT		rcUI;
	SetRect(&rcUI, _int(m_UIInfo.fX - m_UIInfo.fSizeX * 0.5f), _int(m_UIInfo.fY - m_UIInfo.fSizeY * 0.5f), _int(m_UIInfo.fX + m_UIInfo.fSizeX * 0.5f), _int(m_UIInfo.fY + m_UIInfo.fSizeY * 0.5f));


}

void CQuestUI::LateTick(_float fTimeDelta)
{

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);
}

HRESULT CQuestUI::Render()
{
	RECT rc;
	_float4x4		Matrix;
	D3DXMatrixIdentity(&Matrix);
	CQuestManager* Questinstance = CQuestManager::Get_Instance();


	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphic_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphic_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);







	// 퀘스트의 상태가 1일때 -퀘스트가 진행중일 때만 퀘스트가 비어있다는것을 출력, 다른 경우에 퀘스트창이 비어있음을 출력
	if (Questinstance->Set_QuestState() == 1 || Questinstance->Set_QuestState() == 2)
	{
		if (FAILED(m_pTextureCom->Bind_Texture(1)))
		{
			return E_FAIL;
		}
	}
	else
	{
		if (FAILED(m_pTextureCom->Bind_Texture(0)))
			return E_FAIL;
	}



	m_pTransformCom->Bind_WorldMatrix();
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &Matrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	m_pVIBufferCom->Render();

	TCHAR cHunt[128];
	TCHAR cOrangeMushroom[50];
	TCHAR cCountHunt[15];
	_uint iOrangeMushroom = Questinstance->Set_OrangeMushroom();
	wsprintf(cHunt,TEXT("[헤네시스] 농장을 망치는 범인\n") TEXT(" 주황버섯"));
	wsprintf(cOrangeMushroom, TEXT("%d"), iOrangeMushroom);
	wsprintf(cCountHunt, TEXT(" / 10"));

	if (Questinstance->Set_QuestState() == 1 || Questinstance->Set_QuestState() == 2)
	{
		SetRect(&rc, 1100, 270, 1200, 150);
		m_pFont->DrawText(NULL, cHunt,
			-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		if (iOrangeMushroom == 10)
		{
			SetRect(&rc, 1165, 285, 1205, 165);
			m_pFont->DrawText(NULL, cOrangeMushroom,
				-1, &rc, DT_NOCLIP, D3DXCOLOR(0.f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			SetRect(&rc, 1165, 285, 1205, 165);
			m_pFont->DrawText(NULL, cOrangeMushroom,
				-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, 1.0f));
		}

		SetRect(&rc, 1178, 285, 1218, 165);
		m_pFont->DrawText(NULL, cCountHunt,
			-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}



	return S_OK;
}

HRESULT CQuestUI::SetUp_Components()
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

void CQuestUI::MouseCollision()
{
}

CQuestUI * CQuestUI::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CQuestUI*		pInstance = new CQuestUI(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CQuestUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CQuestUI::Clone(void* pArg)
{
	CQuestUI*		pInstance = new CQuestUI(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Created : CQuestUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CQuestUI::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
}

