#pragma once

/* Ư�� ������ ���Ǵ� ��ü������ ��Ƽ� �����صγ�. */
/* �����ϰ� �մ� ��ü���� Tick�� ȣ�����ش�. */

#include "Base.h"

BEGIN(Engine)

class CMap_Manager final : public CBase
{
	DECLARE_SINGLETON(CMap_Manager)

public:
	typedef struct tagCubeDATA
	{
		_float3	vPos;
		_int	iIndex;
	}CUBEDATA;

private:
	CMap_Manager();
	virtual ~CMap_Manager() = default;

public:
	HRESULT LoadMapData(HWND hWnd);
	list<CUBEDATA>* ReadMap(const _tchar* pMapTag);

	void LoadData(HWND hWnd);

private:
	list<CUBEDATA>* Find_Map(const _tchar* pMapTag);


private: /* ���� Map���� ������ Ŀ���̳ʤ� */
	map<const _tchar*, list<CUBEDATA>>			m_MapPrototypes;
	typedef map<const _tchar*, list<CUBEDATA>>	MAPDATA;

	list<CMap_Manager::CUBEDATA> m_TempList;

public:
	virtual void Free() override;

};

END