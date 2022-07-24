#pragma once

#include "Creature.h"

BEGIN(Client)

class CAngelRay_Effect final : public CCreature
{
private:
	CAngelRay_Effect(LPDIRECT3DDEVICE9 pGraphic_Device);
	CAngelRay_Effect(const CAngelRay_Effect& rhs);
	virtual ~CAngelRay_Effect() = default;

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

public:
	void SetState(STATE eState, DIR eDir);

public:
	virtual void SetAni() override;


private:
	STATE m_eCurState;
	DIR m_eDir;
	_bool m_bCreate;
	_bool m_bRender;

private:
	HRESULT SetUp_Components();

public:
	static CAngelRay_Effect* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END