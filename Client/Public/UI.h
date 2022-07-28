#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CUI : public CGameObject
{
public:
	enum Collision_Type {TYPE_NO, TYPE_ON, TYPE_DOWN, TYPE_UP, TYPE_PRESSING, TYPE_END};
public:
	typedef struct tagUIInfo
	{
		_float					fX, fY, fSizeX, fSizeY;
	}UIINFO;
protected:
	CUI(LPDIRECT3DDEVICE9 pGraphic_Device);
	CUI(const CUI& rhs);
	virtual ~CUI() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

protected:
	CTexture*				m_pTextureCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CTransform*				m_pTransformCom = nullptr;
	CVIBuffer_Rect*			m_pVIBufferCom = nullptr;

protected:
	_float4x4				m_ProjMatrix;
	_float4x4				m_ViewMatrix;
	UIINFO					m_UIInfo;
	RECT					m_RectUI;
	Collision_Type			m_eCollision;
	_uint					m_iTexturenum;

protected:
	HRESULT SetUp_Components();
	virtual HRESULT Set_RenderState();
	virtual HRESULT Reset_RenderState();
	void Check_Collision(DIMK m_eMouseKey);

protected:
	_bool m_bRender;

public:
	static CUI* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END