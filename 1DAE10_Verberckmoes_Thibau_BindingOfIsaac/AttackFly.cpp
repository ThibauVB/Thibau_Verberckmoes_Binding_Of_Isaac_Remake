#include "pch.h"
#include "AttackFly.h"

AttackFly::AttackFly(Texture* texture, Point2f SpawnPos, Vector2f Velocity, int Health, int maxHealth) : BasicAI{ Point2f{SpawnPos},Vector2f{Velocity},Health,maxHealth,25,5 },
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
	m_Texture->Draw(DstRect,srcRect);
}

void AttackFly::Update(float elapsedSec)
{
	TimeCounter(elapsedSec);
	DstRect.width = 70.f;
	DstRect.height = 60.f;
	DstRect.left = m_CenterPos.x - DstRect.width / 2;
	DstRect.bottom = m_CenterPos.y - DstRect.height / 2;

	srcRect.width = 92.5f;
	srcRect.height = 90;
	srcRect.left = 0 + (srcRect.width * m_AnimFrame);
	srcRect.bottom = 0;
}

void AttackFly::TimeCounter(float elapsedTime)
{
	m_TimePassedForAnimation += elapsedTime;
	if (m_TimePassedForAnimation >= 1.f / m_FramesPerSec)
	{
		m_AnimFrame++;
		if (m_AnimFrame >= m_NrOfFramesForBody)
		{
			m_AnimFrame = 0;
		}
		m_TimePassedForAnimation = 0;
	}
}

