#pragma once
#include "BasicAI.h"
class AttackFly : public BasicAI
{
public:
	AttackFly(Texture* Texture, Point2f SpawnPos, Vector2f Velocity, int Health, int maxHealth);
	virtual ~AttackFly();
	void Attack();
	void Draw()const;
private:
	Texture* m_Texture;
};