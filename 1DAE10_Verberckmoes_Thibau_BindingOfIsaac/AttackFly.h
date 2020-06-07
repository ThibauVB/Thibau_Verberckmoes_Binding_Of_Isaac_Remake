#pragma once
#include "BasicAI.h"
class AttackFly : public BasicAI
{
public:
	explicit AttackFly(Texture* Texture, Point2f SpawnPos, Vector2f Velocity, int Health, int maxHealth);
	virtual ~AttackFly();
	void Attack();
	void Draw()const;
	void Update(float elapsedSec,const Point2f& pos);
	void TimeCounter(float elapsedSec);
	void CheckIfHit(const Point2f pos, std::vector<Tear*>& activetears, const SoundManager& soundManager);
	Rectf GetHitbox() const;
private:
	Rectf m_srcRect, m_DstRect;
	Texture* m_TextureFly;
	void DrawHitbox()const;
};