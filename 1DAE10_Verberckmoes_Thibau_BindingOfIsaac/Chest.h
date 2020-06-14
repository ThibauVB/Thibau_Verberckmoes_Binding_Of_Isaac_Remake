#pragma once
#include "LootManager.h"
class Chest
{
public:
	Chest(Texture& texture);
	~Chest();
	void Draw() const;
private:
	Texture* m_ChestTexture;
};
