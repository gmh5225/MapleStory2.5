#include "stdafx.h"
#include "..\Public\Chat.h"
#include "GameInstance.h"
#include "QuestManager.h"
#include "SkillManager.h"
#include "InvenManager.h"
#include "ItemInfo.h"
#include "CutSceneManager.h"

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

	// npcä���� �������� ä���� ī��Ʈ�� ������Ŵ
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



	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_ComponentPtr(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

	_float3 vPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);

	if (fabs(m_pTransformCom->Get_State(CTransform::STATE_POSITION).x - vPlayerPos.x) < 2.f && fabs(m_pTransformCom->Get_State(CTransform::STATE_POSITION).z - vPlayerPos.z) < 2.f)
	{

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
					wsprintf(cChat, TEXT("��ν�ź"));
					SetRect(&rc, 350, 500, 0, 0);
					m_pFont->DrawText(NULL, cChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.45f, 0.f, 1.f));


					if (m_iRandom == 0)
					{
						wsprintf(m_cNPCChat, TEXT("�ڳ� ������ �Ȱ���?"));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else if (m_iRandom == 1)
					{
						wsprintf(m_cNPCChat, TEXT("����..�� ���������� ������ �Ƿڴ� 10���̸�.."));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}


					else if (m_iRandom == 2)
					{
						wsprintf(m_cNPCChat, TEXT("��..."));
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
			// ����Ʈ�Ŵ����� ���� ������ ä�ð��� TRUE�̸� ä���� �׸�, ���͸� ������ ����Ʈ ������ �������� �ٲٰ� ä�ð��� FALSE�� ����
			if (m_bChat && pInstance->Set_QuestState() == 0)
			{
				Bind_Animation();
				m_pVIBufferCom->Render();

				// ���� �ִϸ��̼��� �� �׷�����
				if (!m_bCountCheck)
				{
					m_bCountCheck2 = true;
					TCHAR cChat[128];
					_tchar m_cNPCChat[128];

					wsprintf(cChat, TEXT("��ν�ź"));
					SetRect(&rc, 350, 500, 0, 0);
					m_pFont->DrawText(NULL, cChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.45f, 0.f, 1.f));

					if (CGameInstance::Get_Instance()->Key_Down(DIKEYBOARD_SPACE))
						m_iChatProgress++;

					if (m_iChatProgress == 0)
					{
						wsprintf(m_cNPCChat, TEXT("����..��ٸ��� �־���, ���� �� ��� ��翩."));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else if (m_iChatProgress == 1)
					{
						wsprintf(m_cNPCChat, TEXT("�ڳ׸� ã�� �־��µ� �ݹ� ���־�����."));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else if (m_iChatProgress == 2)
					{
						wsprintf(m_cNPCChat, TEXT("��� ������ ū ������ �����."));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else if (m_iChatProgress == 3)
					{
						wsprintf(m_cNPCChat, TEXT("�ڳ׵� �˴ٽ��� �츮 ��׽ý� �ֹε���\n������ ��Ͽ� ��Ȱ�ϰ� �ֳ�"));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else if (m_iChatProgress == 4)
					{
						wsprintf(m_cNPCChat, TEXT("��׽ý��� �̷����� ���Ͱ� ���������� �׵��� �����̵��� ����\n���۹��� � ���ĸԴ°� �����ϰ�� ���� ���忡 ū ���ش� ������."));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else if (m_iChatProgress == 5)
					{
						wsprintf(m_cNPCChat, TEXT("�׷��� ��Ȳ���� �༮���� ���忡 �������� �ִٴ°��� �˾����ȴ���,\n�����ֺ��� ��ü�� ��Ÿ������ ���۹��� ���� ���ĸ԰� ��ġ�°� �ƴѰ�!"));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else if (m_iChatProgress == 6)
					{
						wsprintf(m_cNPCChat, TEXT("�̴�� ���ٰ� ��� ���� �װ� ���ž�"));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else
					{
						wsprintf(m_cNPCChat, TEXT("�׷��� �ð��� �����ٸ� �ڳװ� ��Ȳ�������� ȥ�������� �ϴµ�..\n�����ϰڴ°�?"));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}
				}

				if ((GetKeyState(VK_RETURN) & 0x8000))
				{
					pInstance->QuestProgress();
					pInstance->Check_End_Quest();
					m_bCountCheck = false;
					m_fCount = 0;
				}
			}

			if (m_bChat && pInstance->Set_QuestState() == 2)
			{
				m_bCountCheck = true;
				Bind_Animation();
				m_pVIBufferCom->Render();

				if (!m_bCountCheck)
				{
					m_bCountCheck2 = true;
					TCHAR cChat[128];
					_tchar m_cNPCChat[128];
					wsprintf(cChat, TEXT("��ν�ź"));
					SetRect(&rc, 350, 500, 0, 0);
					m_pFont->DrawText(NULL, cChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.45f, 0.f, 1.f));

					wsprintf(m_cNPCChat, TEXT("���� �� ��Ҵ°�?\n����!"));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				}

				if (GetKeyState(VK_RETURN) & 0x8000)
				{
					m_fCount = 0;
					pInstance->QuestPrepare();
					pInstance->Check_End_Quest();
					pInstance->Reset_Hunt();
					CQuestManager::Get_Instance()->Set_Second();
					CSkillManager::Get_Instance()->Set_SkillPoint(3);
					m_iChatProgress = 10;
				}
			}
		}

		else if (pInstance->Get_QuestNum() == 2)
		{
			// ����Ʈ�Ŵ����� ���� ������ ä�ð��� TRUE�̸� ä���� �׸�, ���͸� ������ ����Ʈ ������ �������� �ٲٰ� ä�ð��� FALSE�� ����
			if (m_bChat && pInstance->Set_QuestState() == 0)
			{
				m_bCountCheck = true;
				Bind_Animation();
				m_pVIBufferCom->Render();

				if (!m_bCountCheck)
				{
					m_bCountCheck2 = true;
					TCHAR cChat[128];
					_tchar m_cNPCChat[128];

					wsprintf(cChat, TEXT("��ν�ź"));
					SetRect(&rc, 350, 500, 0, 0);
					m_pFont->DrawText(NULL, cChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.45f, 0.f, 1.f));

					if (CGameInstance::Get_Instance()->Key_Down(DIKEYBOARD_SPACE))
						m_iChatProgress++;

					if (m_iChatProgress == 10)
					{
						wsprintf(m_cNPCChat, TEXT("��, �ڳױ���.. ��Ȳ������ ����ذ� ���� ������,\n������ ������ ���� �ƾ�."));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else if (m_iChatProgress == 11)
					{
						wsprintf(m_cNPCChat, TEXT("...�׷��� Ȥ�� �ڳ� �ð� �� �ֳ�?\n���������� ��Ź�ϰ� ������ �־.."));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else if (m_iChatProgress == 12)
					{
						wsprintf(m_cNPCChat, TEXT("��� �����ְ� �� �Ƴ��� �ֹֺ��� �����ε�,\n������ �� �ְ� �; ���̾�"));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else if (m_iChatProgress == 13)
					{
						wsprintf(m_cNPCChat, TEXT("�� �̷��� �غ��� ���\n���� �ڳװ� �� �� ���� �ʰڳ�"));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else
					{
						wsprintf(m_cNPCChat, TEXT("Ȥ�� ������ �ٸ��� �� ã�ƴ� �� �� �ְڳ�?"));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}
				}
				if ((GetKeyState(VK_RETURN) & 0x8000))
				{
					pInstance->QuestProgress();
					pInstance->Check_End_Quest();
					m_bCountCheck = false;
					m_fCount = 0;
				}
			}

			if (m_bChat && pInstance->Set_QuestState() == 2)
			{
				m_bCountCheck = true;
				Bind_Animation();
				m_pVIBufferCom->Render();

				if (!m_bCountCheck)
				{
					m_bCountCheck2 = true;
					TCHAR cChat[128];
					_tchar m_cNPCChat[128];
					wsprintf(cChat, TEXT("��ν�ź"));
					SetRect(&rc, 350, 500, 0, 0);
					m_pFont->DrawText(NULL, cChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.45f, 0.f, 1.f));

					wsprintf(m_cNPCChat, TEXT("...��� ���� ����� ������ �̷���?\nũ�� �ƹ�ư ����!"));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				}

				if (GetKeyState(VK_RETURN) & 0x8000)
				{
					m_fCount = 0;
					m_bCountCheck = false;
					pInstance->QuestPrepare();
					pInstance->Check_End_Quest();
					pInstance->Reset_Hunt();
					CQuestManager::Get_Instance()->Set_Third();
					CSkillManager::Get_Instance()->Set_SkillPoint(3);
					m_iChatProgress = 20;

					CItemInfo* RedSnailInfo = CInvenManager::Get_Instance()->Get_ItemInfo(L"RedSnailInfo", CInvenManager::TYPE_STUFF);
					CItemInfo* BlueSnailInfo = CInvenManager::Get_Instance()->Get_ItemInfo(L"BlueSnailInfo", CInvenManager::TYPE_STUFF);
					CItemInfo* RibbonPigInfo = CInvenManager::Get_Instance()->Get_ItemInfo(L"RibbonPigInfo", CInvenManager::TYPE_STUFF);
					RedSnailInfo->Set_NowNum(0);
					BlueSnailInfo->Set_NowNum(0);
					RibbonPigInfo->Set_NowNum(0);
				}
			}
		}
		else if (pInstance->Get_QuestNum() == 3)
		{
			// ����Ʈ�Ŵ����� ���� ������ ä�ð��� TRUE�̸� ä���� �׸�, ���͸� ������ ����Ʈ ������ �������� �ٲٰ� ä�ð��� FALSE�� ����
			if (m_bChat && pInstance->Set_QuestState() == 0)
			{
				m_bCountCheck = true;
				Bind_Animation();
				m_pVIBufferCom->Render();

				if (!m_bCountCheck)
				{
					m_bCountCheck2 = true;
					TCHAR cChat[128];
					_tchar m_cNPCChat[128];

					wsprintf(cChat, TEXT("��ν�ź"));
					SetRect(&rc, 350, 500, 0, 0);
					m_pFont->DrawText(NULL, cChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.45f, 0.f, 1.f));

					if (CGameInstance::Get_Instance()->Key_Down(DIKEYBOARD_SPACE))
						m_iChatProgress++;

					if (m_iChatProgress == 20)
					{
						wsprintf(m_cNPCChat, TEXT("��, ��翩 �������̳�,\n������ ������ ���� ������. ������ �� �����ϴ���."));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else if (m_iChatProgress == 21)
					{
						wsprintf(m_cNPCChat, TEXT("���� ��� �ڳ� ���� �ַ���\n������ �����Ͼƿ� �ٳ������ �߾���."));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else if (m_iChatProgress == 22)
					{
						wsprintf(m_cNPCChat, TEXT("�ڳ׸� �����ϸ� ��� �������� �������µ�...�̰� ����!\n�����Ͼ� ���� �ϳ��ۿ� ���� ���� ���� ���� �����ִ°� �ƴѰ�!"));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else if (m_iChatProgress == 23)
					{
						wsprintf(m_cNPCChat, TEXT("�׷��� ��¿ �� ���� �׳� ���ƿԴٳ�...�̷��� ������ ���� ����.\n���� ���� ����� ����� ������?\n ���� ������� ��⿣ ũ�� ��ĥ���� �и��ѵ�..."));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else
					{
						wsprintf(m_cNPCChat, TEXT("...�ڳװ� ����ְڴٰ�? �̷��� ���� ����!\n���� ����! �ϰ� �ְڳ�!"));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}
				}
				if ((GetKeyState(VK_RETURN) & 0x8000))
				{
					m_fCount = 0;
					pInstance->QuestProgress();
					pInstance->Check_End_Quest();
				}
			}

			if (m_bChat && pInstance->Set_QuestState() == 2)
			{
				m_bCountCheck = true;
				Bind_Animation();
				m_pVIBufferCom->Render();

				if (!m_bCountCheck)
				{
					m_bCountCheck2 = true;
					TCHAR cChat[128];
					_tchar m_cNPCChat[128];
					wsprintf(cChat, TEXT("��ν�ź"));
					SetRect(&rc, 350, 500, 0, 0);
					m_pFont->DrawText(NULL, cChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.45f, 0.f, 1.f));

					wsprintf(m_cNPCChat, TEXT("�ƴ� �̷��� ����!�ڳ״� ���� ��׽ý��� �����ϼ�!\n���� ����!"));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				}
				if (GetKeyState(VK_RETURN) & 0x8000)
				{
					{
						m_fCount = 0;
						m_bCountCheck = false;
						pInstance->QuestPrepare();
						pInstance->Check_End_Quest();
						pInstance->Reset_Hunt();
						CQuestManager::Get_Instance()->Set_Fourth();
						CSkillManager::Get_Instance()->Set_SkillPoint(3);
						m_iChatProgress = 30;
					}
				}

			}
		}


		else if (pInstance->Get_QuestNum() == 4)
		{
			// ����Ʈ�Ŵ����� ���� ������ ä�ð��� TRUE�̸� ä���� �׸�, ���͸� ������ ����Ʈ ������ �������� �ٲٰ� ä�ð��� FALSE�� ����
			if (m_bChat && pInstance->Set_QuestState() == 0)
			{
				m_bCountCheck = true;
				Bind_Animation();
				m_pVIBufferCom->Render();

				if (!m_bCountCheck)
				{
					m_bCountCheck2 = true;
					TCHAR cChat[128];
					_tchar m_cNPCChat[128];

					wsprintf(cChat, TEXT("��ν�ź"));
					SetRect(&rc, 350, 500, 0, 0);
					m_pFont->DrawText(NULL, cChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.45f, 0.f, 1.f));

					if (CGameInstance::Get_Instance()->Key_Down(DIKEYBOARD_SPACE))
						m_iChatProgress++;

					if (m_iChatProgress == 30)
					{
						wsprintf(m_cNPCChat, TEXT("����.....����! ���� ��� ���纸��!\n�ڳ� �� ���� ���� �ɾ �� ������ ���ϳ�?\n�Ͱ� �� �ȵ鸰�ٰ�....? �̰� �������̶� �ؾ߰ڱ���"));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else if (m_iChatProgress == 31)
					{
						wsprintf(m_cNPCChat, TEXT("�׷��� �ϴ� ���ε� �� �ڳ׿��� ��Ź�� ���� ���� ������.\n�̹����� ����� �ѱ׸��� ������ְ� �; ���ϼ�. ��ٷ�����."));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else if (m_iChatProgress == 32)
					{
						wsprintf(m_cNPCChat, TEXT("��..�̰� ��� �״���....���, ��ᰡ ���� ���ڶ�! �̰� ��¼��!\n....Ȥ�� �ڳ� ���� �ٻ۰�?"));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}

					else
					{
						wsprintf(m_cNPCChat, TEXT("�ٻ��� �ʴٸ� ������ ��Ḧ ���� ���ش� �� �� �ְڳ�?\n����� �� �� �ؼ� 2�κи�....���� �����ϰڳ�!"));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					}
				}
				if ((GetKeyState(VK_RETURN) & 0x8000))
				{
					m_fCount = 0;
					pInstance->QuestProgress();
					pInstance->Check_End_Quest();
				}
			}

			if (m_bChat && pInstance->Set_QuestState() == 2)
			{
				m_bCountCheck = true;
				Bind_Animation();
				m_pVIBufferCom->Render();

				if (!m_bCountCheck)
				{
					m_bCountCheck2 = true;
					TCHAR cChat[128];
					_tchar m_cNPCChat[128];
					wsprintf(cChat, TEXT("��ν�ź"));
					SetRect(&rc, 350, 500, 0, 0);
					m_pFont->DrawText(NULL, cChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.45f, 0.f, 1.f));

					wsprintf(m_cNPCChat, TEXT("��Ḧ �� ��ƿԱ���! �� �ݹ� ������ְڳ�!\n�� �������!���� ���� ���� �Ծ��...\n��..����! ����..."));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				}
				if (GetKeyState(VK_RETURN) & 0x8000)
				{
					m_fCount = 0;
					pInstance->QuestPrepare();
					pInstance->Check_End_Quest();
					pInstance->Reset_Hunt();
					CQuestManager::Get_Instance()->Set_Fifth();
					CSkillManager::Get_Instance()->Set_SkillPoint(3);

					CItemInfo* SlimeInfo = CInvenManager::Get_Instance()->Get_ItemInfo(L"SlimeInfo", CInvenManager::TYPE_STUFF);
					CItemInfo* GoStumpInfo = CInvenManager::Get_Instance()->Get_ItemInfo(L"GoStumpInfo", CInvenManager::TYPE_STUFF);
					CItemInfo* GreenMushroomInfo = CInvenManager::Get_Instance()->Get_ItemInfo(L"GreenMushroomInfo", CInvenManager::TYPE_STUFF);

					SlimeInfo->Set_NowNum(0);
					GoStumpInfo->Set_NowNum(0);
					GreenMushroomInfo->Set_NowNum(0);
					CCutSceneManager::Get_Instance()->Start_Enter_GASHenesys();
				}
			}
		}



		else if (pInstance->Get_QuestNum() == 5)
		{
			// ����Ʈ�Ŵ����� ���� ������ ä�ð��� TRUE�̸� ä���� �׸�, ���͸� ������ ����Ʈ ������ �������� �ٲٰ� ä�ð��� FALSE�� ����
			if (m_bChat && pInstance->Set_QuestState() == 0)
			{
				m_bCountCheck = true;
				{
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
				else
				{
					m_pTextureCom->Bind_Texture(17);
					m_bCountCheck = false;
				}
				}
				m_pVIBufferCom->Render();

				if (!m_bCountCheck)
				{
					m_bCountCheck2 = true;
					TCHAR cChat[128];
					_tchar m_cNPCChat[128];

					wsprintf(cChat, TEXT("��"));
					SetRect(&rc, 350, 500, 0, 0);
					m_pFont->DrawText(NULL, cChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.45f, 0.f, 1.f));

						wsprintf(m_cNPCChat, TEXT("(... ��ν�ź�� ��ġ�� �� ����. �����ַ� ����.)"));
						SetRect(&rc, 350, 530, 0, 0);
						m_pFont->DrawText(NULL, m_cNPCChat,
							-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
					

				}
				if ((GetKeyState(VK_RETURN) & 0x8000))
				{
					m_fCount = 0;
					pInstance->QuestProgress();
					pInstance->Check_End_Quest();
				}
			}

			if (m_bChat && pInstance->Set_QuestState() == 2)
			{
				m_bCountCheck = true;
				Bind_Animation();
				m_pVIBufferCom->Render();

				if (!m_bCountCheck)
				{
					m_bCountCheck2 = true;
					TCHAR cChat[128];
					_tchar m_cNPCChat[128];
					wsprintf(cChat, TEXT("��ν�ź"));
					SetRect(&rc, 350, 500, 0, 0);
					m_pFont->DrawText(NULL, cChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.45f, 0.f, 1.f));

					wsprintf(m_cNPCChat, TEXT("�����༭ ���� ����!"));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				}
				if (GetKeyState(VK_RETURN) & 0x8000)
				{
					m_fCount = 0;
					pInstance->QuestPrepare();
					pInstance->Check_End_Quest();
					pInstance->Reset_Hunt();
					CSkillManager::Get_Instance()->Set_SkillPoint(3);
					CQuestManager::Get_Instance()->Set_Sixth();

					CCutSceneManager::Get_Instance()->Start_Enter_InitDHenesys();
				}
			}
		}

		else if (pInstance->Get_QuestNum() == 6)
		{
			// ����Ʈ�Ŵ����� ���� ������ ä�ð��� TRUE�̸� ä���� �׸�, ���͸� ������ ����Ʈ ������ �������� �ٲٰ� ä�ð��� FALSE�� ����
			if (m_bChat && pInstance->Set_QuestState() == 0)
			{
				m_bCountCheck = true;
				{
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
					else
					{
						m_pTextureCom->Bind_Texture(17);
						m_bCountCheck = false;
					}
				}
				m_pVIBufferCom->Render();

				if (!m_bCountCheck)
				{
					m_bCountCheck2 = true;
					TCHAR cChat[128];
					_tchar m_cNPCChat[128];

					wsprintf(cChat, TEXT("��"));
					SetRect(&rc, 350, 500, 0, 0);
					m_pFont->DrawText(NULL, cChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.45f, 0.f, 1.f));

					if (CGameInstance::Get_Instance()->Key_Down(DIKEYBOARD_SPACE))
						m_iChatProgress++;

					wsprintf(m_cNPCChat, TEXT("������ ���� �ν�����...���� ������� �����Ͼ� ������ ����ģ �� ����.\n���� �濡 ������ �����ϴ� ���͵��� óġ����."));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

				}
				if ((GetKeyState(VK_RETURN) & 0x8000))
				{
					m_fCount = 0;
					pInstance->QuestProgress();
					pInstance->Check_End_Quest();
				}
			}

			if (m_bChat && pInstance->Set_QuestState() == 2)
			{
				m_bCountCheck = true;
				Bind_Animation();
				m_pVIBufferCom->Render();

				if (!m_bCountCheck)
				{
					m_bCountCheck2 = true;
					TCHAR cChat[128];
					_tchar m_cNPCChat[128];
					wsprintf(cChat, TEXT("��"));
					SetRect(&rc, 350, 500, 0, 0);
					m_pFont->DrawText(NULL, cChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.45f, 0.f, 1.f));

					wsprintf(m_cNPCChat, TEXT("���� ������..."));
					SetRect(&rc, 350, 530, 0, 0);
					m_pFont->DrawText(NULL, m_cNPCChat,
						-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
				}
				if (GetKeyState(VK_RETURN) & 0x8000)
				{
					m_fCount = 0;
					pInstance->QuestClear();
					pInstance->Check_End_Quest();
					pInstance->Reset_Hunt();
					CSkillManager::Get_Instance()->Set_SkillPoint(3);
					CQuestManager::Get_Instance()->Set_Sixth();
				}
			}
		}
	}


	Safe_Release(pGameInstance);

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

