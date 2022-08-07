#pragma once

#include "Client_Defines.h"
#include "Base.h"


BEGIN(Client)

class CParticleManager final : CBase
{
	DECLARE_SINGLETON(CParticleManager)

private:
	CParticleManager();
	virtual ~CParticleManager() = default;


public:
	void Player_Walk(_float3 _vPos, _float3 _vDirVec);
	void Player_Lend(_float3 _vPos);

	void Shot(_float3 _vPos, _float3 _vDirVec);

public:
	void MakeParticle(_float3 _vPos, _float _fScale, _float3 _vDirVec, _float _fForce_Y, _float _fForce_X, _bool _bGravity, _float _fGravityVal, _float _fLifeTime);

public:
	virtual void Free() override;
};

END