#pragma once

#include "Client_Defines.h"
#include "Base.h"

BEGIN(Engine)
class CCollider;
END

BEGIN(Client)

class CToolManager final : CBase
{
	DECLARE_SINGLETON(CToolManager)

private:
	CToolManager();
	virtual ~CToolManager() = default;


public:
	// For. LevelChange
	void SetDestLevel(LEVEL eLevel, _float3 vDestPos) { m_eDestLevel = eLevel; m_vDestPos = vDestPos; }
	void CheckDestLevel(CCollider* pColliderCom, LPDIRECT3DDEVICE9 pGraphic_Device);


private:
	LEVEL m_eDestLevel = LEVEL_END;
	_float3 m_vDestPos;

public:
	virtual void Free() override;
};

END