#include "stdafx.h"
#include "..\Public\Chat.h"
#include "GameInstance.h"
#include "QuestManager.h"
#include "SkillManager.h"

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
	m_bCountCheck = false;
	m_bCountCheck2 = false;
	m_bWhy = false;
	m_iRandom = 0;

	m_fCount = 0;
	m_fCountChat = 0;

	m_iChatProgress = 0;

	D3DXCreateFont(m_pGraphic_Device, 45, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Consolas"), &m_pFontName);

	D3DXCreateFont(m_pGraphic_Device, 33, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Arial"), &m_pFont);

	D3DXMatrixOrthoLH(&m_ProjMatrix, _float(g_iWinSizeX), _float(g_iWinSizeY), 0, 1);

	m_UIInfo.fSizeX = 1024.0f;
	m_UIInfo.fSizeY = 512.0f;
	m_UIInfo.fX = 650.0f;
	m_UIInfo.fY = 500.0f;

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
	SetRect(&rcUI, _int(m_UIInfo.fX - m_UIInfo.fSizeX * 0.5f), _int(m_UIInfo.fY - m_UIInfo.fSizeY * 0.5f), _int(m_UIInfo.fX + m_UIInfo.fSizeX * 0.5f), _int(m_UIInfo.fY + m_UIInfo.fSizeY * 0.5f));

	CQuestManager* pInstance = CQuestManager::Get_Instance();

	if (m_bCountCheck)
		m_fCount += 1.f * fTimeDelta;

	// npc채팅이 켜졌을때 채팅의 카운트를 증가시킴
	if(m_bCountCheck2)
		m_fCountChat += 1.f * fTimeDelta;
}

void CChat::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);

	CQuestManager* pInstance = CQuestManager::Get_Instance();

	m_bChat = pInstance->Check_Quest();

}

