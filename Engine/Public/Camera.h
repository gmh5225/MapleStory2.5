#pragma once

/* Ŭ�󿡼� ������ ī�޶���� �θ�. */
/* ��� ī�޶� �������� �⺻���� ����� �����Ѵ�. */
#include "GameObject.h"
#include "Transform.h"

BEGIN(Engine)

class ENGINE_DLL CCamera abstract : public CGameObject
{
public:
	typedef struct tagCameraDesc
	{
		_float3		vEye, vAt;
		_float		fFovy, fAspect, fNear, fFar;

		CTransform::TRANSFORMDESC		TransformDesc;
	}CAMERADESC;

protected:
	CCamera(LPDIRECT3DDEVICE9 pGraphic_Device);
	CCamera(const CCamera& rhs, CTransform::TRANSFORMDESC* pArg);
	virtual ~CCamera() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();

protected:
	class CTransform*			m_pTransformCom = nullptr;
	CAMERADESC					m_CameraDesc;


public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free();
};

END