#include "stdafx.h"
#include "..\Public\WarriorReefIcon.h"
#include "GameInstance.h"
#include "SkillManager.h"
#include "MouseManager.h"


CWarriorReefIcon::CWarriorReefIcon(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CWarriorReefIcon::CWarriorReefIcon(const CWarriorReefIcon& rhs)
	: CUI(rhs)
{
}


HRESULT CWarriorReefIcon::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CWarriorReefIcon::Initialize(void * pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	memcpy(&m_UIInfo, pArg, sizeof(UIINFO));

	__super::Initialize(pArg);
	m_iTexturenum = 0;
	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();

	m_pSkillInfo = (CWarriorReefInfo*)pSkillInstance->Get_SkillInfo(L"WarriorReefInfo", CSkillManager::GRADE_BEGENNER);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Texture_WarriorReefIcon"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	D3DXCreateFont(m_pGraphic_Device, 13, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"����ü", &m_NoticeFont);

	pSkillInstance->Add_SkillFrameImage(this);

	m_bRender = false;

	return S_OK;
}

void CWarriorReefIcon::Tick(_float fTimeDelta)
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

void CWarriorReefIcon::LateTick(_float fTimeDelta)
{
	SetRect(&m_RectUI, m_UIInfo.fX - m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY - m_UIInfo.fSizeY * 0.5f, m_UIInfo.fX + m_UIInfo.fSizeX * 0.5f, m_UIInfo.fY + m_UIInfo.fSizeY * 0.5f);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_UIInfo.fX - g_iWinSizeX * 0.5f, -m_UIInfo.fY + g_iWinSizeY * 0.5f, 0.f));

	Change_Texture();
	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();
	if (m_bRender&& pSkillInstance->Get_SkillGrade() == CSkillManager::GRADE_BEGENNER)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);

}

HRESULT CWarriorReefIcon::Render()
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

void CWarriorReefIcon::Change_Texture()
{
	CSkillManager* pSkillInstance = CSkillManager::Get_Instance();
	if (pSkillInstance->Get_SkillInfo(L"WarriorReefInfo", CSkillManager::GRADE_BEGENNER)->Get_SkillLevel() < 1)
		m_iTexturenum = 0;
	else
		m_iTexturenum = 1;

	if (m_bRender)
	{
		CMouseManager* pMouseInstance = CMouseManager::Get_Instance();
		if (m_eCollision == TYPE_DOWN && m_pSkillInfo->Get_SkillLevel() != 0 && pSkillInstance->Get_SkillGrade() == CSkillManager::GRADE_BEGENNER)
		{
			CGameInstance::Get_Instance()->PlaySoundW(L"DragStart.mp3", 25, 1.f);
			pMouseInstance->Set_SkillIconIndex(CMouseManager::TYPE_SKILL, L"WarriorReefInfo", CSkillManager::GRADE_BEGENNER, m_pSkillInfo->Get_TextNum(), m_pSkillInfo->Get_SkillNotice());
		}
	}

}

CWarriorReefIcon* CWarriorReefIcon::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CWarriorReefIcon*		pInstance = new CWarriorReefIcon(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CWarriorReefIcon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CWarriorReefIcon::Clone(void * pArg)
{
	CWarriorReefIcon*		pInstance = new CWarriorReefIcon(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CWarriorReefIcon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CWarriorReefIcon::Free()
{
	__super::Free();
}
