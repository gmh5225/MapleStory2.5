#pragma once

#include "Creature.h"

BEGIN(Client)

class CBlueSnail final : public CCreature
{
private:
	enum RandomMove { MOVE_R, MOVE_L, MOVE_U, MOVE_D, MOVE_END };


	CBlueSnail(LPDIRECT3DDEVICE9 pGraphic_Device);
	CBlueSnail(const CBlueSnail& rhs);
	virtual ~CBlueSnail() = default;

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
	virtual	void SetState(STATE eState, DIR eDir) override;

public:
	virtual void SetAni() override;
	virtual void Damaged(CGameObject* pOther) override;

private:
	STATE m_eCurState;
	DIR m_eDir;

	CGameObject* m_pTarget;

	_uint m_iMove;
	_float3 m_fEndPos;
	_float3 m_fStartPos;
	_bool m_bDir;
	_float m_fDistance;

	_uint m_iHp;
	_int m_iIndexNum;

	_bool temp = false;

private:
	HRESULT SetUp_Components();

public:
	static CBlueSnail* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END