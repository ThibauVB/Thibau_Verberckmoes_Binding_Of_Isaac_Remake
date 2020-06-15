#include "pch.h"
#include "UImanager.h"

UImanager::UImanager(Vector2f windowSize) : m_HeartTexture(new Texture("../Resources/Hud/Heart.png")),
m_lives(3),
m_BossHealth(50),
m_windowSize(Vector2f{windowSize.x,windowSize.y})
{
}

UImanager::~UImanager()
{
	delete m_HeartTexture;
}

void UImanager::DrawHeart() const
{
	Rectf dstRect{};
	Rectf srcRect{};
	dstRect.left = 150.f;
	dstRect.bottom = 650.f;
	dstRect.width = 70.f;
	dstRect.height = 70.f;

	srcRect.width = 200.f;
	srcRect.height = 200.f;

	switch (m_lives)
	{
	case 3:
		srcRect.left = srcRect.width * 0;
		break;
	case 2:
		srcRect.left = srcRect.width * 1;
		break;
	case 1:
		srcRect.left = srcRect.width * 2;
		break;
	case 0:
		srcRect.left = srcRect.width * 3;
		break;
	}
	srcRect.bottom = 0;

	m_HeartTexture->Draw(dstRect, srcRect);
}

void UImanager::UpdateHeart(int lives)
{
	m_lives = lives;
}

////void UImanager::DrawHealthBarBoss() const
////{
////	utils::SetColor(Color4f{ 0.5f, 0.5f, 0.5f, 1.f });
////	utils::DrawRect(m_windowSize.x / 3, m_windowSize.y - 100, m_BossHealth * 10, 40, 7);
////	utils::SetColor(Color4f{ 1.0f, 0.f, 0.f, 1.f });
////	utils::FillRect(m_windowSize.x/3, m_windowSize.y-100, m_BossHealth * 10, 40);
////}
////
////void UImanager::UpdateHealthBarBoss(int health)
////{
////	m_BossHealth = health;
////}
