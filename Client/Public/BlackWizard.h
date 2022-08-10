#pragma once

#include "Creature.h"

BEGIN(Client)

class CBlackWizard final : public CCreature
{
public:
	enum STATE {STATE_APPEAR, STATE_STAND, STATE_SKILL1, STATE_END};
public:
	CBlackWizard(LPDIRECT3DDEVICE9 pGraphic_Device);
	CBlackWizard(const CBlackWizard& rhs);
	virtual ~CBlackWizard() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual void Collision(CGameObject* pOther) override;

public:
	void SetState();
	void Pattern();
	void Fix_Scale();

public:
	virtual void SetAni() override;
	virtual void Damaged(CGameObject* pOther) override;

protected:
	virtual HRESULT Set_RenderState() override;
	virtual HRESULT Reset_RenderState() override;

private:
	HRESULT SetUp_Components();

private:
	CGameObject* m_pTarget;
	STATE m_eCurState;
	bool m_bState;
public:
	static CBlackWizard* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;


};

END

