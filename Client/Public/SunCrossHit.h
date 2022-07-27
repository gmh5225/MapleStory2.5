#pragma once

#include "Creature.h"

BEGIN(Client)

class CSunCrossHit final : public CCreature
{
public:
	typedef struct tagSunCross_HitDESC
	{
		_float3 vPos;
	}SUNCROSSHITDESC;

private:
	CSunCrossHit(LPDIRECT3DDEVICE9 pGraphic_Device);
	CSunCrossHit(const CSunCrossHit& rhs);
	virtual ~CSunCrossHit() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual void Collision(CGameObject* pOther) override;

protected:
	virtual HRESULT Set_RenderState() override;
	virtual HRESULT Reset_RenderState() override;

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
	SUNCROSSHITDESC m_Desc;

private:
	HRESULT SetUp_Components();

public:
	static CSunCrossHit* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END