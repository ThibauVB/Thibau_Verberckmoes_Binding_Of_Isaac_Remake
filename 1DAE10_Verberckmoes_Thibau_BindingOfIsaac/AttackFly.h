#pragma once
#include "BasicAI.h"
class AttackFly : public BasicAI
{
public:
	AttackFly(Texture* Texture, Point2f SpawnPos, Vector2f Velocity, int Health, int maxHealth);
	virtual ~AttackFly();
	void Attack();
	void Draw()const;
	void Update(float elapsedSec,const Point2f& pos);
	void TimeCounter(float elapsedSec);
	void CheckIfHit(const Point2f pos, std::vector<Tear*>& activetears);
private:
	Rectf srcRect, DstRect;
	Texture* m_TextureFly;
	void DrawHitbox()const;
};