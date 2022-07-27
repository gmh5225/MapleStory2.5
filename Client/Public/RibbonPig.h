#pragma once

#include "Creature.h"

BEGIN(Client)

class CRibbonPig final : public CCreature
{
private:
	CRibbonPig(LPDIRECT3DDEVICE9 pGraphic_Device);
	CRibbonPig(const CRibbonPig& rhs);
	virtual ~CRibbonPig() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual void Collision(CGameObject* pOther) override;

private:
	void Tick_Idle(_float fTimeDelta);
	void Tick_Move(_float fTimeDelta);
	void Tick_Hit(_float fTimeDelta);
	void Tick_Chase(_float fTimeDelta);

public:
	void SetState(STATE eState, DIR eDir);

public:
	virtual void SetAni() override;
	virtual void Damaged(CGameObject* pOther) override;


private:
	STATE m_eCurState;
	DIR m_eDir;

	CGameObject* m_pTarget;

private:
	HRESULT SetUp_Components();

public:
	static CRibbonPig* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END