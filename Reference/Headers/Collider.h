#pragma once

#include "Component.h"

/* 화면에 그려져야할 객체들을 그려져야할 순서대로 모아서 보관한다.  */
/* 보관하고 있는 개첻르의 렌더함수를 호출해주낟. */

BEGIN(Engine)

class ENGINE_DLL CCollider final : public CComponent
{
public: /* 그려지는 순서에 따른 정의 */
	enum COLLSIONGROUP { COLLSION_PLAYER, COLLSION_MONSTER, COLLSION_NPC, COLLSION_SKILL, COLLSION_BLOCK, COLLSION_UI, COLLSION_END };


private:
	CCollider(LPDIRECT3DDEVICE9 pGraphic_Device);
	CCollider(const CCollider& rhs);
	virtual ~CCollider() = default;



public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
public:
	HRESULT Add_CollsionGroup(COLLSIONGROUP eCollsionGroup, class CGameObject* pGameObject);
	HRESULT Check_SphereCollsion(COLLSIONGROUP eCollsionGroup_L, COLLSIONGROUP eCollsionGroup_R);
	HRESULT End_Collsion();

public:
	_bool Check_Sphere(CGameObject* pObj_L, CGameObject* pObj_R);

private:
	list<class CGameObject*>				m_CollisionObjects[COLLSION_END];
	typedef list<class CGameObject*>		COLLSIONOBJECTS;

public:
	static CCollider* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END