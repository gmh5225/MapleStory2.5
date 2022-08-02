#include "stdafx.h"
#include "..\Public\QuestManager.h"

IMPLEMENT_SINGLETON(CQuestManager)


CQuestManager::CQuestManager()
{
	m_iHuntSlime = 0;
	m_iHuntOrangeMushroom = 0;
	m_iHuntStoneGolem = 0;
	m_iQuestNum = QUEST_START;
}

void CQuestManager::Hunting(const _tchar * MonsterName)
{
	if (wcscmp(MonsterName, TEXT("Slime")) == 0 && m_iQuestState == QUEST_PROGRESS)
		++m_iHuntSlime;

	if (wcscmp(MonsterName, TEXT("OrangeMushroom")) == 0 && m_iQuestState == QUEST_PROGRESS && m_iHuntOrangeMushroom < 10
		&& m_iQuestNum == QUEST_FIRST)
		++m_iHuntOrangeMushroom;

	if (wcscmp(MonsterName, TEXT("StoneGolem")) == 0 && m_iQuestState == QUEST_PROGRESS && m_iHuntStoneGolem < 1)
		++m_iHuntStoneGolem;

}

void CQuestManager::Free()
{
}


