#include "pch.h"
#include "LootManager.h"

LootManager::LootManager() : m_CenterPos(),
m_ChestTexture("../Resources/Loot/Chest.png"),
m_PropTexture("../Resources/Loot/Poweruptears.png")
{
}

LootManager::~LootManager()
{
}

void LootManager::UpdateLoot()
{
	
}

void LootManager::DrawLoot() const
{
	for (size_t idX{0}; idX < m_chests.size();++idX)
	{
		m_chests[idX].Draw();
	}
}

void LootManager::CreateLootBox(Point2f centerposition)
{
	m_chests.push_back(Chest(&m_ChestTexture,centerposition));
}

void LootManager::DeleteChest()
{
	m_chests.pop_back();
}
