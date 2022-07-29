#pragma once
#include "UI.h"

BEGIN(Client)

class CSkillFrame final : public CUI
{
private:
	CSkillFrame(LPDIRECT3DDEVICE9 pGraphic_Device);
	CSkillFrame(const CSkillFrame& rhs);
	virtual ~CSkillFrame() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	static CSkillFrame* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;

	//LPD3DXFONT m_SkillFrameFont;
};

END

