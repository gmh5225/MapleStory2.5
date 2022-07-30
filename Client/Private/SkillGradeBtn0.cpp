#include "stdafx.h"
#include "..\Public\SkillGradeBtn0.h"
#include "GameInstance.h"
#include "SkillManager.h"



CSkillGradeBtn0::CSkillGradeBtn0(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CSkillGradeBtn0::CSkillGradeBtn0(const CSkillGradeBtn0& rhs)
	: CUI(rhs)
{
}


HRESULT CSkillGradeBtn0::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CSkillGradeBtn0::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	memcpy(&m_UIInfo, pArg, sizeof(UIINFO));
	m_iTexturenum = 0;
	__super::Initialize(pArg);

	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();

	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_SkillGradeBtn0"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	pSkillInstance->Add_SkillFrameImage(this);

	return S_OK;
}

void CSkillGradeBtn0::Tick(_float fTimeDelta)
{
	CGameInstance* pInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pInstance);

	if (pInstance->Key_Down(DIK_K))
	{
		m_bRender = !m_bRender;
	}

	Check_Collision(DIMK_LBUTTON);
	Change_Texture();


	Safe_Release(pInstance);
}

void CSkillGradeBtn0::LateTick(_float fTimeDelta)
{
	

	SetRect(&m_RectUI, m_UIInfo.fX - m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY - m_UIInfo.fSizeY * 0.5f, m_UIInfo.fX + m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY + m_UIInfo.fSizeY * 0.5f);
	
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_UIInfo.fX - g_iWinSizeX * 0.5f, -m_UIInfo.fY + g_iWinSizeY * 0.5f, 0.f));

	if (m_bRender)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);


}

HRESULT CSkillGradeBtn0::Render()
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

void CSkillGradeBtn0::Change_Texture()
{

	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();

	switch (m_eCollision)
	{
	case Client::CUI::TYPE_NO:
		break;
	case Client::CUI::TYPE_ON:		
		break;
	case Client::CUI::TYPE_DOWN:
		pSkillInstance->Set_SkillGrade(CSkillManager::GRADE_BEGENNER);		
		break;
	case Client::CUI::TYPE_UP:
		break;
	case Client::CUI::TYPE_PRESSING:	
		break;
	case Client::CUI::TYPE_END:
		break;
	default:
		break;
	}
	if (pSkillInstance->Get_SkillGrade() == CSkillManager::GRADE_BEGENNER)
		m_iTexturenum = 1;
	else
		m_iTexturenum = 0;
	

	

}

CSkillGradeBtn0* CSkillGradeBtn0::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSkillGradeBtn0*		pInstance = new CSkillGradeBtn0(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CSkillGradeBtn0"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CSkillGradeBtn0::Clone(void * pArg)
{
	CSkillGradeBtn0*		pInstance = new CSkillGradeBtn0(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CSkillGradeBtn0"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSkillGradeBtn0::Free()
{
	__super::Free();

}
