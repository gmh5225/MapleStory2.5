#pragma once

#include "Component.h"

/* ȭ�鿡 �׷������� ��ü���� �׷������� ������� ��Ƽ� �����Ѵ�.  */
/* �����ϰ� �ִ� ���b���� �����Լ��� ȣ�����ֳ�. */

BEGIN(Engine)

class ENGINE_DLL CCollider final : public CComponent
{
public: /* �׷����� ������ ���� ���� */
	enum COLLSIONGROUP { COLLSION_PLAYER, COLLSION_MONSTER, COLLSION_NPC, COLLSION_PLAYER_SKILL, COLLSION_MONSTER_SKILL, COLLSION_BLOCK, COLLISION_ITEM, COLLSION_UI, COLLSION_SECTION, COLLSION_END };


private:
	CCollider(LPDIRECT3DDEVICE9 pGraphic_Device);
	CCollider(const CCollider& rhs);
	virtual ~CCollider() = default;



public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
public:
	HRESULT Add_SphereCollsionGroup(COLLSIONGROUP eCollsionGroup, class CGameObject* pGameObject);
	HRESULT Add_BoxCollsionGroup(COLLSIONGROUP eCollsionGroup, class CGameObject* pGameObject);
	HRESULT Add_PushBoxCollsionGroup(COLLSIONGROUP eCollsionGroup, class CGameObject* pGameObject);
	HRESULT Check_SphereCollsion(COLLSIONGROUP eCollsionGroup_L, COLLSIONGROUP eCollsionGroup_R);
	HRESULT Check_BoxCollsion(COLLSIONGROUP eCollsionGroup_L, COLLSIONGROUP eCollsionGroup_R);
	HRESULT Check_PushBoxCollsion(COLLSIONGROUP eCollsionGroup_L, COLLSIONGROUP eCollsionGroup_R);

	HRESULT Check_PushCubeCollsion(COLLSIONGROUP eCollsionGroup_L);

	HRESULT End_Collsion();

	HRESULT Set_SectionCubes();

public:
	_bool Check_Sphere(CGameObject* pObj_L, CGameObject* pObj_R);
	_bool Check_Box(CGameObject* pObj_L, CGameObject* pObj_R, _bool bPush = false);

private:
	list<class CGameObject*>				m_SphereCollisionObjects[COLLSION_END];
	list<class CGameObject*>				m_BoxCollisionObjects[COLLSION_END];
	list<class CGameObject*>				m_PhshBoxCollisionObjects[COLLSION_END];
	typedef list<class CGameObject*>		COLLSIONOBJECTS;

	list<class CGameObject*>		m_Sections;

public:
	static CCollider* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END