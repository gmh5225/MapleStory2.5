#pragma once

#include "Component.h"

/* 1.��ü�� ������¸� �����Ѵ�.(���) */
/* 2.���û����� ������ ������·� ��ȯ���ֱ����ѱ��  */

BEGIN(Engine)

class ENGINE_DLL CTransform final : public CComponent
{
public:
	enum STATETYPE { STATE_RIGHT, STATE_UP, STATE_LOOK, STATE_POSITION, STATE_END };

public:
	typedef struct tagTransformDesc
	{
		_float			fSpeedPerSec;
		_float			fRotationPerSec;
	}TRANSFORMDESC;
public:
	CTransform(LPDIRECT3DDEVICE9 pGraphic_Device);
	CTransform(const CTransform& rhs);
	virtual ~CTransform() = default;

public: 
	_float3 Get_State(STATETYPE eState) const {
		return *(_float3*)&m_WorldMatrix.m[eState][0];
	}

	_float3 Get_Scaled() const;

	_float4x4 Get_WorldMatrixInverse() {
		_float4x4		WorldMatrixInv;
		return	*D3DXMatrixInverse(&WorldMatrixInv, nullptr, &m_WorldMatrix);
	}

	void Set_State(STATETYPE eState, const _float3& State) {
		memcpy(&m_WorldMatrix.m[eState][0], &State, sizeof(_float3));		
	}

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	HRESULT Bind_WorldMatrix();

public:
	void Go_Straight(_float fTimeDelta);
	void Go_Backward(_float fTimeDelta);
	void Go_Right(_float fTimeDelta);
	void Go_Left(_float fTimeDelta);

	void Rotation(_float3 vAxis, _float fRadian);
	void Turn(_float3 vAxis, _float fTimeDelta);
	void LookAt(_float3 vTargetPos);
	void LookAtForLandObject(_float3 vTargetPos);
	void Chase(_float3 vTargetPos, _float fTimeDelta);

public:




private:
	_float4x4			m_WorldMatrix;
	TRANSFORMDESC		m_TransformDesc;

public:
	static CTransform* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END