#include "stdafx.h"
#include "..\Public\DomiScreen.h"

#include "GameInstance.h"


CDomiScreen::CDomiScreen(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CDomiScreen::CDomiScreen(const CDomiScreen& rhs)
	: CUI(rhs)
{
}


HRESULT CDomiScreen::Initialize_Prototype()
{
	__super::Initialize_Prototype();


	return S_OK;
}

HRESULT CDomiScreen::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_UIInfo.fSizeX = 1280;
	m_UIInfo.fSizeY = 720;
	m_UIInfo.fX = g_iWinSizeX*0.5f;
	m_UIInfo.fY = g_iWinSizeY*0.5f;
	// m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_UIInfo.fX - g_iWinSizeX * 0.5f, -m_UIInfo.fY + g_iWinSizeY * 0.5f, 0.f));
	m_iTexturenum = 0;

	__super::Initialize(pArg);

	m_bRender = false;

	D3DXCreateFont(m_pGraphic_Device, 30, 0, FW_BOLD, 1, TRUE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Arial"), &m_pFont);

	return S_OK;
}

void CDomiScreen::OnCutScreen()
{
	m_bCutScreen = true;
	m_iCount = 0;
	m_fTimeAcc = 0.f;

	m_bRender = true;
}
void CDomiScreen::OffCutScreen()
{
	m_bCutScreen = false;
	m_iCount = 18;
	m_fTimeAcc = 0.f;

	m_bRender = true;
}


void CDomiScreen::Tick(_float fTimeDelta)
{

	OnOffTick(fTimeDelta);

	if (m_bStartTalk)
		BlackMageTalkTick(fTimeDelta);


}

void CDomiScreen::LateTick(_float fTimeDelta)
{
	if (!m_bRender)
		return;

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);
}

HRESULT CDomiScreen::Render()
{
	if (!m_bRender)
		return S_OK;



	m_pTransformCom->Bind_WorldMatrix();
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	if (FAILED(m_pTextureCom->Bind_Texture(m_iCount)))
		return E_FAIL;

	Set_RenderState();

	m_pVIBufferCom->Render();

	Reset_RenderState();


	if(m_bStartTalk)
		BlackMageTalk();





	return S_OK;
}



HRESULT CDomiScreen::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components()))
		return E_FAIL;


	/* For.Com_Texture */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Texture_DomiScreen"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;



	return S_OK;
}

void CDomiScreen::OnOffTick(_float fTimeDelta)
{

	if (m_bCutScreen)
	{

		m_fTimeAcc += fTimeDelta;

		if (0.1f < m_fTimeAcc)
		{
			++m_iCount;
			m_fTimeAcc = 0.f;
			if (17 < m_iCount)
			{
				m_iCount = 17;
				m_bStartTalk = true;
			}

		}

	}
	else
	{
		m_fTimeAcc += fTimeDelta;

		if (0.1f < m_fTimeAcc)
		{
			++m_iCount;
			m_fTimeAcc = 0.f;
			if (32 < m_iCount)
			{
				m_iCount = 32;
				m_bRender = false;
			}
		}
	}

}

void CDomiScreen::BlackMageTalkTick(_float fTimeDelta)
{
	m_fTalkTimeAcc += fTimeDelta;

	if (0.1f < m_fTalkTimeAcc)
	{
		++m_iTalkCount;

		if (26 < m_iTalkCount)
			m_bStartTalk = false;

		m_fTalkTimeAcc = 0.f;
	}

}

