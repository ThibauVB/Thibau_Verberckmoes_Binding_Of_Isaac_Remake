#pragma once
#include "pch.h"
#include "Texture.h"
#include "Chest.h"

class LootManager
{
public:
	explicit LootManager();
	~LootManager();

	void UpdateLoot();
	void DrawLoot()const;
	void CreateLootBox(Point2f centerposition);
private:
	std::vector<Chest> m_chests;
	Point2f m_CenterPos;
	Texture m_ChestTexture;
	Texture m_PropTexture;
};
