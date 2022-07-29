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


public:
	void QuestPrepared() { m_iQuestState = QUEST_PROGRESS; }
	void QuestProgressed() { m_iQuestState = QUEST_CLEAR; }
	void QuestCleared() { m_iQuestState = QUEST_END; }
	void QuestStart() { m_iQuestState = QUEST_PREPARE; }
	_uint Set_QuestState() { return m_iQuestState; }

	void Check_End_Quest() { m_bCheckQuest = false; }
	void Check_Start_Quest() { m_bCheckQuest = true; }
	bool Check_Quest() { return m_bCheckQuest; }

	void Hunting(const _tchar* MonsterName);

	_uint Set_Slime(){ return m_iHuntSlime; }

	// 사냥한 모든 몬스터 초기화
	void Reset_Hunt() { m_iHuntSlime = 0; }

public:
	virtual void Free() override;


public:
	enum QUEST_STATE { QUEST_PREPARE, QUEST_PROGRESS, QUEST_CLEAR, QUEST_END};
	enum QUEST_HUNT { HUNT_SLIME, HUNT_ORANGEMUSHROOM, HUNT_END};

private:
	_uint	m_iQuestState;
	_uint	m_iHunt;
	bool	m_bCheckQuest;

	_uint	m_iHuntSlime;
};

END