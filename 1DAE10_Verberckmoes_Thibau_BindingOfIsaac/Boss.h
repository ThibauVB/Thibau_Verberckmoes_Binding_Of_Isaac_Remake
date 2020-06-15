#pragma once

#pragma once
#include "BasicAI.h"
class Boss : public BasicAI
{
public:
	explicit Boss(Texture* Texture, Point2f SpawnPos, Vector2f Velocity, int Health, int maxHealth);;
	~Boss();
	void Attack();
	void Draw()const;
	void Update(float elapsedSec, const Point2f& pos)override;
	void TimeCounter(float elapsedSec);
	void CheckIfHit(const Point2f pos, std::vector<Tear*>& activetears, const SoundManager& soundManager);
	Rectf GetHitbox() const;
	
private:
	Rectf m_srcRect, m_DstRect;
	Texture* m_TextureBoss;
	void DrawHitbox()const;
};
