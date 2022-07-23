#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CRenderer;
class CTransform;
class CVIBuffer_Cube;
END


BEGIN(Client)

class CWood final : public CGameObject
{
public:
	typedef struct tagCubeDesc
	{
		_float3	vPos;
		const _tchar* pTextureTag;
	}CUBEDESC;
private:
	CWood(LPDIRECT3DDEVICE9 pGraphic_Device);
	CWood(const CWood& rhs);
	virtual ~CWood() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTexture*				m_pTextureCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CTransform*				m_pTransformCom = nullptr;
	CVIBuffer_Cube*			m_pVIBufferCom = nullptr;

private:
	_float3			m_vTargetPos = _float3(0.f, 0.f, 0.f);

private:
	HRESULT Set_RenderState();
	HRESULT Reset_RenderState();
private:
	HRESULT SetUp_Components();

public:
	static CWood* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END