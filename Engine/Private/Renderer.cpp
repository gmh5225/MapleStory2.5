#include "..\Public\Renderer.h"

#include "GameObject.h"

CRenderer::CRenderer(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
}

HRESULT CRenderer::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CRenderer::Initialize(void * pArg)
{
	return S_OK;
}

HRESULT CRenderer::Add_RenderGroup(RENDERGROUP eRenderGroup, CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	m_RenderObjects[eRenderGroup].push_back(pGameObject);

	Safe_AddRef(pGameObject);

	return S_OK;
}

HRESULT CRenderer::Draw()
{
	for (_uint i = 0; i < RENDER_END; ++i)
	{
		if (i == RENDER_ALPHABLEND)
		{
			m_RenderObjects[i].sort([](CGameObject* pSour, CGameObject* pDest)
			{
				return pSour->Get_CamDistance() > pDest->Get_CamDistance();
			});
		}

		if (i == RENDER_MOVEALPHABLEND)
		{
			m_RenderObjects[i].sort([](CGameObject* pSour, CGameObject* pDest)
			{
				return pSour->Get_YDistance() < pDest->Get_YDistance();
			});
		}

		if (i == RENDER_BOSS)
		{
			m_RenderObjects[i].sort([](CGameObject* pSour, CGameObject* pDest)
			{
				return pSour->Get_CamDistance() > pDest->Get_CamDistance();
			});
		}

		

		for (auto& pRenderObject : m_RenderObjects[i])
		{
			if (nullptr != pRenderObject)
				pRenderObject->Render();

			Safe_Release(pRenderObject);
		}
		m_RenderObjects[i].clear();
	}

	return S_OK;
}

CRenderer * CRenderer::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CRenderer*			pInstance = new CRenderer(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CRenderer"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CRenderer::Clone(void * pArg)
{
	AddRef();

	return this;
}

void CRenderer::Free()
{
	__super::Free();

	for (auto& List : m_RenderObjects)
	{
		for (auto& pGameObject : List)
		{
			Safe_Release(pGameObject);
		}
		List.clear();
	}	
}
