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
		_int 	r, g, b;
	}CUBEDATA;
	typedef struct tagModelDesc
	{
		_tchar  cModelName[256] = { 0 };
		_float3	vPos;
		_float3 vAix;
		_float fScale;
	}MODELDESC;

private:
	CMap_Manager();
	virtual ~CMap_Manager() = default;

public:
	void SetFildNames();
	list<_tchar*>* GetVoxelNames() { return &m_cVoxelNames; }
	
	HRESULT LoadMapData(HWND hWnd);
	list<CUBEDATA>* ReadMap(const _tchar* pMapTag);



	void LoadData(HWND hWnd);
	void LoadModel(HWND hWnd);
	void LoadModelState(HWND hWnd);

public:
	list<CUBEDATA>* Find_Map(const _tchar* pMapTag);
	list<MODELDESC>* Find_Model(const _tchar* pModelTag);


private: /* ���� Map���� ������ Ŀ���̳ʤ� */
	map<const _tchar*, list<CUBEDATA>>			m_MapPrototypes;
	typedef map<const _tchar*, list<CUBEDATA>>	MAPDATA;
	list<CMap_Manager::CUBEDATA> m_TempList;


	map<const _tchar*, list<CMap_Manager::MODELDESC>>			m_ModelPrototypes;
	// typedef map<const _tchar*, list<MODELDESC>>	MODELDATA;
	list<CMap_Manager::MODELDESC> m_TempModelList;

	list<string> m_VoxelNames;
	list<_tchar*> m_cVoxelNames;

	list<string> m_ModelNames;

public:
	virtual void Free() override;

};

END