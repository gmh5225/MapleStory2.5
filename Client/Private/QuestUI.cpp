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


	return S_OK;
}

void CQuestUI::Tick(_float fTimeDelta)
{
	if (CQuestManager::Get_Instance()->Set_OrangeMushroom() >= 10)
		CQuestManager::Get_Instance()->QuestClear();
	else if (CQuestManager::Get_Instance()->Set_StoneGolem() >= 1)
		CQuestManager::Get_Instance()->QuestClear();

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


	// ����Ʈ�� ���°� 1�϶� -����Ʈ�� �������� ���� ����Ʈ�� ����ִٴ°��� ���, �ٸ� ��쿡 ����Ʈâ�� ��������� ���
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

	if (Questinstance->Get_QuestNum() == 1)
	{

		TCHAR cHunt[128];
		TCHAR cOrangeMushroom[50];
		TCHAR cCountHunt[15];
		_uint iOrangeMushroom = Questinstance->Set_OrangeMushroom();
		wsprintf(cHunt, TEXT("[��׽ý�] ������ ��ġ�� ����\n") TEXT(" ��Ȳ����"));
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
	}

	else if (Questinstance->Get_QuestNum() == 2)
	{
		TCHAR cQuest[128];
		TCHAR cRedShell[50];
		TCHAR cCountRed[15];

		_tchar cQuest2[20];
		_tchar cBlueShell[20];
		TCHAR cCountBlue[15];

		_tchar cQuest3[20];
		_tchar cPigRibbon[20];
		TCHAR cCountRibbon[15];

		_uint iRedShell = Questinstance->Set_RedShell();
		_uint iBlueShell = Questinstance->Set_BlueShell();
		_uint iPigRibbon = Questinstance->Set_PigRibbon();

		wsprintf(cQuest, TEXT("[��׽ý�] �ֹֺ����� ���ϼ���\n") TEXT(" ���� ����"));
		wsprintf(cRedShell, TEXT("%d"), iRedShell);
		wsprintf(cCountRed, TEXT(" / 2\n"));


		wsprintf(cQuest2, TEXT(" �Ķ� ����"));
		wsprintf(cBlueShell, TEXT("%d"), iBlueShell);
		wsprintf(cCountBlue, TEXT(" / 2\n"));

		wsprintf(cQuest3, TEXT("������ ����"));
		wsprintf(cPigRibbon, TEXT("%d"), iPigRibbon);
		wsprintf(cCountRibbon, TEXT(" / 2"));


		if (Questinstance->Set_QuestState() == 1 || Questinstance->Set_QuestState() == 2)
		{
			SetRect(&rc, 1100, 270, 1200, 150);
			m_pFont->DrawText(NULL, cQuest,
				-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			if (iRedShell >= 2)
			{
				SetRect(&rc, 1165, 285, 1205, 165);
				m_pFont->DrawText(NULL, cRedShell,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(0.f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				SetRect(&rc, 1165, 285, 1205, 165);
				m_pFont->DrawText(NULL, cRedShell,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, 1.0f));
			}

			SetRect(&rc, 1178, 285, 1218, 165);
			m_pFont->DrawText(NULL, cCountRed,
				-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));




			SetRect(&rc, 1100, 300, 1200, 150);
			m_pFont->DrawText(NULL, cQuest2,
				-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			if (iBlueShell >= 2)
			{
				SetRect(&rc, 1165, 300, 1205, 165);
				m_pFont->DrawText(NULL, cBlueShell,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(0.f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				SetRect(&rc, 1165, 300, 1205, 165);
				m_pFont->DrawText(NULL, cBlueShell,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, 1.0f));
			}

			SetRect(&rc, 1178, 300, 1218, 165);
			m_pFont->DrawText(NULL, cCountBlue,
				-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));



			SetRect(&rc, 1105, 315, 1200, 150);
			m_pFont->DrawText(NULL, cQuest3,
				-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			if (iPigRibbon >= 2)
			{
				SetRect(&rc, 1170, 315, 1205, 165);
				m_pFont->DrawText(NULL, cPigRibbon,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(0.f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				SetRect(&rc, 1170, 315, 1205, 165);
				m_pFont->DrawText(NULL, cPigRibbon,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, 1.0f));
			}

			SetRect(&rc, 1183, 315, 1218, 165);
			m_pFont->DrawText(NULL, cCountRibbon,
				-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));



		}
	}

	else if (Questinstance->Get_QuestNum() == 3)
	{
		TCHAR cHunt[128];
		TCHAR cStoneGolem[50];
		TCHAR cCountHunt[15];
		_uint iStoneGolem = Questinstance->Set_StoneGolem();
		wsprintf(cHunt, TEXT("[��׽ý�] ���� ���� �Ķ�������\n") TEXT(" ���ӽ���"));
		wsprintf(cStoneGolem, TEXT("%d"), iStoneGolem);
		wsprintf(cCountHunt, TEXT(" / 1"));

		if (Questinstance->Set_QuestState() == 1 || Questinstance->Set_QuestState() == 2)
		{
			SetRect(&rc, 1100, 270, 1200, 150);
			m_pFont->DrawText(NULL, cHunt,
				-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			if (iStoneGolem == 1)
			{
				SetRect(&rc, 1165, 285, 1205, 165);
				m_pFont->DrawText(NULL, cStoneGolem,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(0.f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				SetRect(&rc, 1165, 285, 1205, 165);
				m_pFont->DrawText(NULL, cStoneGolem,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, 1.0f));
			}

			SetRect(&rc, 1178, 285, 1218, 165);
			m_pFont->DrawText(NULL, cCountHunt,
				-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	else if (Questinstance->Get_QuestNum() == 4)
	{
		TCHAR cQuest[128];
		TCHAR cSlimeEssence[50];
		TCHAR cCountSlime[15];

		_tchar cQuest2[20];
		_tchar cStumpFirewoodl[20];
		TCHAR cCountStump[15];

		_tchar cQuest3[20];
		_tchar cGreenMushroom[20];
		TCHAR cCountMushroom[15];

		_uint iSlimeEssence = Questinstance->Set_SlimeEssence();
		_uint iStumpFirewoodl = Questinstance->Set_StumpFirewood();
		_uint iGreenMushroom = Questinstance->Set_GreenMushroom();

		wsprintf(cQuest, TEXT("[�����Ͼ�] ��ν�ź�� �����\n") TEXT(" ������ ����"));
		wsprintf(cSlimeEssence, TEXT("%d"), iSlimeEssence);
		wsprintf(cCountSlime, TEXT(" / 2\n"));


		wsprintf(cQuest2, TEXT(" �������� ����"));
		wsprintf(cStumpFirewoodl, TEXT("%d"), iStumpFirewoodl);
		wsprintf(cCountStump, TEXT(" / 2\n"));

		wsprintf(cQuest3, TEXT("�ʷϹ����� ��"));
		wsprintf(cGreenMushroom, TEXT("%d"), iGreenMushroom);
		wsprintf(cCountMushroom, TEXT(" / 2"));


		if (Questinstance->Set_QuestState() == 1 || Questinstance->Set_QuestState() == 2)
		{
			SetRect(&rc, 1100, 270, 1200, 150);
			m_pFont->DrawText(NULL, cQuest,
				-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			if (iSlimeEssence >= 2)
			{
				SetRect(&rc, 1200, 285, 1205, 165);
				m_pFont->DrawText(NULL, cSlimeEssence,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(0.f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				SetRect(&rc, 1200, 285, 1205, 165);
				m_pFont->DrawText(NULL, cSlimeEssence,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, 1.0f));
			}

			SetRect(&rc, 1213, 285, 1218, 165);
			m_pFont->DrawText(NULL, cCountSlime,
				-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));




			SetRect(&rc, 1100, 300, 1200, 150);
			m_pFont->DrawText(NULL, cQuest2,
				-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			if (iStumpFirewoodl >= 2)
			{
				SetRect(&rc, 1200, 300, 1205, 165);
				m_pFont->DrawText(NULL, cStumpFirewoodl,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(0.f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				SetRect(&rc, 1200, 300, 1205, 165);
				m_pFont->DrawText(NULL, cStumpFirewoodl,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, 1.0f));
			}

			SetRect(&rc, 1213, 300, 1218, 165);
			m_pFont->DrawText(NULL, cCountStump,
				-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));



			SetRect(&rc, 1105, 315, 1200, 150);
			m_pFont->DrawText(NULL, cQuest3,
				-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			if (iGreenMushroom >= 2)
			{
				SetRect(&rc, 1200, 315, 1205, 165);
				m_pFont->DrawText(NULL, cGreenMushroom,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(0.f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				SetRect(&rc, 1200, 315, 1205, 165);
				m_pFont->DrawText(NULL, cGreenMushroom,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, 1.0f));
			}

			SetRect(&rc, 1213, 315, 1218, 165);
			m_pFont->DrawText(NULL, cCountMushroom,
				-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));



		}
	}



		else if (Questinstance->Get_QuestNum() == 5)
		{
			TCHAR cQuest[128];
			TCHAR cGAS[50];
			TCHAR cCountSlime[15];

			_uint iGAS = Questinstance->Set_GAS();

			wsprintf(cQuest, TEXT("[�����Ͼ�] ����� ���� ������ óġ\n") TEXT(" ��.��.��"));
			wsprintf(cGAS, TEXT("	%d"), iGAS);
			wsprintf(cCountSlime, TEXT("		/ 1\n"));



			if (Questinstance->Set_QuestState() == 1 || Questinstance->Set_QuestState() == 2)
			{
				SetRect(&rc, 1100, 270, 1200, 150);
				m_pFont->DrawText(NULL, cQuest,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				if (iGAS == 11)
				{
					SetRect(&rc, 1165, 285, 1205, 165);
					m_pFont->DrawText(NULL, cGAS,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(0.f, 1.0f, 1.0f, 1.0f));
				}
				else
				{
					SetRect(&rc, 1165, 285, 1205, 165);
					m_pFont->DrawText(NULL, cGAS,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, 1.0f));
				}

				SetRect(&rc, 1178, 285, 1218, 165);
				m_pFont->DrawText(NULL, cCountSlime,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			}
		}


		else if (Questinstance->Get_QuestNum() == 6)
		{
			TCHAR cQuest[128];
			TCHAR cGAS[50];
			TCHAR cCountSlime[15];

			_uint iGAS = Questinstance->Set_GAS();

			wsprintf(cQuest, TEXT("[����] ���������� óġ\n") TEXT(" ���� ������"));
			wsprintf(cGAS, TEXT("	%d"), iGAS);
			wsprintf(cCountSlime, TEXT("	/ 1\n"));



			if (Questinstance->Set_QuestState() == 1 || Questinstance->Set_QuestState() == 2)
			{
				SetRect(&rc, 1100, 270, 1200, 150);
				m_pFont->DrawText(NULL, cQuest,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				if (iGAS == 11)
				{
					SetRect(&rc, 1165, 285, 1205, 165);
					m_pFont->DrawText(NULL, cGAS,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(0.f, 1.0f, 1.0f, 1.0f));
				}
				else
				{
					SetRect(&rc, 1165, 285, 1205, 165);
					m_pFont->DrawText(NULL, cGAS,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, 1.0f));
				}

				SetRect(&rc, 1178, 285, 1218, 165);
				m_pFont->DrawText(NULL, cCountSlime,
					-1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			}
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
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Quest"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
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