HRESULT CChat::Render()
{
	RECT rc;
	_float4x4		Matrix;
	D3DXMatrixIdentity(&Matrix);



	//m_pGraphic_Device->SetTransform(D3DTS_WORLD, &Matrix);
	m_pTransformCom->Bind_WorldMatrix();
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &Matrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphic_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphic_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	CQuestManager* pInstance = CQuestManager::Get_Instance();

	m_bChat = pInstance->Check_Quest(); 


	if (pInstance->Set_QuestState() == 1)
	{
		if (CGameInstance::Get_Instance()->Key_Down(DIKEYBOARD_SPACE))
		{
			m_bWhy = true;
		}
		if (m_bWhy)
		{
			Bind_Animation();
			m_pVIBufferCom->Render();

			if (!m_bCountCheck)
			{
				TCHAR cChat[128];
				_tchar m_cNPCChat[128];
				wsprintf(cChat, TEXT("장로스탄"));
				SetRect(&rc, 350, 500, 0, 0);
				m_pFont->DrawText(NULL, cChat,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.45f, 0.f, 1.f));


				if (m_iRandom == 0)
				{
					wsprintf(m_cNPCChat, TEXT("자네 아직도 안갔나?"));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				}

				else if (m_iRandom == 1)
				{
					wsprintf(m_cNPCChat, TEXT("허허..농작물들이 다 죽겠구만"));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				}


				else if (m_iRandom == 2)
				{
					wsprintf(m_cNPCChat, TEXT("흠..."));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				}


				if (CGameInstance::Get_Instance()->Key_Down(DIKEYBOARD_RETURN))
				{
					m_bWhy = false;
					m_fCount = 0;
					m_iRandom = (CGameInstance::Get_Instance()->Get_Random(0, 2));
				}
			}
			
		}
	}

	if (pInstance->Get_QuestNum() == 1)
	{
		// 퀘스트매니져를 통해 가져온 채팅값이 TRUE이면 채팅을 그림, 엔터를 누르면 퀘스트 전구를 진행으로 바꾸고 채팅값을 FALSE로 만듦
		if (m_bChat && pInstance->Set_QuestState() == 0)
		{
			Bind_Animation();
			m_pVIBufferCom->Render();

			// 시작 애니메이션이 다 그려지면
			if (!m_bCountCheck)
			{
				m_bCountCheck2 = true;
				TCHAR cChat[128];
				_tchar m_cNPCChat[128];

				wsprintf(cChat, TEXT("장로스탄"));
				SetRect(&rc, 350, 500, 0, 0);
				m_pFont->DrawText(NULL, cChat,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.45f, 0.f, 1.f));

				if (CGameInstance::Get_Instance()->Key_Down(DIKEYBOARD_SPACE))
					m_iChatProgress++;

				if (m_iChatProgress == 0)
				{
					wsprintf(m_cNPCChat, TEXT("오오..기다리고 있었네, 몸은 좀 어떤가 용사여."));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				}

				else if (m_iChatProgress == 1)
				{
					wsprintf(m_cNPCChat, TEXT("자네를 찾고 있었는데 금방 와주었구만."));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				}

				else if (m_iChatProgress == 2)
				{
					wsprintf(m_cNPCChat, TEXT("사실 마을에 큰 문제가 생겼네."));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				}

				else if (m_iChatProgress == 3)
				{
					wsprintf(m_cNPCChat, TEXT("자네도 알다시피 우리 헤네시스 주민들은\n농장을 운영하여 생활하고 있네"));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				}

				else if (m_iChatProgress == 4)
				{
					wsprintf(m_cNPCChat, TEXT("헤네시스에 이런저런 몬스터가 많긴하지만 그동안 달팽이들이 가끔\n농작물을 몇개 훔쳐먹는걸 제외하고는 딱히 농장에 큰 피해는 없었지."));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				}

				else if (m_iChatProgress == 5)
				{
					wsprintf(m_cNPCChat, TEXT("그런데 주황버섯 녀석들이 농장에 먹을것이 있다는것을 알아차렸는지,\n지난주부터 단체로 나타나서는 농작물을 전부 훔쳐먹고 망치는게 아닌가!"));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				}

				else if (m_iChatProgress == 6)
				{
					wsprintf(m_cNPCChat, TEXT("이대로 가다간 모두 굶어 죽고 말거야"));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				}

				else
				{
					wsprintf(m_cNPCChat, TEXT("그러니 시간만 괜찮다면 자네가 주황버섯들을 혼내줬으면 하는데..\n가능하겠는가?"));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				}
			}

			if ((GetKeyState(VK_RETURN) & 0x8000))
			{
				pInstance->QuestProgress();
				pInstance->Check_End_Quest();
				m_fCount = 0;
			}
		}

		if (m_bChat && pInstance->Set_QuestState() == 2)
		{
			Bind_Animation();
			m_pVIBufferCom->Render();
			if (GetKeyState(VK_RETURN) & 0x8000)
			{
				m_fCount = 0;
				pInstance->QuestPrepare();
				pInstance->Check_End_Quest();
				pInstance->Reset_Hunt();
				CQuestManager::Get_Instance()->Set_Second();
				CSkillManager::Get_Instance()->Set_SkillPoint(3);
			}
		}
	}

	else if (pInstance->Get_QuestNum() == 2)
	{
		// 퀘스트매니져를 통해 가져온 채팅값이 TRUE이면 채팅을 그림, 엔터를 누르면 퀘스트 전구를 진행으로 바꾸고 채팅값을 FALSE로 만듦
		if (m_bChat && pInstance->Set_QuestState() == 0)
		{
			Bind_Animation();
			m_pVIBufferCom->Render();
			if ((GetKeyState(VK_RETURN) & 0x8000))
			{
				m_fCount = 0;
				pInstance->QuestProgress();
				pInstance->Check_End_Quest();
			}
		}

		if (m_bChat && pInstance->Set_QuestState() == 2)
		{
			Bind_Animation();
			m_pVIBufferCom->Render();
			if (GetKeyState(VK_RETURN) & 0x8000)
			{
				m_fCount = 0;
				pInstance->QuestEnd();
				pInstance->Check_End_Quest();
				pInstance->Reset_Hunt();
				CSkillManager::Get_Instance()->Set_SkillPoint(3);
			}
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
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Chat"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
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

void CChat::Bind_Animation()
{
	m_bCountCheck = true;
	if (m_fCount <= 0.1)
		m_pTextureCom->Bind_Texture(0);
	else if (0.1 < m_fCount && m_fCount <= 0.12)
		m_pTextureCom->Bind_Texture(1);
	else if (0.12 < m_fCount && m_fCount <= 0.14)
		m_pTextureCom->Bind_Texture(2);
	else if (0.14 < m_fCount && m_fCount <= 0.16)
		m_pTextureCom->Bind_Texture(3);
	else if (0.16 < m_fCount && m_fCount <= 0.18)
		m_pTextureCom->Bind_Texture(4);
	else if (0.18 < m_fCount && m_fCount <= 0.2)
		m_pTextureCom->Bind_Texture(5);
	else if (0.2 < m_fCount && m_fCount <= 0.22)
		m_pTextureCom->Bind_Texture(6);
	else if (0.22 < m_fCount && m_fCount <= 0.24)
		m_pTextureCom->Bind_Texture(7);
	else if (0.24 < m_fCount && m_fCount <= 0.26)
		m_pTextureCom->Bind_Texture(8);
	else if (0.26 < m_fCount && m_fCount <= 0.28)
		m_pTextureCom->Bind_Texture(9);
	else if (0.28 < m_fCount && m_fCount <= 0.3)
		m_pTextureCom->Bind_Texture(10);
	else if (0.3 < m_fCount && m_fCount <= 0.32)
		m_pTextureCom->Bind_Texture(11);
	else if (0.32 < m_fCount && m_fCount <= 0.34)
		m_pTextureCom->Bind_Texture(12);
	else if (0.34 < m_fCount && m_fCount <= 0.36)
		m_pTextureCom->Bind_Texture(13);
	else if (0.36 < m_fCount && m_fCount <= 0.38)
		m_pTextureCom->Bind_Texture(14);
	else if (0.38 < m_fCount && m_fCount <= 0.4)
		m_pTextureCom->Bind_Texture(15);
	else if (0.4 < m_fCount && m_fCount <= 0.42)
		m_pTextureCom->Bind_Texture(16);
	else if (0.42 < m_fCount && m_fCount <= 0.44)
		m_pTextureCom->Bind_Texture(17);
	else if (0.44 < m_fCount && m_fCount <= 0.47)
		m_pTextureCom->Bind_Texture(18);
	else if (0.47 < m_fCount && m_fCount <= 0.5)
		m_pTextureCom->Bind_Texture(19);
	else if (0.5 < m_fCount && m_fCount <= 0.53)
		m_pTextureCom->Bind_Texture(20);
	else if (0.53 < m_fCount && m_fCount <= 0.56)
		m_pTextureCom->Bind_Texture(21);
	else if (0.56 < m_fCount && m_fCount <= 0.59)
		m_pTextureCom->Bind_Texture(22);
	else
	{
		m_pTextureCom->Bind_Texture(23);
		m_bCountCheck = false;
	}
}

void CChat::Create_Chat(string Chat)
{
}

