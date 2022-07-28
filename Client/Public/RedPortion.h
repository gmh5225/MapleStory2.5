#pragma once

#include "Creature.h"

BEGIN(Client)

class CRedPortion final : public CCreature
{
public:
	typedef struct tagRedPortionDESC
	{
		_float3 vPos;//몬스터위치받아오기
		_int iNum; //갯수 넘겨줘야할것같아서
		//DIR eDir;
	}REDPORTIONDESC;
private:
	CRedPortion(LPDIRECT3DDEVICE9 pGraphic_Device);
	CRedPortion(const CRedPortion& rhs);
	virtual ~CRedPortion() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;//죽은 몬스터의 position 받아와서 클론 생성
	virtual void Tick(_float fTimeDelta) override; //랜덤방향으로 터져서 방사형으로 터지는 움직임 주고싶음
	virtual void LateTick(_float fTimeDelta) override; 
	virtual HRESULT Render() override;

	virtual void Collision(CGameObject* pOther) override; //플레이어와 충돌범위 내에 있을때 z키 누르면 줍기

protected:
	virtual HRESULT Set_RenderState() override;
	virtual HRESULT Reset_RenderState() override;

public:
	void Appearance(_float fTimeDelta);
	void Effect();
	void SetDirection();
	void SetPosition(DIR eDir);
	

public:
	virtual void SetAni() override;


private:
	_int m_iNum;
	DIR m_eDir;
	REDPORTIONDESC m_Desc;

	list<CGameObject*> m_pOther;

private:
	HRESULT SetUp_Components();

public:
	static CRedPortion* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END