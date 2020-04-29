#include "pch.h"
#include "AttackFly.h"

AttackFly::AttackFly(Texture* texture, Point2f SpawnPos, Vector2f Velocity, int Health, int maxHealth) : BasicAI{ Point2f{SpawnPos},Vector2f{Velocity},Health,maxHealth },
	m_Texture(texture)
{
}

AttackFly::~AttackFly()
{
}

void AttackFly::Attack()
{
	std::cout << "Works" << std::endl;
}

void AttackFly::Draw() const
{
	m_Texture->Draw(m_CenterPos);
}

