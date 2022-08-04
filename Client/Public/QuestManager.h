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


public:	//퀘스트의 상태를 변화시킴
	void QuestPrepare() { m_iQuestState = QUEST_PREPARE; }
	void QuestProgress() { m_iQuestState = QUEST_PROGRESS; }
	void QuestClear() { m_iQuestState = QUEST_CLEAR; }
	void QuestEnd() { m_iQuestState = QUEST_END; }
	
	//퀘스트의 상태를 리턴
	_uint Set_QuestState() { return m_iQuestState; }

	// 퀘스트의 시작과 끝을 리턴, 설정함
	void Check_End_Quest() { m_bCheckQuest = false; }
	void Check_Start_Quest() { m_bCheckQuest = true; }
	bool Check_Quest() { return m_bCheckQuest; }

	// 몬스터가 죽을때 인자로 몬스터의 이름을 넣고 호출시킴, 퀘스트의 클리어를 담당
	void Hunting(const _tchar* MonsterName);

	// 아이템을 먹을때 인자로 아이템의 이름을 넣음, 아이템 퀘스트 클리어를 담당
	void Eat_Item(const _tchar* ItemName);


	// 사냥한 몬스터 마릿수 리턴
	_uint Set_Slime(){ return m_iHuntSlime; }
	_uint Set_OrangeMushroom() { return m_iHuntOrangeMushroom; }
	_uint Set_StoneGolem() { return m_iHuntStoneGolem; }




	// 사냥한 모든 몬스터 초기화
	void Reset_Hunt() { m_iHuntSlime = 0; m_iHuntOrangeMushroom = 0; m_iHuntStoneGolem = 0; }

	// 몇번째 퀘스트인지를 GETSET
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

	//사냥한 몬스터를 갖고있는 변수
	_uint	m_iHuntSlime;
	_uint	m_iHuntOrangeMushroom;
	_uint	m_iHuntRibbonPig;
	_uint	m_iHuntStoneGolem;

	//획득한 아이템을 갖고있는 변수
	_uint	m_iRedShell;
	_uint	m_iBlueShell;
	_uint	m_iPigRibbon;

	// 몇번째 퀘스트인지
	_uint	m_iQuestNum;
};

END