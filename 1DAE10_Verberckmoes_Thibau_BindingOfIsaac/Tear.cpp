#include "pch.h"
#include "Tear.h"
#include <cmath>
Tear::Tear(Texture* texture, Vector2f velocity, Point2f StartingPos) : m_TearTexture(texture),
m_Velocity(velocity),
m_Pos(StartingPos),
m_tearAlivePos(StartingPos),
m_LifeTime(0)
{
}

Tear::~Tear()
{
}

void Tear::DrawTear() const
{
	m_TearTexture->Draw(m_Pos);
	DrawHitBox();
}

void Tear::UpdateTear(float elapsedSec,Window const&window)
{
	float fraction = 1.f;
	m_LifeTime += elapsedSec;
	{
		m_Pos.y += elapsedSec * m_Velocity.y;
		m_Pos.x += elapsedSec * m_Velocity.x;
	}
	CheckIfWall(window);
	CheckLifeTime();
}

bool Tear::getAliveState()const
{
	return m_KeepAlive;
}


Point2f Tear::GetPostion()const
{
	return m_Pos;
}

void Tear::SetAliveState(bool state)
{
	m_KeepAlive = state;
}

void Tear::CheckLifeTime()
{
	if (m_LifeTime>m_MaxLifeTime.x)
	{
		std::cout << "Destroy Tear" << std::endl;
		m_KeepAlive = false;
	}
}

void Tear::CheckIfWall(const Window& window)
{
	Vector2f offset; Vector2f ExtraOffset;
	offset.x = 150.f;
	offset.y = 125.f;
	ExtraOffset.y = 85.f;
	ExtraOffset.x = 35;
	Rectf PlayArea{};
	PlayArea.left = offset.x - ExtraOffset.x;
	PlayArea.bottom = offset.y;
	PlayArea.height = window.height - offset.y - ExtraOffset.y;
	PlayArea.width = window.width - offset.x - ExtraOffset.y;

	if (m_Pos.x<PlayArea.left)
	{
		m_KeepAlive = false;
	}
	if (m_Pos.y<PlayArea.bottom)
	{
		m_KeepAlive = false;
	}
	if (m_Pos.x>PlayArea.left+PlayArea.width-ExtraOffset.x)
	{
		m_KeepAlive = false;
	}
	if (m_Pos.y>PlayArea.bottom+PlayArea.height-ExtraOffset.y/2)
	{
		m_KeepAlive = false;
	}
}

void Tear::DrawHitBox()const
{
	utils::SetColor(Color4f{ 1.f,1.f,0.f,1.f });
	utils::DrawRect(m_Pos.x, m_Pos.y, m_TearTexture->GetWidth(), m_TearTexture->GetHeight(), 2);
	utils::SetColor(Color4f{ 0.f,1.f,0.f,1.f });
}
