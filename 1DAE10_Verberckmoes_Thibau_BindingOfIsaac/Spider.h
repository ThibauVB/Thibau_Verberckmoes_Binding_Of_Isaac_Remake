#pragma once
#include "BasicAI.h"
class Spider : public BasicAI
{
public:
	explicit Spider(Texture* Texture, Point2f SpawnPos, Vector2f Velocity, int Health, int maxHealth);;
	~Spider();
	void Attack();
	void Draw()const;
	void Update(float elapsedSec, const Point2f& pos)override;
	void TimeCounter(float elapsedSec);
	void CheckIfHit(const Point2f pos, std::vector<Tear*>& activetears, const SoundManager& soundManager);
	Rectf GetHitbox() const;
private:
	Rectf m_srcRect, m_DstRect;
	Texture* m_TextureSpider;
	void DrawHitbox()const;
};
