#include "pch.h"
#include "Spider.h"

Spider::Spider(Texture* texture, Point2f SpawnPos, Vector2f Velocity, int Health, int maxHealth) : BasicAI{ Point2f{SpawnPos},Vector2f{Velocity},Health,maxHealth,13,6 },
m_TextureSpider(texture)
/*m_HitBox(m_CenterPos.x - (m_TextureFly->GetWidth() / 5) / 2, m_CenterPos.y - m_TextureFly->GetHeight() / 2, m_TextureFly->GetWidth() / 5, m_TextureFly->GetHeight())*/
{
}

Spider::~Spider()
{
}

void Spider::Attack()
{
	std::cout << "Works" << std::endl;
}

void Spider::Draw() const
{
	m_TextureSpider->Draw(m_DstRect, m_srcRect);
	DrawHitbox();
}

void Spider::Update(float elapsedSec, const Point2f& pos)
{
	TimeCounter(elapsedSec);
	m_DstRect.width = 100.f;
	m_DstRect.height = 60.f;
	m_DstRect.left = m_CenterPos.x - m_DstRect.width / 2;
	m_DstRect.bottom = m_CenterPos.y - m_DstRect.height / 2;

	m_srcRect.width = 112.65;
	m_srcRect.height = 90;
	m_srcRect.left = (m_srcRect.width * m_AnimFrame);
	m_srcRect.bottom = 0;
	UpdateHitbox(Rectf{ (m_CenterPos.x - (m_TextureSpider->GetWidth() / 5) / 2) ,m_CenterPos.y - m_TextureSpider->GetHeight() / 2,m_TextureSpider->GetWidth() / 5,m_TextureSpider->GetHeight() });
	SetLocationOfPlayer(pos);
	CalculateDeltaPos(elapsedSec);

	m_CenterPos.x += DeltaPos.x;
	m_CenterPos.y += DeltaPos.y;
}

void Spider::TimeCounter(float elapsedTime)
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

void Spider::CheckIfHit(const Point2f pos, std::vector<Tear*>& activetears, const SoundManager& soundManager)
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

Rectf Spider::GetHitbox() const
{
	return m_HitBox;
}

void Spider::DrawHitbox()const
{
	utils::SetColor(Color4f{ 0.f,0.f,1.f,1.f });
	utils::DrawRect(m_CenterPos.x - (m_TextureSpider->GetWidth() / 5) / 2, m_CenterPos.y - m_TextureSpider->GetHeight() / 2, m_TextureSpider->GetWidth() / 5, m_TextureSpider->GetHeight(), 2);
	utils::SetColor(Color4f{ 0.f,1.f,0.f,1.f });
}