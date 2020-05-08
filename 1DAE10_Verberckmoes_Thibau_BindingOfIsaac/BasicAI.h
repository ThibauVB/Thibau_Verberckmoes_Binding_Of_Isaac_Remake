#pragma once
#include "Texture.h"
#include "Tear.h"
class BasicAI
{
protected:
	explicit BasicAI(Point2f SpawnPos, Vector2f velocity, int Health, int maxHealth,int fps,int nrOfFrames);
public:
	virtual ~BasicAI();
	virtual void Draw()const;
	virtual void Update(float elapsedSec,const Point2f& pos);
	virtual void CheckIfHit(const Point2f pos, std::vector<Tear*>& activetears);
	void SetLocationOfPlayer(Point2f pos);
	int GetHealth()const;
protected:
	Point2f GetLocationOfPlayer()const;
	void UpdateHitbox(Rectf hitBox);
	void AIHit();
	void CalculateDeltaPos(float elapsedSec);
	Point2f m_CenterPos;
	Rectf m_HitBox;
	Vector2f m_Velocity;
	int m_Health;
	int m_MaxHealth;
	Texture* m_Texture;
	float m_TimePassedForAnimation;
	int m_FramesPerSec;
	int m_AnimFrame;
	int m_NrOfFramesForBody;
	Point2f m_LocationOfPlayer;
	Vector2f DeltaPos;
};

