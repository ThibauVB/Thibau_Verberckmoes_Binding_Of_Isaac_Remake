#include "pch.h"
#include "Tear.h"

Tear::Tear(Texture* texture, float velocity, Point2f StartingPos) :  m_TearTexture(texture),
	m_Velocity(velocity),
	m_Pos(StartingPos)
{
	
}

void Tear::DrawTear() const
{
	std::cout << m_Pos.x <<":"<< m_Pos.y << std::endl;
	m_TearTexture->Draw(m_Pos);
}

void Tear::UpdateTear(float elapsedSec)
{
	m_Pos.x += elapsedSec * m_Velocity;
}


