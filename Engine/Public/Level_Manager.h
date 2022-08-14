#pragma once

#include "Base.h"

/* ���� ��������� ������ �����͸� ������ �ִ´�. */
/* ������ ƽ, ������ ����ȣ���Ѵ�. */
/* ��[����ü�ÿ� �������� ����,. ���ο�� ��ü�Ѵ�. */

BEGIN(Engine)

class CLevel_Manager final : public CBase
{
	DECLARE_SINGLETON(CLevel_Manager)
private:
	CLevel_Manager();
	virtual ~CLevel_Manager() = default;

public:
	/* �������� ����. ���ο�� ����. */
	HRESULT Open_Level(_uint iLevelIndex, class CLevel* pNewLevel);
	void Tick(_float fTimeDelta);
	HRESULT Render();
	HRESULT Reserve_Check(_uint iNumLevels);
	_uint Get_CurLevel() { return m_iCurrentLevelIndex; }

private:
	class CLevel*				m_pCurrentLevel = nullptr;
	_uint						m_iCurrentLevelIndex = 0;
	

public:
	virtual void Free() override;
};

END