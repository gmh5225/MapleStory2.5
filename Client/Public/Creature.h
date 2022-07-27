#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CAnimator;
class CTexture;
class CRenderer;
class CCollider;
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CCreature : public CGameObject
{
public:
	enum STATE { STATE_IDLE, STATE_MOVE, STATE_JUMP, STATE_ATTACK, STATE_DASH,STATE_HIT, STATE_CHASE, STATE_DIE, STATE_END };
	enum DIR { DIR_L, DIR_R, DIR_U, DIR_D, DIR_LU, DIR_RU, DIR_LD, DIR_RD, DIR_END };

protected:
	CCreature(LPDIRECT3DDEVICE9 pGraphic_Device);
	CCreature(const CCreature& rhs);
	virtual ~CCreature() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual void Collision(CGameObject* pOther) override {};

public:
	void SetState(STATE eState, DIR eDir);

public:
	virtual void SetAni();
	void Set_Billboard();

	virtual void Damaged(CGameObject* pOther) override {};
	
protected:
	CTexture*				m_pTextureCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CTransform*				m_pTransformCom = nullptr;
	CVIBuffer_Rect*			m_pVIBufferCom = nullptr;
	CAnimator*				m_pAnimatorCom = nullptr;
	CCollider*				m_pColliderCom = nullptr;

protected:
	_float3 m_vLookTemp;
	STATE m_eCurState;
	DIR m_eDir;

protected:
 	virtual HRESULT Set_RenderState();
	virtual HRESULT Reset_RenderState();

protected:
	HRESULT SetUp_Components();

public:
	static CCreature* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END