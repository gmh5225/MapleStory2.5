#pragma once
#include "UI.h"

BEGIN(Client)
class CItemNotice final : public  CUI
{
private:
	CItemNotice(LPDIRECT3DDEVICE9 pGraphic_Device);
	CItemNotice(const CItemNotice& rhs);
	virtual ~CItemNotice() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	static CItemNotice* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};
END

