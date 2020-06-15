#include "pch.h"
#include "Chest.h"

Chest::Chest(Texture* texture, Point2f centerpos) :
m_ChestTexture(texture),
m_CenterPosition(centerpos)
{
}

Chest::~Chest()
{
	delete m_ChestTexture;
}

void Chest::Draw() const
{
	m_ChestTexture->Draw(m_CenterPosition);
}

void Chest::UpdateChest(const Point2f& pos)
{
	Point2f deltaPos;

	deltaPos.x = pos.x - m_CenterPosition.x;
	deltaPos.x = abs(deltaPos.x);
	deltaPos.y = pos.y - m_CenterPosition.y;
	deltaPos.y = abs(deltaPos.y);

	if (utils::IsPointInRect(pos,m_hitbox))
	{
		std::cout << "inside range" << std::endl;
	}
}

void Chest::SetHitBox()
{
	m_hitbox.left = m_CenterPosition.x - m_ChestTexture->GetWidth() / 2;
	m_hitbox.bottom = m_CenterPosition.y - m_ChestTexture->GetHeight() / 2;
	m_hitbox.width = m_ChestTexture->GetWidth();
	m_hitbox.height = m_ChestTexture->GetHeight();
}
