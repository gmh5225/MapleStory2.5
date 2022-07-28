#pragma once

#include "Component.h"

/* ȭ�鿡 �׷������� ��ü���� �׷������� ������� ��Ƽ� �����Ѵ�.  */
/* �����ϰ� �ִ� ���b���� �����Լ��� ȣ�����ֳ�. */

BEGIN(Engine)

class ENGINE_DLL CBoxCollider final : public CComponent
{
public:
	typedef struct tagBoxColComDesc
	{
		_float3		vScale;
		_float3		vPivot;
	}BOXCOLCOMEDESC;


private:
	CBoxCollider(LPDIRECT3DDEVICE9 pGraphic_Device);
	CBoxCollider(const CBoxCollider& rhs);
	virtual ~CBoxCollider() = default;

public:
	_float3 Get_WorldMax() { return m_vWorldMax; }
	_float3 Get_WorldMin() { return m_vWorldMin; }

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

	void Tick(class CTransform* pTrans);

	
private:
	_float3		m_vMax;
	_float3		m_vMin;
	_float3		m_vPivot;

	_float3		m_vWorldMax;
	_float3		m_vWorldMin;

public:
	static CBoxCollider* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END