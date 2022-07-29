#include "stdafx.h"
#include "..\Public\QuestManager.h"

IMPLEMENT_SINGLETON(CQuestManager)


CQuestManager::CQuestManager()
{
	m_iHuntSlime = 0;
}

void CQuestManager::Hunting(const _tchar * MonsterName)
{
	if (wcscmp(MonsterName, TEXT("Slime")) == 0)
		++m_iHuntSlime;

	if (m_iHuntSlime == 1)
		QuestProgressed();
}

void CQuestManager::Free()
{
}


