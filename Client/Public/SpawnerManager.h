#pragma once

#include "Client_Defines.h"
#include "Base.h"
#include "Spawner.h"

BEGIN(Client)

class CSpawnerManager final : CBase
{
	DECLARE_SINGLETON(CSpawnerManager)

public:
	CSpawnerManager();
	virtual ~CSpawnerManager() = default;


public:
	void Tick(_float fTimeDelta);
	void LateTick(_float fTimeDelta);

public:

	void Add_Spawner(void* pArg);
	// ���͸� ���ؼ� �������� �ε����� Ȯ���ϴ� �Լ�
	void Check_MonsterIndex(_int index);
	void Add_SpawnerInfo(CSpawner* Spawner) { m_SpawnerList.push_back(Spawner); }

	void Clear();

public:
	virtual void Free() override;

private:
		//int	monstercount- �������� �ε����� �޾ƿ�
	_uint	m_iIndexNum;
	list<CSpawner*>			m_SpawnerList;
};

END