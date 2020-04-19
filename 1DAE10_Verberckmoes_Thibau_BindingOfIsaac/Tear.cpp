#include "pch.h"
#include "Tear.h"

Tear::Tear(Texture* texture, Vector2f velocity, Point2f StartingPos) : m_TearTexture(texture),
m_Velocity(velocity),
m_Pos(StartingPos),
m_tearAlive(StartingPos)
{
}

Tear::~Tear()
{
}

void Tear::DrawTear() const
{
	m_TearTexture->Draw(m_Pos);
}

void Tear::UpdateTear(float elapsedSec)
{
	m_Pos.x += elapsedSec * m_Velocity.x;
	m_Pos.y += elapsedSec * m_Velocity.y;
	CheckLifeTime();
}

bool Tear::getAliveState()
{
	return m_KeepAlive;
}

void Tear::CheckLifeTime()
{
	if (m_Pos.x - m_MaxLifeTime.x > m_tearAlive.x)
	{
		std::cout << "Destroy Tear" << std::endl;
		m_KeepAlive = false;
	}
}