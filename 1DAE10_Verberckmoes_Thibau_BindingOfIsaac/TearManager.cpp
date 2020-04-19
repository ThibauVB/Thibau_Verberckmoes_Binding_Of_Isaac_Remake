#include "pch.h"
#include "TearManager.h"
TearManager::TearManager()
{
}

TearManager::~TearManager()
{
	for (int i{ 0 }; i < m_ActiveTears.size(); ++i)
	{
		delete m_ActiveTears[i];
		m_ActiveTears[i] = nullptr;
	}
}

void TearManager::CreateTear(Point2f pos, utils::ShootingDirection shootingDirection)
{
	Vector2f Velocity;
	switch (shootingDirection)
	{
	case utils::ShootingUp:
		Velocity.y = 450.f;
		Velocity.x = 0.f;
		m_ActiveTears.push_back(new Tear{ &m_TearTexture,Velocity,pos });
		break;
	case utils::ShootingRight:
		Velocity.y = 0.f;
		Velocity.x = 450.f;
		m_ActiveTears.push_back(new Tear{ &m_TearTexture,Velocity,pos });
		break;
	case utils::ShootingDown:
		Velocity.y = -450.f;
		Velocity.x = 0.f;
		m_ActiveTears.push_back(new Tear{ &m_TearTexture,Velocity,pos });
		break;
	case utils::ShootingLeft:
		Velocity.y = 0.f;
		Velocity.x = -450.f;
		m_ActiveTears.push_back(new Tear{ &m_TearTexture,Velocity,pos});
		break;
	}
}

void TearManager::DrawTears() const
{
	for (int i{ 0 }; i < m_ActiveTears.size(); ++i)
	{
		m_ActiveTears[i]->DrawTear();
	}
}

void TearManager::UpdateTears(float elapsedSec)
{
	//for (Tear amount : m_ActiveTears)
	//{
	//	amount.UpdateTear(elapsedSec);
	//}
	//

	for (int i{ 0 }; i < m_ActiveTears.size(); ++i)
	{
		m_ActiveTears[i]->UpdateTear(elapsedSec);
		if (m_ActiveTears[i]->getAliveState() == false)
		{
			DeleteTear(i);
		}
	}
}

void TearManager::SetPlayerPostion(Point2f PlayerPos)
{
	m_Pos = PlayerPos;
}

void TearManager::DeleteTear(size_t tear)
{
	delete m_ActiveTears[tear];
	m_ActiveTears[tear] = m_ActiveTears.back();
	m_ActiveTears.pop_back();
	std::cout << "Deleted a Tear" << std::endl;
}