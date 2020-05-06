#pragma once
#include "Texture.h"

class BasicAI
{
protected:
	explicit BasicAI(Point2f SpawnPos, Vector2f velocity, int Health, int maxHealth,int fps,int nrOfFrames);
public:
	virtual ~BasicAI();
	virtual void Draw()const;
	virtual void Update(float elapsedSec);
protected:
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
};

