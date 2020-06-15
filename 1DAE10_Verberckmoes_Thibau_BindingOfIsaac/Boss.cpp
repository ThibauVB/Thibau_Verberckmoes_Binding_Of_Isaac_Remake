﻿#include "pch.h"
#include "Boss.h"

Boss::Boss(Texture* texture, Point2f SpawnPos, Vector2f Velocity, int Health, int maxHealth) : BasicAI{ Point2f{SpawnPos},Vector2f{Velocity},Health,maxHealth,10,6 },
m_TextureBoss(texture)
/*m_HitBox(m_CenterPos.x - (m_TextureFly->GetWidth() / 5) / 2, m_CenterPos.y - m_TextureFly->GetHeight() / 2, m_TextureFly->GetWidth() / 5, m_TextureFly->GetHeight())*/
{
}

Boss::~Boss()
{
}

void Boss::Attack()
{
	std::cout << "Works" << std::endl;
}

void Boss::Draw() const
{
	m_TextureBoss->Draw(m_DstRect, m_srcRect);
	//DrawHitbox();
}

void Boss::Update(float elapsedSec, const Point2f& pos)
{
	TimeCounter(elapsedSec);
	m_DstRect.width = 130.f;
	m_DstRect.height = 155.f;
	m_DstRect.left = m_CenterPos.x - m_DstRect.width / 2;
	m_DstRect.bottom = m_CenterPos.y - m_DstRect.height / 2;

	m_srcRect.width = 130;
	m_srcRect.height = 155;
	m_srcRect.left = (m_srcRect.width * m_AnimFrame);
	m_srcRect.bottom = 0;
	UpdateHitbox(Rectf{ (m_CenterPos.x - (m_TextureBoss->GetWidth() / 5) / 2) ,m_CenterPos.y - m_TextureBoss->GetHeight() / 2,m_TextureBoss->GetWidth() / 5,m_TextureBoss->GetHeight() });
	SetLocationOfPlayer(pos);
	CalculateDeltaPos(elapsedSec);

	m_CenterPos.x += DeltaPos.x;
	m_CenterPos.y += DeltaPos.y;
}

void Boss::TimeCounter(float elapsedTime)
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

void Boss::CheckIfHit(const Point2f pos, std::vector<Tear*>& activetears, const SoundManager& soundManager)
{
	if (utils::IsPointInRect(pos, m_HitBox))
	{
		for (int i{ 0 }; i < activetears.size(); ++i)
		{
			if (activetears[i]->GetPostion().x == pos.x && activetears[i]->GetPostion().y == pos.y)
			{
				activetears[i]->SetAliveState(false);
				soundManager.PlaytearDestroySound();
			}
		}
		AIHit();
	}
}

Rectf Boss::GetHitbox() const
{
	return m_HitBox;
}

void Boss::DrawHitbox()const
{
	utils::SetColor(Color4f{ 0.f,0.f,1.f,1.f });
	utils::DrawRect(m_CenterPos.x - (m_TextureBoss->GetWidth() / 5) / 2, m_CenterPos.y - m_TextureBoss->GetHeight() / 2, m_TextureBoss->GetWidth() / 5, m_TextureBoss->GetHeight(), 2);
	utils::SetColor(Color4f{ 0.f,1.f,0.f,1.f });
}