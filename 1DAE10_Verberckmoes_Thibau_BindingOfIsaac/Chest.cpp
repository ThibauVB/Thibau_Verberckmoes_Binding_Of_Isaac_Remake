#include "pch.h"
#include "Chest.h"

Chest::Chest(Texture* texture, Point2f centerpos) :
m_ChestTexture(texture),
m_CenterPosition(centerpos)
{
}

Chest::~Chest()
{
}

void Chest::Draw() const
{
	m_ChestTexture->Draw();
}

void Chest::UpdateChest(const Point2f& pos)
{
	Point2f deltaPos;

	deltaPos.x = pos.x - m_CenterPosition.x;
	deltaPos.x = abs(deltaPos.x);
	deltaPos.y = pos.y - m_CenterPosition.y;
	deltaPos.y = abs(deltaPos.y);

	if (deltaPos.y < 50.f || deltaPos.x < 50.f)
	{
		std::cout << "inside range" << std::endl;
	}
}
