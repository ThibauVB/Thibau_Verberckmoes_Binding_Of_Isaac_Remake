#include "pch.h"
#include "BasicAI.h"
BasicAI::BasicAI(Point2f SpawnPos, Vector2f Velocity, int Health, int maxHealth) :
m_CenterPos(SpawnPos),
m_Velocity(Velocity),
m_Health(Health),
m_MaxHealth(maxHealth)
{
}

BasicAI::~BasicAI()
{
}

void BasicAI::Draw() const
{
	
}


