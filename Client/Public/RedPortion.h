#pragma once

#include "Creature.h"

BEGIN(Client)

class CRedPortion final : public CCreature
{
public:
	enum ITEM{ ITEM_APPEAR, ITEM_IDLE, ITEM_PICKED, ITEM_END};
public:
	typedef struct tagRedPortionDESC
	{
		_float3 vPos;//������ġ�޾ƿ���
		_int iNum; //���� �Ѱ�����ҰͰ��Ƽ�
		//DIR eDir;
		ITEM eItemState;
	}REDPORTIONDESC;
private:
	CRedPortion(LPDIRECT3DDEVICE9 pGraphic_Device);
	CRedPortion(const CRedPortion& rhs);
	virtual ~CRedPortion() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;//���� ������ position �޾ƿͼ� Ŭ�� ����
	virtual void Tick(_float fTimeDelta) override; //������������ ������ ��������� ������ ������ �ְ����
	virtual void LateTick(_float fTimeDelta) override; 
	virtual HRESULT Render() override;

	virtual void Collision(CGameObject* pOther) override; //�÷��̾�� �浹���� ���� ������ zŰ ������ �ݱ�

protected:
	virtual HRESULT Set_RenderState() override;
	virtual HRESULT Reset_RenderState() override;

public:
	void Appearance(_float fTimeDelta);
	void Effect();
	void SetDirection();
	void SetPosition(DIR eDir);

private:
	_int m_iNum;
	DIR m_eDir;
	REDPORTIONDESC m_Desc;
	list<CGameObject*> m_pOther;
	_int a;
	_bool	bPlusY;
private:
	HRESULT SetUp_Components();

public:
	static CRedPortion* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END