﻿#include "pch.h"
#include "BasicAI.h"
BasicAI::BasicAI(Point2f SpawnPos, Vector2f Velocity, int Health, int maxHealth,int fps, int nrOfFrames) :
m_CenterPos(SpawnPos),
m_Velocity(Velocity),
m_Health(Health),
m_MaxHealth(maxHealth),
m_TimePassedForAnimation(0),
m_FramesPerSec(fps),
m_NrOfFramesForBody(nrOfFrames),
m_AnimFrame(0)
{
}

BasicAI::~BasicAI()
{
}

void BasicAI::Draw() const
{
	
}

void BasicAI::Update(float elapsedSec)
{
	
}


