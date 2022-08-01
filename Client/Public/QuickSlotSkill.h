#pragma once
#include "UI.h"

BEGIN(Client)
class CQuickSlotSkill final : public  CUI
{
private:
	CQuickSlotSkill(LPDIRECT3DDEVICE9 pGraphic_Device);
	CQuickSlotSkill(const CQuickSlotSkill& rhs);
	virtual ~CQuickSlotSkill() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	void Change_Texture();

private:
	_uint m_iIndexNum;

public:
	static CQuickSlotSkill* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;

};
END

