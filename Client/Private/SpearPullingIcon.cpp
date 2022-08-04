#include "stdafx.h"
#include "..\Public\SpearPullingIcon.h"
#include "GameInstance.h"
#include "SkillManager.h"
#include "MouseManager.h"


CSpearPullingIcon::CSpearPullingIcon(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CSpearPullingIcon::CSpearPullingIcon(const CSpearPullingIcon& rhs)
	: CUI(rhs)
{
}


HRESULT CSpearPullingIcon::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CSpearPullingIcon::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	memcpy(&m_UIInfo, pArg, sizeof(UIINFO));

	__super::Initialize(pArg);
	m_iTexturenum = 0;
	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();

	m_pSkillInfo = (CSpearPullingInfo*)pSkillInstance->Get_SkillInfo(L"SpearPullingInfo", CSkillManager::GRADE_SECOND);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Texture_SpearPullingIcon"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	D3DXCreateFont(m_pGraphic_Device, 13, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"����ü", &m_NoticeFont);

	pSkillInstance->Add_SkillFrameImage(this);

	return S_OK;
}

void CSpearPullingIcon::Tick(_float fTimeDelta)
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

void CSpearPullingIcon::LateTick(_float fTimeDelta)
{
	SetRect(&m_RectUI, m_UIInfo.fX - m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY - m_UIInfo.fSizeY * 0.5f, m_UIInfo.fX + m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY + m_UIInfo.fSizeY * 0.5f);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_UIInfo.fX - g_iWinSizeX * 0.5f, -m_UIInfo.fY + g_iWinSizeY * 0.5f, 0.f));

	Change_Texture();
	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();
	if (m_bRender&& pSkillInstance->Get_SkillGrade() == CSkillManager::GRADE_SECOND)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);

}

HRESULT CSpearPullingIcon::Render()
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
		RECT SunCrossNotice;
		SetRect(&SunCrossNotice, m_UIInfo.fX, m_UIInfo.fY, 0, 0);
		m_NoticeFont->DrawText(NULL, m_pSkillInfo->Get_SkillNotice(), -1, &SunCrossNotice, DT_NOCLIP, D3DXCOLOR(0.f, 0.f, 255.0f, 1.0f));
	}

	return S_OK;
}

void CSpearPullingIcon::Change_Texture()
{
	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();
	if (pSkillInstance->Get_SkillInfo(L"SpearPullingInfo", CSkillManager::GRADE_SECOND)->Get_SkillLevel() < 1)
		m_iTexturenum = 0;
	else
		m_iTexturenum = 1;

	CMouseManager* pMouseInstance = CMouseManager::Get_Instance();
	if (m_eCollision == TYPE_DOWN && m_pSkillInfo->Get_SkillLevel() != 0 && pSkillInstance->Get_SkillGrade() == CSkillManager::GRADE_SECOND)
		pMouseInstance->Set_SkillIconIndex(CMouseManager::TYPE_SKILL, L"SpearPullingInfo", CSkillManager::GRADE_SECOND, m_pSkillInfo->Get_TextNum(), m_pSkillInfo->Get_SkillNotice());


}

CSpearPullingIcon* CSpearPullingIcon::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSpearPullingIcon*		pInstance = new CSpearPullingIcon(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CSpearPullingIcon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CSpearPullingIcon::Clone(void * pArg)
{
	CSpearPullingIcon*		pInstance = new CSpearPullingIcon(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CSpearPullingIcon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSpearPullingIcon::Free()
{
	__super::Free();
}
