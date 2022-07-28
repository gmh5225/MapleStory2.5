#include "..\Public\Map_Manager.h"

IMPLEMENT_SINGLETON(CMap_Manager)

CMap_Manager::CMap_Manager()
{
}



HRESULT CMap_Manager::LoadMapData(HWND hWnd)
{
	LoadData(hWnd);


	//for (_int i = -10; i < 10; i++)
	//{
	//	for (_int j = -10; j < 10; j++)
	//	{
	//		CUBEDATA d = { _float3(i, -0.5f, j), 0 };
	//		m_TempList.push_back(d);
	//	}
	//}

	// 1. y축 45도 회전 행렬을 구한다.
	_float4x4 RotationMatrix;
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationAxis(&RotationMatrix, &_float3{0.f, 1.f, 0.f}, D3DXToRadian(45.f));
	
	// 2. 각 큐브 포스에 회전행렬을 곱하고 다시 대입해 준다.
	for (auto& CubeData : m_TempList)
	{
		D3DXVec3TransformCoord(&CubeData.vPos, &CubeData.vPos, &RotationMatrix);
		CubeData.vPos.y += 10.f;
	}

	m_MapPrototypes.emplace(TEXT("Map_Henesys"), m_TempList);

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
	HANDLE		hFile = CreateFile(L"../Data/MapData.dat",			// 파일 경로와 이름 명시
		GENERIC_READ,				// 파일 접근 모드 (GENERIC_WRITE 쓰기 전용, GENERIC_READ 읽기 전용)
		NULL,						// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가, NULL인 경우 공유하지 않는다
		NULL,						// 보안 속성, 기본값	
		OPEN_EXISTING,				// 생성 방식, CREATE_ALWAYS는 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXISTING 파일이 있을 경우에면 열기
		FILE_ATTRIBUTE_NORMAL,		// 파일 속성(읽기 전용, 숨기 등), FILE_ATTRIBUTE_NORMAL 아무런 속성이 없는 일반 파일 생성
		NULL);						// 생성도리 파일의 속성을 제공할 템플릿 파일, 우리는 사용하지 않아서 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// 팝업 창을 출력해주는 기능의 함수
		// 1. 핸들 2. 팝업 창에 띄우고자하는 메시지 3. 팝업 창 이름 4. 버튼 속성
		// MessageBox(hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. 파일 쓰기

	DWORD		dwByte = 0;
	CMap_Manager::CUBEDATA		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(CMap_Manager::CUBEDATA), &dwByte, nullptr);

		if (0 == dwByte)	// 더이상 읽을 데이터가 없을 경우
			break;

		m_TempList.push_back(CMap_Manager::CUBEDATA(tInfo));
	}


	// 3. 파일 소멸
	CloseHandle(hFile);

}


void CMap_Manager::Free()
{

}

