#pragma once

#include "Client_Defines.h"
#include "Creature.h"

BEGIN(Client)

class CPlayer final : public CCreature
{
private:
	CPlayer(LPDIRECT3DDEVICE9 pGraphic_Device);
	CPlayer(const CPlayer& rhs);
	virtual ~CPlayer() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual void Collision(CGameObject* pOther) override;
	virtual void OnLay(_float3 vOutDis) override;

public:
	void GetKeyInput(_float fTimeDelta);
	void GetJumpKeyInput(_float fTimeDelta);
	virtual void SetAni() override;
	virtual void SetState(STATE eState, DIR eDir);

	void SetOnceEndAni();

	void SetRespownPos(_float3 RePos);


	virtual void SetShadow(LEVEL eLevel, _float fScale) override;

private:
	void Idle(_float fTimeDelta);
	void Dash(_float fTimeDelta);
	void Jump(_float fTimeDelta);
	void DoubleJump(_float fTimeDelta);

	void Particle(_float fTimeDelta);

protected:
	virtual HRESULT Set_RenderState() override;
	virtual HRESULT Reset_RenderState() override;

private:
	HRESULT SetUp_Components();
	LPD3DXFONT m_Font;
	_bool temp = false;

	_float m_fDashAcc;
	_float m_fRespownPosAcc;
	_float3 m_vRespownPos;

	// TEST
	_float _fParticleMoveTimeAcc = 0.f;


public:
	static CPlayer* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END