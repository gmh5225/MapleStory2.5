#include "stdafx.h"
#include "..\Public\ParticleManager.h"

#include "GameInstance.h"
#include "Particle.h"

IMPLEMENT_SINGLETON(CParticleManager)

CParticleManager::CParticleManager()
{
	
}


void CParticleManager::Player_Walk(_float3 _vPos, _float3 _vDirVec)
{
	_float3 vStartPos = _vPos;
	vStartPos.y -= 0.5f;

	MakeParticle(vStartPos, 0.15f, _vDirVec, 2.5f, 0.2f, true, 1.f, 0.5f);
}

void CParticleManager::Player_Lend(_float3 _vPos)
{
	_float3 vStartPos = _vPos;
	vStartPos.y -= 0.5f;

	_float fDegree = 0.f;
	for (_int i = 0; i < 4; i++)
	{
		fDegree = (_float)i * 90.f;
		
		_float3 vDirVec = { 1.f, 0.f, 0.f };

		_float4x4 Mat_Y;
		D3DXMatrixIdentity(&Mat_Y);

		D3DXMatrixRotationY(&Mat_Y, fDegree);
		D3DXVec3TransformNormal(&vDirVec, &vDirVec, &Mat_Y);

		MakeParticle(vStartPos, 0.12f, vDirVec, 2.5f, 1.0f, true, 1.f, 0.7f);
	}

}

void CParticleManager::MakeParticle(_float3 _vPos, _float _fScale, _float3 _vDirVec, _float _fForce_Y, _float _fForce_X, _bool _bGravity, _float _fGravityVal, _float _fLifeTime)
{
	CParticle::PARTICLEDESC ParticleDesc;
	ZeroMemory(&ParticleDesc, sizeof(CParticle::PARTICLEDESC));

	ParticleDesc.vPos = _vPos;
	ParticleDesc.fScale = _fScale;

	ParticleDesc.vDirVec = _vDirVec;
	ParticleDesc.fForce_X = _fForce_X;

	ParticleDesc.bGravity = _bGravity;
	ParticleDesc.fGravityVal = _fGravityVal;
	ParticleDesc.fForce_Y = _fForce_Y;

	ParticleDesc.fLifeTime = _fLifeTime;

	CGameInstance::Get_Instance()->Add_GameObjectToLayer(TEXT("Prototype_GameObject_Particle"), LEVEL_GAMEPLAY, TEXT("Layer_Particle"), &ParticleDesc);

}

void CParticleManager::Free()
{
}


