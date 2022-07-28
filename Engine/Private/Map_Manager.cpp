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

	// 1. y�� 45�� ȸ�� ����� ���Ѵ�.
	_float4x4 RotationMatrix;
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationAxis(&RotationMatrix, &_float3{0.f, 1.f, 0.f}, D3DXToRadian(45.f));
	
	// 2. �� ť�� ������ ȸ������� ���ϰ� �ٽ� ������ �ش�.
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
	HANDLE		hFile = CreateFile(L"../Data/MapData.dat",			// ���� ��ο� �̸� ���
		GENERIC_READ,				// ���� ���� ��� (GENERIC_WRITE ���� ����, GENERIC_READ �б� ����)
		NULL,						// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�, NULL�� ��� �������� �ʴ´�
		NULL,						// ���� �Ӽ�, �⺻��	
		OPEN_EXISTING,				// ���� ���, CREATE_ALWAYS�� ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXISTING ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,		// ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ��� �Ӽ��� ���� �Ϲ� ���� ����
		NULL);						// �������� ������ �Ӽ��� ������ ���ø� ����, �츮�� ������� �ʾƼ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// �˾� â�� ������ִ� ����� �Լ�
		// 1. �ڵ� 2. �˾� â�� �������ϴ� �޽��� 3. �˾� â �̸� 4. ��ư �Ӽ�
		// MessageBox(hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. ���� ����

	DWORD		dwByte = 0;
	CMap_Manager::CUBEDATA		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(CMap_Manager::CUBEDATA), &dwByte, nullptr);

		if (0 == dwByte)	// ���̻� ���� �����Ͱ� ���� ���
			break;

		m_TempList.push_back(CMap_Manager::CUBEDATA(tInfo));
	}


	// 3. ���� �Ҹ�
	CloseHandle(hFile);

}


void CMap_Manager::Free()
{

}

