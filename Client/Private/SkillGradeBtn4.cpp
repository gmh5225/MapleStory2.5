#include "stdafx.h"
#include "..\Public\SkillGradeBtn4.h"
#include "GameInstance.h"
#include "SkillManager.h"


CSkillGradeBtn4::CSkillGradeBtn4(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CSkillGradeBtn4::CSkillGradeBtn4(const CSkillGradeBtn4& rhs)
	: CUI(rhs)
{
}


HRESULT CSkillGradeBtn4::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CSkillGradeBtn4::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	memcpy(&m_UIInfo, pArg, sizeof(UIINFO));
	m_iTexturenum = 0;
	__super::Initialize(pArg);

	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();

	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_SkillGradeBtn4"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	pSkillInstance->Add_SkillFrameImage(this);

	return S_OK;
}

void CSkillGradeBtn4::Tick(_float fTimeDelta)
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

void CSkillGradeBtn4::LateTick(_float fTimeDelta)
{
	

	SetRect(&m_RectUI, m_UIInfo.fX - m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY - m_UIInfo.fSizeY * 0.5f, m_UIInfo.fX + m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY + m_UIInfo.fSizeY * 0.5f);
	
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_UIInfo.fX - g_iWinSizeX * 0.5f, -m_UIInfo.fY + g_iWinSizeY * 0.5f, 0.f));	

	if (m_bRender)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);


}

HRESULT CSkillGradeBtn4::Render()
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

void CSkillGradeBtn4::Change_Texture()
{

	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();

	switch (m_eCollision)
	{
	case Client::CUI::TYPE_NO:
		break;
	case Client::CUI::TYPE_ON:		
		break;
	case Client::CUI::TYPE_DOWN:
		pSkillInstance->Set_SkillGrade(CSkillManager::GRADE_FOURTH);
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
	
	if (pSkillInstance->Get_SkillGrade() == CSkillManager::GRADE_FOURTH)
		m_iTexturenum = 2;
	else
		m_iTexturenum = 1;
	

	

}

CSkillGradeBtn4* CSkillGradeBtn4::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSkillGradeBtn4*		pInstance = new CSkillGradeBtn4(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CSkillGradeBtn4"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CSkillGradeBtn4::Clone(void * pArg)
{
	CSkillGradeBtn4*		pInstance = new CSkillGradeBtn4(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CSkillGradeBtn4"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSkillGradeBtn4::Free()
{
	__super::Free();

}