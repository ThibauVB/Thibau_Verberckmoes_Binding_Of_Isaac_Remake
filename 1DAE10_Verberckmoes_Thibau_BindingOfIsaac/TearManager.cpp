#include "pch.h"
#include "TearManager.h"
TearManager::TearManager()
{
	
}

void TearManager::CreateTear()
{
	//m_ActiveTears.push_back(Tear{&m_TearTexture,50.f,});
}

void TearManager::DrawTears() const
{
	for (Tear amount : m_ActiveTears)
	{
		amount.DrawTear();
	}
}

void TearManager::UpdateTears(float elapsedSec)
{
	for (Tear amount : m_ActiveTears)
	{
		amount.UpdateTear(elapsedSec);
	}
}

void TearManager::SetPlayerPostion(Point2f PlayerPos)
{
	m_Pos = PlayerPos;
}
