#include "pch.h"
#include "AttackFly.h"

AttackFly::AttackFly(Texture* texture, Point2f SpawnPos, Vector2f Velocity, int Health, int maxHealth) : BasicAI{ Point2f{SpawnPos},Vector2f{Velocity},Health,maxHealth,25,5 },
	m_TextureFly(texture)
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
	m_TextureFly->Draw(DstRect,srcRect);
	DrawHitbox();
}

void AttackFly::Update(float elapsedSec, const Point2f& pos)
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
	UpdateHitbox(Rectf{ (m_CenterPos.x - (m_TextureFly->GetWidth() / 5) / 2) ,m_CenterPos.y - m_TextureFly->GetHeight() / 2,m_TextureFly->GetWidth() / 5,m_TextureFly->GetHeight()});
	SetLocationOfPlayer(pos);
	CalculateDeltaPos(elapsedSec);
	
	m_CenterPos.x += DeltaPos.x;
	m_CenterPos.y += DeltaPos.y;
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

void AttackFly::CheckIfHit(const Point2f pos, std::vector<Tear*>& activetears)
{
	if (utils::IsPointInRect(pos,m_HitBox))
	{
		for (int i{ 0 }; i < activetears.size(); ++i)
		{
			if (activetears[i]->GetPostion().x == pos.x && activetears[i]->GetPostion().y == pos.y)
			{
				activetears[i]->SetAliveState(false);
			}
		}
		AIHit();
	}
}

void AttackFly::DrawHitbox()const
{
	utils::SetColor(Color4f{ 0.f,0.f,1.f,1.f });
	utils::DrawRect(m_CenterPos.x-(m_TextureFly->GetWidth()/5)/2,m_CenterPos.y-m_TextureFly->GetHeight()/2,m_TextureFly->GetWidth()/5,m_TextureFly->GetHeight(),2);
	utils::SetColor(Color4f{ 0.f,1.f,0.f,1.f });
}

