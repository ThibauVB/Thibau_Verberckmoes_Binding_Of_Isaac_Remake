#include "pch.h"
#include "UImanager.h"

UImanager::UImanager() : m_HeartTexture(new Texture("../Resources/Hud/Heart.png")),
m_lives(3)
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