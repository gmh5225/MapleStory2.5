#pragma once

#include "Creature.h"
#include "Spawner.h"

BEGIN(Client)

class CGAS final : public CCreature
{
private:
	CGAS(LPDIRECT3DDEVICE9 pGraphic_Device);
	CGAS(const CGAS& rhs);
	virtual ~CGAS() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual void Collision(CGameObject* pOther) override;

private:
	void Tick_Idle(_float fTimeDelta);
	void Tick_Hit(_float fTimeDelta);
	void Tick_Chase(_float fTimeDelta);
	void Tick_Jump(_float fTimeDelta);
	void Tick_DJump(_float fTimeDelta);
	void Tick_Dash(_float fTimeDelta);
	void Tick_End(_float fTimeDelta);	// 텔포 이후
	void Tick_Attack(_float fTimeDelta);
	void Tick_Die(_float fTimeDelta);

public:
	void SetState(STATE eState, DIR eDir);

public:
	virtual void SetAni() override;
	virtual void Damaged(CGameObject* pOther) override;

private:
	HRESULT SetUp_Components();
	void Die();

private:
	STATE m_eCurState;
	DIR m_eDir;

	CGameObject* m_pTarget;


public:
	static CGAS* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;

private:
	_int	m_iHp;
	_int	m_iIndexNum;
	_float m_fCountDead;

	_bool m_bPatterStart;
	_int m_iRandomPattern;
	_float m_fPatternCycle;

	_float m_fJump;
	_float m_fDJump;
	_float m_fAttack;
	_float m_fDash;
	_float m_fEnd;

	_bool m_bTest;

};

END