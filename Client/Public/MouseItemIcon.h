#pragma once
#include "UI.h"

BEGIN(Client)


class CMouseItemIcon final : public  CUI
{
private:
	CMouseItemIcon(LPDIRECT3DDEVICE9 pGraphic_Device);
	CMouseItemIcon(const CMouseItemIcon& rhs);
	virtual ~CMouseItemIcon() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	void Change_Texture();
	_uint Get_TextNum() { return m_iTexturenum; }

public:
	static CMouseItemIcon* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;


};
END

