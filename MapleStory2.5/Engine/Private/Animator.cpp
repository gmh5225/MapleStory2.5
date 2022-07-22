#include "..\Public\Animator.h"

#include "GameInstance.h"

CAnimator::CAnimator(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CComponent(pGraphic_Device)
	, m_fAnimPerTime(0.f)
	, m_iAnimCount(0)
{
}

CAnimator::CAnimator(const CAnimator& rhs)
	:CComponent(rhs)
	, m_fAnimPerTime(rhs.m_fAnimPerTime)
	, m_iAnimCount(rhs.m_iAnimCount)
{

}

HRESULT CAnimator::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CAnimator::Initialize(void * pArg)
{

	return S_OK;
}

HRESULT CAnimator::Create_Texture(_uint iLevelIndex, const _tchar * pPrototypeTag, void * pArg)
{
	CGameInstance* pInstance = pInstance->Get_Instance();
	Safe_AddRef(pInstance);

	CComponent* pTexture = pInstance->Clone_Component(iLevelIndex, pPrototypeTag, pArg);

	m_AniTexture.emplace(pPrototypeTag, (CTexture*)pTexture);

	Safe_Release(pInstance);

	return S_OK;
}

HRESULT CAnimator::Bind_Texture(const _tchar * pTexTag, _uint iCount)
{
	CTexture* pTexture = Find_Component(pTexTag);

	if (nullptr == pTexture)
		return E_FAIL;

	pTexture->Bind_Texture(iCount);

	return S_OK;
}

HRESULT CAnimator::Play_Loof(const _tchar * pTexTag, _float delay, _float fTimeDelta)
{
	CTexture* pTex = Find_Component(pTexTag);
	if (pTex == nullptr)
		return E_FAIL;

	m_fAnimPerTime += fTimeDelta;

	if (delay < m_fAnimPerTime)
	{
		++m_iAnimCount;

		if (m_iAnimCount >= pTex->Get_Size())
			m_iAnimCount = 0;

		m_fAnimPerTime = 0.f;
	}

	Bind_Texture(pTexTag, m_iAnimCount);
	return S_OK;
}

CAnimator * CAnimator::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CAnimator*			pInstance = new CAnimator(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CAnimator"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CAnimator * CAnimator::Clone(void * pAvg)
{
	CAnimator*			pInstance = new CAnimator(*this);

	if (FAILED(pInstance->Initialize(pAvg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CAnimator"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CTexture* CAnimator::Find_Component(const _tchar * pComponentTag)
{
	auto	iter = find_if(m_AniTexture.begin(), m_AniTexture.end(), CTag_Finder(pComponentTag));

	if (iter == m_AniTexture.end())
		return nullptr;

	return iter->second;
}


void CAnimator::Free()
{
	for (auto& iter : m_AniTexture)
	{
		if (iter.second != nullptr)
			Safe_Release(iter.second);
	}
	m_AniTexture.clear();

	__super::Free();


}



