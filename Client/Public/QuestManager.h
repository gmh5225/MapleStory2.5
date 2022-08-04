#pragma once

#include "Client_Defines.h"
#include "Base.h"

BEGIN(Client)

class CQuestManager final : CBase
{
	DECLARE_SINGLETON(CQuestManager)

public:
	CQuestManager();
	virtual ~CQuestManager() = default;


public:	//����Ʈ�� ���¸� ��ȭ��Ŵ
	void QuestPrepare() { m_iQuestState = QUEST_PREPARE; }
	void QuestProgress() { m_iQuestState = QUEST_PROGRESS; }
	void QuestClear() { m_iQuestState = QUEST_CLEAR; }
	void QuestEnd() { m_iQuestState = QUEST_END; }
	
	//����Ʈ�� ���¸� ����
	_uint Set_QuestState() { return m_iQuestState; }

	// ����Ʈ�� ���۰� ���� ����, ������
	void Check_End_Quest() { m_bCheckQuest = false; }
	void Check_Start_Quest() { m_bCheckQuest = true; }
	bool Check_Quest() { return m_bCheckQuest; }

	// ���Ͱ� ������ ���ڷ� ������ �̸��� �ְ� ȣ���Ŵ, ����Ʈ�� Ŭ��� ���
	void Hunting(const _tchar* MonsterName);

	// �������� ������ ���ڷ� �������� �̸��� ����, ������ ����Ʈ Ŭ��� ���
	void Eat_Item(const _tchar* ItemName);


	// ����� ���� ������ ����
	_uint Set_Slime(){ return m_iHuntSlime; }
	_uint Set_OrangeMushroom() { return m_iHuntOrangeMushroom; }
	_uint Set_StoneGolem() { return m_iHuntStoneGolem; }




	// ����� ��� ���� �ʱ�ȭ
	void Reset_Hunt() { m_iHuntSlime = 0; m_iHuntOrangeMushroom = 0; m_iHuntStoneGolem = 0; }

	// ���° ����Ʈ������ GETSET
	void Set_First() { m_iQuestNum = QUEST_FIRST; }
	void Set_Second() { m_iQuestNum = QUEST_SECOND; }
	_uint Get_QuestNum() { return m_iQuestNum; }

public:
	virtual void Free() override;


public:
	enum QUEST_STATE { QUEST_PREPARE, QUEST_PROGRESS, QUEST_CLEAR, QUEST_END};
	enum QUEST_HUNT { HUNT_SLIME, HUNT_ORANGEMUSHROOM, HUNT_END};
	enum QUEST_NUM { QUEST_START, QUEST_FIRST, QUEST_SECOND, QUEST_THIRD };

private:
	_uint	m_iQuestState;
	_uint	m_iHunt;
	bool	m_bCheckQuest;

	//����� ���͸� �����ִ� ����
	_uint	m_iHuntSlime;
	_uint	m_iHuntOrangeMushroom;
	_uint	m_iHuntRibbonPig;
	_uint	m_iHuntStoneGolem;

	//ȹ���� �������� �����ִ� ����
	_uint	m_iRedShell;
	_uint	m_iBlueShell;
	_uint	m_iPigRibbon;

	// ���° ����Ʈ����
	_uint	m_iQuestNum;
};

END