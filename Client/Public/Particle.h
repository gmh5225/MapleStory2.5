#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
#include "Map_Manager.h"

BEGIN(Engine)
class CTexture;
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END


BEGIN(Client)

class CParticle final : public CGameObject
{
public:
	typedef struct tagParticleDesc
	{
		// ���
		_float3 vPos;

		// ũ�⸦
		_float fScale;

		// � ��������,
		_float3 vDirVec;
		// ����
		_float  fForce_Y;
		_float  fForce_X;

		// �߷� ����, �߷� ��
		_bool bGravity;
		_float fGravityVal;
		// ������ ����, ���� ��

		// �� �� ����
		_float fLifeTime;

	}PARTICLEDESC;

private:
	CParticle(LPDIRECT3DDEVICE9 pGraphic_Device);
	CParticle(const CParticle& rhs);
	virtual ~CParticle() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTexture*				m_pTextureCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CTransform*				m_pTransformCom = nullptr;
	CVIBuffer_Rect*			m_pVIBufferCom = nullptr;

private:
	PARTICLEDESC			m_ParticleDesc;
	_float					m_fLifeTimeAcc;

	_float3					m_vLookTemp;

private:
	HRESULT Set_RenderState();
	HRESULT Reset_RenderState();

	void Set_Billboard();

private:
	HRESULT SetUp_Components();

public:
	static CParticle* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END