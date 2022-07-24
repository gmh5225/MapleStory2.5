#include "..\Public\Map_Manager.h"

IMPLEMENT_SINGLETON(CMap_Manager)

CMap_Manager::CMap_Manager()
{
}



HRESULT CMap_Manager::LoadMapData()
{
	list<CMap_Manager::CUBEDATA> testList;
	for (_int i = -20; i < 20; i++)
	{
		for (int j = -20; j < 20; j++)
		{
			testList.push_back(CUBEDATA{ _float3((_float)j, -0.5f, (_float)i), TEXT("") });
		}
	}

	// 1. y축 45도 회전 행렬을 구한다.
	_float4x4 RotationMatrix;
	D3DXMatrixRotationAxis(&RotationMatrix, &_float3{0.f, 1.f, 0.f}, 45.f);
	
	// 2. 각 큐브 포스에 회전행렬을 곱하고 다시 대입해 준다.
	for (auto& CubeData : testList)
	{
		_float3 temp;
		D3DXVec3TransformCoord(&temp, &CubeData.vPos, &RotationMatrix);
		CubeData.vPos = temp;
	}

	m_MapPrototypes.emplace(TEXT("Map_Henesys"), testList);

	return S_OK;
}

list<CMap_Manager::CUBEDATA>* CMap_Manager::ReadMap(const _tchar * pMapTag)
{
	list<CUBEDATA>* tempList = Find_Map(pMapTag);
	if (nullptr == tempList)
		return nullptr;

	return tempList;
}


list<CMap_Manager::CUBEDATA>* CMap_Manager::Find_Map(const _tchar * pMapTag)
{
	auto	iter = find_if(m_MapPrototypes.begin(), m_MapPrototypes.end(), CTag_Finder(pMapTag));

	if (iter == m_MapPrototypes.end())
		return nullptr;

	return &(iter->second);
}


void CMap_Manager::Free()
{

}
