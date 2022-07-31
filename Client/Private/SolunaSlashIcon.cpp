#include "stdafx.h"
#include "..\Public\SolunaSlashIcon.h"
#include "GameInstance.h"
#include "SkillManager.h"
#include "SolunaSlashInfo.h"


CSolunaSlashIcon::CSolunaSlashIcon(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CSolunaSlashIcon::CSolunaSlashIcon(const CSolunaSlashIcon& rhs)
	: CUI(rhs)
{
}


HRESULT CSolunaSlashIcon::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CSolunaSlashIcon::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	memcpy(&m_UIInfo, pArg, sizeof(UIINFO));

	__super::Initialize(pArg);
	m_iTexturenum = 0;
	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();

	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_SolunaSlashIcon"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	D3DXCreateFont(m_pGraphic_Device, 13, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"돋움체", &m_NoticeFont);

	pSkillInstance->Add_SkillFrameImage(this);

	return S_OK;
}

void CSolunaSlashIcon::Tick(_float fTimeDelta)
{
	CGameInstance* pInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pInstance);

	if (pInstance->Key_Down(DIK_K))
	{
		m_bRender = !m_bRender;
	}

	if (pInstance->Mouse_Up(DIMK_LBUTTON))
	{

	}
	Check_Collision(DIMK_LBUTTON);

	Safe_Release(pInstance);
}

void CSolunaSlashIcon::LateTick(_float fTimeDelta)
{


	SetRect(&m_RectUI, m_UIInfo.fX - m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY - m_UIInfo.fSizeY * 0.5f, m_UIInfo.fX + m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY + m_UIInfo.fSizeY * 0.5f);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_UIInfo.fX - g_iWinSizeX * 0.5f, -m_UIInfo.fY + g_iWinSizeY * 0.5f, 0.f));

	Change_Texture();
	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();
	if (m_bRender && pSkillInstance->Get_SkillGrade() == CSkillManager::GRADE_FIRST)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);

}

HRESULT CSolunaSlashIcon::Render()
{
	if (FAILED(m_pTextureCom->Bind_Texture(m_iTexturenum)))
		return E_FAIL;

	m_pTransformCom->Bind_WorldMatrix();
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	Set_RenderState();

	m_pVIBufferCom->Render();

	Reset_RenderState();


	if (m_eCollision == TYPE_ON)
	{
		RECT SolunaSlashNotice;
		SetRect(&SolunaSlashNotice, m_UIInfo.fX, m_UIInfo.fY, 0, 0);
		m_NoticeFont->DrawText(NULL, L"스킬 설명 테스트\n타입 : 대쉬\n 소모 마나 : 30\n이동 거리 : 300px", -1, &SolunaSlashNotice, DT_NOCLIP, D3DXCOLOR(0.f, 0.f, 255.0f, 1.0f));
	}

	return S_OK;
}

void CSolunaSlashIcon::Change_Texture()
{
	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();
	if (pSkillInstance->Get_SkillInfo(L"SolunaSlashInfo", CSkillManager::GRADE_BEGENNER)->Get_SkillLevel() < 1)
		m_iTexturenum = 0;
	else
		m_iTexturenum = 1;



}

CSolunaSlashIcon* CSolunaSlashIcon::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSolunaSlashIcon*		pInstance = new CSolunaSlashIcon(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CSolunaSlashIcon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CSolunaSlashIcon::Clone(void * pArg)
{
	CSolunaSlashIcon*		pInstance = new CSolunaSlashIcon(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CSolunaSlashIcon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSolunaSlashIcon::Free()
{
	__super::Free();

}
