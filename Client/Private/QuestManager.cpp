#include "stdafx.h"
#include "..\Public\QuestManager.h"

IMPLEMENT_SINGLETON(CQuestManager)


CQuestManager::CQuestManager()
{
	m_iHuntSlime = 0;
	m_iHuntOrangeMushroom = 0;
	m_iHuntStoneGolem = 0;
	m_iQuestNum = QUEST_START;
	m_iRedShell = 0;
	m_iBlueShell = 0;
	m_iPigRibbon = 0;
	m_iSlimeEssence = 0;
	m_iStumpFirewood = 0;
	m_iGreenMushroom = 0;
}

void CQuestManager::Hunting(const _tchar * MonsterName)
{
	if (m_iQuestNum == 1)
	{
		if (wcscmp(MonsterName, TEXT("OrangeMushroom")) == 0 && m_iQuestState == QUEST_PROGRESS && m_iHuntOrangeMushroom < 10
			&& m_iQuestNum == QUEST_FIRST)
			++m_iHuntOrangeMushroom;
	}

	else if (m_iQuestNum == 3)
	{
		if (wcscmp(MonsterName, TEXT("StoneGolem")) == 0 && m_iQuestState == QUEST_PROGRESS && m_iHuntStoneGolem < 1)
			++m_iHuntStoneGolem;
	}
}

void CQuestManager::Eat_Item(const _tchar * ItemName)
{
	if (m_iQuestNum == 2)
	{
		if (wcscmp(ItemName, TEXT("RedShell")) == 0 && m_iQuestState == QUEST_PROGRESS && m_iRedShell < 7)
			++m_iRedShell;

		if (wcscmp(ItemName, TEXT("BlueShell")) == 0 && m_iQuestState == QUEST_PROGRESS && m_iBlueShell < 7)
			++m_iBlueShell;

		if (wcscmp(ItemName, TEXT("PigRibbon")) == 0 && m_iQuestState == QUEST_PROGRESS && m_iPigRibbon < 10)
			++m_iPigRibbon;

		if (m_iPigRibbon == 10 && m_iBlueShell == 7 && m_iRedShell == 7)
			QuestClear();
	}

	if (m_iQuestNum == 4)
	{
		if (wcscmp(ItemName, TEXT("SlimeEssence")) == 0 && m_iQuestState == QUEST_PROGRESS && m_iSlimeEssence < 6)
			++m_iSlimeEssence;
		if (wcscmp(ItemName, TEXT("StumpFirewood")) == 0 && m_iQuestState == QUEST_PROGRESS && m_iStumpFirewood < 6)
			++m_iStumpFirewood;
		if (wcscmp(ItemName, TEXT("GreenMushroom")) == 0 && m_iQuestState == QUEST_PROGRESS && m_iGreenMushroom < 6)
			++m_iGreenMushroom;

		if (m_iSlimeEssence == 6 && m_iStumpFirewood == 6 && m_iGreenMushroom == 6)
			QuestClear();
	}
}

void CQuestManager::Free()
{
}