void CDomiScreen::BlackMageTalk()
{
	RECT rc;
	TCHAR cChat[128] = {0};

	switch (m_iTalkCount)
	{
	case 0:
	{

	}
	case 1:
	{
		wsprintf(cChat, TEXT("��"));
		SetRect(&rc, g_iWinSizeX*0.5f - 60.f, g_iWinSizeY*0.5f, 0, 0);
		m_pFont->DrawText(NULL, cChat,
			-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, .1f));

	}
		break;
	case 2:
	{
		wsprintf(cChat, TEXT("����"));
		SetRect(&rc, g_iWinSizeX*0.5f - 60.f, g_iWinSizeY*0.5f, 0, 0);
		m_pFont->DrawText(NULL, cChat,
			-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, .2f));
	}

		break;
	case 3:
	{
		wsprintf(cChat, TEXT("������"));
		SetRect(&rc, g_iWinSizeX*0.5f - 60.f, g_iWinSizeY*0.5f, 0, 0);
		m_pFont->DrawText(NULL, cChat,
			-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, .3f));
	}
		break;
	case 4:
	{
		wsprintf(cChat, TEXT("�����ڿ�"));
		SetRect(&rc, g_iWinSizeX*0.5f - 60.f, g_iWinSizeY*0.5f, 0, 0);
		m_pFont->DrawText(NULL, cChat,
			-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, .4f));
	}
		break;
	case 5:
	{
		wsprintf(cChat, TEXT("�����ڿ� ��"));
		SetRect(&rc, g_iWinSizeX*0.5f - 60.f, g_iWinSizeY*0.5f, 0, 0);
		m_pFont->DrawText(NULL, cChat,
			-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, .5f));
	}
		break;
	case 6:
	{
		wsprintf(cChat, TEXT("�����ڿ� ���"));
		SetRect(&rc, g_iWinSizeX*0.5f - 60.f, g_iWinSizeY*0.5f, 0, 0);
		m_pFont->DrawText(NULL, cChat,
			-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, .6f));
	}
		break;
	case 7:
	{
		wsprintf(cChat, TEXT("�����ڿ� �����"));
		SetRect(&rc, g_iWinSizeX*0.5f - 60.f, g_iWinSizeY*0.5f, 0, 0);
		m_pFont->DrawText(NULL, cChat,
			-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, .7f));
	}
		break;
	case 8:
	{
		wsprintf(cChat, TEXT("�����ڿ� ����� ��"));
		SetRect(&rc, g_iWinSizeX*0.5f - 60.f, g_iWinSizeY*0.5f, 0, 0);
		m_pFont->DrawText(NULL, cChat,
			-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, .8f));
	}
		break;
	case 9:
	{
		wsprintf(cChat, TEXT("�����ڿ� ����� �ϼ�"));
		SetRect(&rc, g_iWinSizeX*0.5f - 60.f, g_iWinSizeY*0.5f, 0, 0);
		m_pFont->DrawText(NULL, cChat,
			-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, .9f));
	}
		break;
	case 10:
	{
		wsprintf(cChat, TEXT("�����ڿ� ����� �ϼ���"));
		SetRect(&rc, g_iWinSizeX*0.5f - 60.f, g_iWinSizeY*0.5f, 0, 0);
		m_pFont->DrawText(NULL, cChat,
			-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, 1.f));
	}
		break;
	case 11:
	{
		wsprintf(cChat, TEXT("�����ڿ� ����� �ϼ��� ��"));
		SetRect(&rc, g_iWinSizeX*0.5f - 60.f, g_iWinSizeY*0.5f, 0, 0);
		m_pFont->DrawText(NULL, cChat,
			-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, 1.));
	}
		break;
	case 12:
	{
		wsprintf(cChat, TEXT("�����ڿ� ����� �ϼ��� ����"));
		SetRect(&rc, g_iWinSizeX*0.5f - 60.f, g_iWinSizeY*0.5f, 0, 0);
		m_pFont->DrawText(NULL, cChat,
			-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, 1.));
	}
		break;
	case 13:
	{
		wsprintf(cChat, TEXT("�����ڿ� ����� �ϼ��� ����."));
		SetRect(&rc, g_iWinSizeX*0.5f - 60.f, g_iWinSizeY*0.5f, 0, 0);
		m_pFont->DrawText(NULL, cChat,
			-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, 1.));
	}
		break;
	default:
	{
		//wsprintf(cChat, TEXT("�����ڿ� ����� �ϼ��� ����."));
		//SetRect(&rc, g_iWinSizeX*0.5f - 61.f, g_iWinSizeY*0.5f, 0, 0);
		//m_pFont->DrawText(NULL, cChat,
		//	-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 1.f, 1.f, .5f));
		if (24 > m_iTalkCount)
		{
			wsprintf(cChat, TEXT("�����ڿ� ����� �ϼ��� ����."));
			SetRect(&rc, g_iWinSizeX*0.5f - 60.f, g_iWinSizeY*0.5f, 0, 0);
			m_pFont->DrawText(NULL, cChat,
				-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, 1.f));

		}
	}
		break;
	}

	if (24 < m_iTalkCount)
	{
		wsprintf(cChat, TEXT("�����ڿ� ����� �ϼ��� ����."));
		SetRect(&rc, g_iWinSizeX*0.5f - 60.f, g_iWinSizeY*0.5f, 0, 0);
		m_pFont->DrawText(NULL, cChat,
			-1, &rc, DT_NOCLIP, D3DXCOLOR(1.f, 0.f, 0.f, m_fTempA));
		m_fTempA -= 0.1f;
	}
}

CDomiScreen* CDomiScreen::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CDomiScreen*		pInstance = new CDomiScreen(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CCutScreen"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CDomiScreen::Clone(void * pArg)
{
	CDomiScreen*		pInstance = new CDomiScreen(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CCutScreen"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CDomiScreen::Free()
{
	__super::Free();
}
