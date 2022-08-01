#include "stdafx.h"
#include "..\Public\QuickSlotSkill.h"
#include "GameInstance.h"
#include "QuickSlotManager.h"
#include "MouseManager.h"



CQuickSlotSkill::CQuickSlotSkill(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CQuickSlotSkill::CQuickSlotSkill(const CQuickSlotSkill& rhs)
	: CUI(rhs)
{
}


HRESULT CQuickSlotSkill::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CQuickSlotSkill::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	memcpy(&m_UIInfo, pArg, sizeof(UIINFO));
	m_iIndexNum = m_UIInfo.iNum;
	m_iTexturenum = 0;
	m_bRender = false;
	__super::Initialize(pArg);

	//CSkillManager* pSkillInstance = CSkillManager::Get_Instance();

	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_MouseSkillIcon"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	//pSkillInstance->Add_SkillFrameImage(this);

	return S_OK;
}

void CQuickSlotSkill::Tick(_float fTimeDelta)
{
	CGameInstance* pInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pInstance);


	Check_Collision(DIMK_LBUTTON);
	Change_Texture();
	
	Safe_Release(pInstance);
}

void CQuickSlotSkill::LateTick(_float fTimeDelta)
{

	if (m_bRender)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);

}

HRESULT CQuickSlotSkill::Render()
{
	if (FAILED(m_pTextureCom->Bind_Texture(m_iTexturenum)))
		return E_FAIL;

	m_pTransformCom->Bind_WorldMatrix();
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	Set_RenderState();

	m_pVIBufferCom->Render();

	Reset_RenderState();
	return S_OK;
}

void CQuickSlotSkill::Change_Texture()
{

	//CSkillManager* pSkillInstance = CSkillManager::Get_Instance();
	CMouseManager* pMouseInstance = CMouseManager::Get_Instance();

	switch (m_eCollision)
	{
	case Client::CUI::TYPE_NO:
		break;
	case Client::CUI::TYPE_ON:
		break;
	case Client::CUI::TYPE_DOWN:
		break;
	case Client::CUI::TYPE_UP:
		m_iTexturenum = pMouseInstance->Get_SkillIconIndex();
		
		break;
	case Client::CUI::TYPE_PRESSING:
		break;
	case Client::CUI::TYPE_END:
		break;
	default:
		break;
	}





}

CQuickSlotSkill* CQuickSlotSkill::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CQuickSlotSkill*		pInstance = new CQuickSlotSkill(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CQuickSlotSkill"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CQuickSlotSkill::Clone(void * pArg)
{
	CQuickSlotSkill*		pInstance = new CQuickSlotSkill(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CQuickSlotSkill"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CQuickSlotSkill::Free()
{
	__super::Free();

}
