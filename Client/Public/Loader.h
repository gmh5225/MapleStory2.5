#pragma once

#include "Client_Defines.h"
#include "Base.h"

/* Ư�� ������ ���� ���ҽ�, ��ü���� ���� �����ϴ� ��Ȱ�� �Ѵ�. */
/* ���꽺���帪�� �����Ͽ� �� �۾��� �����ϰԲ� �Ѵ�. */

BEGIN(Client)

class CLoader final : public CBase
{
public:
	CLoader(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLoader() = default;

public:
	LEVEL Get_NextLevelID() const {
		return m_eNextLevelID;
	}

	const _tchar* Get_LoadingText() const {
		return m_szLoadingText;
	}

	_bool Get_Finished() const {
		return m_isFinished;
	}

	CRITICAL_SECTION Get_CS() const {
		return m_CriticalSection;
	}

public:
	HRESULT Initialize(LEVEL eNextLevelID);
	HRESULT Loading_ForStatic();
	HRESULT Loading_ForGamePlayLevel();
	HRESULT Loading_ForHenesys();
	HRESULT Loading_ForElenya();
	HRESULT Loading_ForElenyaEnter();
	HRESULT Loading_ForElenyaGas();

	HRESULT Loading_ForDHenesys();
	HRESULT Loading_ForDHenesysHunting();
	HRESULT Loading_ForDElenyaEnter();
	HRESULT Loading_ForDElenya();
	HRESULT Loading_ForDBlackMageEnter();
	HRESULT Loading_ForDBlackMage();
	HRESULT Loading_ForDWhiteMage();



//��ü���� �ε��Լ�
private:
	HRESULT Load_Player_Object();
	HRESULT Load_PlayerSkill_Object();
	HRESULT Load_Monster_Object();
	HRESULT Load_Npc_Object();
	HRESULT Load_UI_Object();
	HRESULT Load_Model_Object();
	HRESULT Load_Item_Object();
	HRESULT	Load_Spawner_Object();
	HRESULT Load_Component();
	HRESULT Load_Map();
	HRESULT Load_Particle();

//�ؽ�ó �ε��Լ�
private:
	HRESULT Load_Player_Texture();
	HRESULT Load_Player_Skill_Texture();
	HRESULT Load_Monster_Texture();
	HRESULT Load_Npc_Texture();
	HRESULT Load_UI_Texture();
	HRESULT Load_Model_Texture();
	HRESULT Load_Item_Texture();
	HRESULT Load_Particle_Texture();



private:
	LPDIRECT3DDEVICE9	m_pGraphic_Device = nullptr;

private:
	HANDLE				m_hThread = 0;
	CRITICAL_SECTION	m_CriticalSection;
	LEVEL				m_eNextLevelID = LEVEL_END;

private:
	_tchar				m_szLoadingText[MAX_PATH] = TEXT("");
	_bool				m_isFinished = false;

public:
	static CLoader* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevelID);
	virtual void Free() override;
};

END