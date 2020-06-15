#pragma once
#include "pch.h"
#include "Texture.h"
class Chest
{
public:
	Chest(Texture* texture,Point2f centerpos);
	~Chest();
	void Draw() const;
	void UpdateChest(const Point2f& pos);
private:
	Texture* m_ChestTexture;
	Point2f m_CenterPosition;
};
