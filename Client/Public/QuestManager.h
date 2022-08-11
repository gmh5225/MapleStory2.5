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
	void Tick();


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
	_uint Set_GAS() { return m_iGAS; }

	// ���� �����ۼ� ����
	_uint Set_RedShell() { return m_iRedShell; }
	_uint Set_BlueShell() { return m_iBlueShell; }
	_uint Set_PigRibbon() { return m_iPigRibbon; }
	_uint Set_SlimeEssence() { return m_iSlimeEssence; }
	_uint Set_StumpFirewood() { return m_iStumpFirewood; }
	_uint Set_GreenMushroom() { return m_iGreenMushroom; }

	void Get_RedShell(_int RedShell) { m_iRedShell = RedShell; }
	void Get_BlueShell(_int BlueShell) { m_iBlueShell = BlueShell; }
	void Get_PigRibbon(_int PigRibbon) { m_iPigRibbon = PigRibbon; }
	void Get_SlimeEssence(_int SlimeEssence) { m_iSlimeEssence = SlimeEssence; }
	void Get_StumpFirewood(_int StumpFirewood) { m_iStumpFirewood = StumpFirewood; }
	void Get_GreenMushroom(_int GreenMushroom) { m_iGreenMushroom = GreenMushroom; }

	// ����� ��� ���� �ʱ�ȭ
	void Reset_Hunt() { m_iHuntSlime = 0; m_iHuntOrangeMushroom = 0; m_iHuntStoneGolem = 0; }

	// ���° ����Ʈ������ GETSET
	void Set_First() { m_iQuestNum = QUEST_FIRST; }
	void Set_Second() { m_iQuestNum = QUEST_SECOND; }
	void Set_Third() { m_iQuestNum = QUEST_THIRD; }
	void Set_Fourth() { m_iQuestNum = QUEST_FOURTH; }
	void Set_Fifth() { m_iQuestNum = QUEST_FIFTH; }
	void Set_Sixth() { m_iQuestNum = QUEST_SIXTH; }
	_uint Get_QuestNum() { return m_iQuestNum; }

public:
	virtual void Free() override;


public:
	enum QUEST_STATE { QUEST_PREPARE, QUEST_PROGRESS, QUEST_CLEAR, QUEST_END};
	enum QUEST_HUNT { HUNT_SLIME, HUNT_ORANGEMUSHROOM, HUNT_END};
	enum QUEST_NUM { QUEST_START, QUEST_FIRST, QUEST_SECOND, QUEST_THIRD , QUEST_FOURTH, QUEST_FIFTH, QUEST_SIXTH};

private:
	_uint	m_iQuestState;
	_uint	m_iHunt;
	bool	m_bCheckQuest;

	//����� ���͸� �����ִ� ����
	_uint	m_iHuntSlime;
	_uint	m_iHuntOrangeMushroom;
	_uint	m_iHuntRibbonPig;
	_uint	m_iHuntStoneGolem;
	_uint	m_iGAS;

	//ȹ���� �������� �����ִ� ����
	_uint	m_iRedShell;
	_uint	m_iBlueShell;
	_uint	m_iPigRibbon;

	_uint	m_iSlimeEssence;
	_uint	m_iStumpFirewood;
	_uint	m_iGreenMushroom;

	// ���° ����Ʈ����
	_uint	m_iQuestNum;
};

END