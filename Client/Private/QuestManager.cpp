#include "stdafx.h"
#include "..\Public\QuestManager.h"

IMPLEMENT_SINGLETON(CQuestManager)


CQuestManager::CQuestManager()
{
	m_iHuntSlime = 0;
	m_iHuntOrangeMushroom = 0;
}

void CQuestManager::Hunting(const _tchar * MonsterName)
{
	if (wcscmp(MonsterName, TEXT("Slime")) == 0 && m_iQuestState == QUEST_PROGRESS)
		++m_iHuntSlime;

	if (wcscmp(MonsterName, TEXT("OrangeMushroom")) == 0 && m_iQuestState == QUEST_PROGRESS && m_iHuntOrangeMushroom < 10)
		++m_iHuntOrangeMushroom;

}

void CQuestManager::Free()
{
}


