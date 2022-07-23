#include "..\Public\Map_Manager.h"

IMPLEMENT_SINGLETON(CMap_Manager)

CMap_Manager::CMap_Manager()
{
}



HRESULT CMap_Manager::LoadMapData()
{
	list<CMap_Manager::CUBEDATA> testList = {
		CUBEDATA{ _float3(5.f, 1.f, 0.f), TEXT("")},
		CUBEDATA{ _float3(5.f, 0.f, 0.f), TEXT("")},
		CUBEDATA{ _float3(5.f, -1.f, 0.f), TEXT("")},
	};

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
