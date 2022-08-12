#include "stdafx.h"
#include "..\Public\QuestManager.h"
#include "ItemInfo.h"

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

void CQuestManager::Tick()
{

	if (m_iQuestNum == 5)
	{
		if (m_iGAS == 1)
			QuestClear();
	}

	if (m_iQuestNum == 2)
	{
		CItemInfo* RedSnailInfo = CInvenManager::Get_Instance()->Get_ItemInfo(L"RedSnailInfo", CInvenManager::TYPE_STUFF);
		CItemInfo* BlueSnailInfo = CInvenManager::Get_Instance()->Get_ItemInfo(L"BlueSnailInfo", CInvenManager::TYPE_STUFF);
		CItemInfo* RibbonPigInfo = CInvenManager::Get_Instance()->Get_ItemInfo(L"RibbonPigInfo", CInvenManager::TYPE_STUFF);


		m_iRedShell = RedSnailInfo->Get_NowNum();
		m_iBlueShell = BlueSnailInfo->Get_NowNum();
		m_iPigRibbon = RibbonPigInfo->Get_NowNum();

		if (m_iRedShell >= 2 && m_iBlueShell >= 2 && m_iPigRibbon >= 2)
			QuestClear();
	}

	if (m_iQuestNum == 4)
	{
		CItemInfo* SlimeInfo = CInvenManager::Get_Instance()->Get_ItemInfo(L"SlimeInfo", CInvenManager::TYPE_STUFF);
		CItemInfo* GoStumpInfo = CInvenManager::Get_Instance()->Get_ItemInfo(L"GoStumpInfo", CInvenManager::TYPE_STUFF);
		CItemInfo* GreenMushroomInfo = CInvenManager::Get_Instance()->Get_ItemInfo(L"GreenMushroomInfo", CInvenManager::TYPE_STUFF);

		m_iSlimeEssence = SlimeInfo->Get_NowNum();
		m_iStumpFirewood = GoStumpInfo->Get_NowNum();
		m_iGreenMushroom = GreenMushroomInfo->Get_NowNum();

		if (m_iSlimeEssence >= 2 && m_iStumpFirewood >= 2 && m_iGreenMushroom >= 2)
			QuestClear();
	}

}

void CQuestManager::Hunting(const _tchar * MonsterName)
{
	if (m_iQuestNum == 1)
	{
		if (wcscmp(MonsterName, TEXT("OrangeMushroom")) == 0 && m_iQuestState == QUEST_PROGRESS && m_iHuntOrangeMushroom < 10
			&& m_iQuestNum == QUEST_FIRST)
			m_iHuntOrangeMushroom += 2;
	}

	else if (m_iQuestNum == 3)
	{
		if (wcscmp(MonsterName, TEXT("BlueMushmom")) == 0 && m_iQuestState == QUEST_PROGRESS && m_iHuntStoneGolem < 1)
			++m_iHuntStoneGolem;
	}

	else if (m_iQuestNum == 5)
	{
		if (wcscmp(MonsterName, TEXT("GAS")) == 0 && m_iQuestState == QUEST_PROGRESS && m_iGAS < 1)
			++m_iGAS;
	}
}

void CQuestManager::Eat_Item(const _tchar * ItemName)
{
}

void CQuestManager::Free()
{
}


