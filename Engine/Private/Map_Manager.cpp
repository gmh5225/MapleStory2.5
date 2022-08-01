#include "..\Public\Map_Manager.h"

IMPLEMENT_SINGLETON(CMap_Manager)

CMap_Manager::CMap_Manager()
{
	SetFildNames();
}


void CMap_Manager::SetFildNames()
{
	m_VoxelNames.push_back(string{ "Wood" });
	m_VoxelNames.push_back(string{ "MushHouse" });

	m_ModelNames.push_back(string{ "Test_Map_Model" });
}


HRESULT CMap_Manager::LoadMapData(HWND hWnd)
{
	LoadData(hWnd);
	LoadModel(hWnd);
	LoadModelState(hWnd);

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


void CMap_Manager::LoadData(HWND hWnd)
{
	HANDLE		hFile = CreateFile(L"../Data/Map/MapData.dat",
		GENERIC_READ,				
		NULL,						
		NULL,						
		OPEN_EXISTING,				
		FILE_ATTRIBUTE_NORMAL,		
		NULL);						

	

	DWORD		dwByte = 0;
	CMap_Manager::CUBEDATA		tInfo{};

	wchar_t* sFildName = new wchar_t[256];
	ReadFile(hFile, sFildName, sizeof(wchar_t) * 256, &dwByte, nullptr);


	_float4x4 RotationMatrix;
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationAxis(&RotationMatrix, &_float3{ 0.f, 1.f, 0.f }, D3DXToRadian(45.f));



	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(CMap_Manager::CUBEDATA), &dwByte, nullptr);

		if (0 == dwByte)	// 더이상 읽을 데이터가 없을 경우
			break;

		CMap_Manager::CUBEDATA CubeData(tInfo);


		D3DXVec3TransformCoord(&CubeData.vPos, &CubeData.vPos, &RotationMatrix);
		// CubeData.vPos.y += 10.f;


		m_TempList.push_back(CubeData);
	}

	const wchar_t* pTemp = sFildName;

	m_MapPrototypes.emplace(pTemp, m_TempList);
	m_TempList.clear();

	// 3. 파일 소멸
	CloseHandle(hFile);

}
void CMap_Manager::LoadModel(HWND hWnd)
{
	for (auto& name : m_VoxelNames)
	{

		string FilePath = name;
		string temp = "../Data/Voxel/";

		FilePath = temp + FilePath + ".dat";

		wchar_t RealPath[256] = { 0 };

		for (int i = 0; i < FilePath.size(); i++)
		{
			RealPath[i] = FilePath[i];
		}





		HANDLE		hFile = CreateFile(RealPath,
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		DWORD		dwByte = 0;
		CMap_Manager::CUBEDATA		tInfo{};

		wchar_t* sFildName = new wchar_t[256];
		ReadFile(hFile, sFildName, sizeof(wchar_t) * 256, &dwByte, nullptr);

		while (true)
		{
			ReadFile(hFile, &tInfo, sizeof(CMap_Manager::CUBEDATA), &dwByte, nullptr);

			if (0 == dwByte)	// 더이상 읽을 데이터가 없을 경우
				break;

			CMap_Manager::CUBEDATA CubeData(tInfo);


			m_TempList.push_back(CubeData);
		}

		const wchar_t* pTemp = sFildName;

		m_MapPrototypes.emplace(pTemp, m_TempList);
		m_TempList.clear();

		// 3. 파일 소멸
		CloseHandle(hFile);

	}

}
void CMap_Manager::LoadModelState(HWND hWnd)
{
	for (auto& name : m_ModelNames)
	{

		string FilePath = name;
		string temp = "../Data/Model/";

		FilePath = temp + FilePath + ".dat";

		wchar_t RealPath[256] = { 0 };

		for (int i = 0; i < FilePath.size(); i++)
		{
			RealPath[i] = FilePath[i];
		}





		HANDLE		hFile = CreateFile(RealPath,
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		DWORD		dwByte = 0;
		CMap_Manager::MODELDESC		tInfo{};

		wchar_t* sFildName = new wchar_t[256];
		ReadFile(hFile, sFildName, sizeof(wchar_t) * 256, &dwByte, nullptr);

		while (true)
		{
			ReadFile(hFile, &tInfo, sizeof(CMap_Manager::MODELDESC), &dwByte, nullptr);

			if (0 == dwByte)	// 더이상 읽을 데이터가 없을 경우
				break;

			CMap_Manager::MODELDESC CubeData(tInfo);


			m_TempModelList.push_back(CubeData);
		}

		const wchar_t* pTemp = sFildName;

		m_ModelPrototypes.emplace(pTemp, m_TempModelList);
		m_TempModelList.clear();

		// 3. 파일 소멸
		CloseHandle(hFile);

	}
}



void CMap_Manager::Free()
{
	for (auto& tag : m_MapPrototypes)
		delete tag.first;
	for (auto& tag : m_ModelPrototypes)
		delete tag.first;

}


