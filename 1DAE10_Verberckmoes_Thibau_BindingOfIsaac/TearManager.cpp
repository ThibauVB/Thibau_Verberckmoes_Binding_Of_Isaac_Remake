#include "pch.h"
#include "TearManager.h"
TearManager::TearManager(Window window) : m_Window(window)
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

void TearManager::CreateTear(Point2f pos, utils::ShootingDirection shootingDirection, const SoundManager* soundmanager)
{
	Vector2f Velocity;
	switch (shootingDirection)
	{
	case utils::ShootingUp:
		Velocity.y = 450.f;
		Velocity.x = 0.f;
		m_ActiveTears.push_back(new Tear{ &m_TearTexture,Velocity,pos });
		soundmanager->PlayshootingSound();
		break;
	case utils::ShootingRight:
		Velocity.y = 0.f;
		Velocity.x = 450.f;
		m_ActiveTears.push_back(new Tear{ &m_TearTexture,Velocity,pos });
		soundmanager->PlayshootingSound();
		break;
	case utils::ShootingDown:
		Velocity.y = -450.f;
		Velocity.x = 0.f;
		m_ActiveTears.push_back(new Tear{ &m_TearTexture,Velocity,pos });
		soundmanager->PlayshootingSound();
		break;
	case utils::ShootingLeft:
		Velocity.y = 0.f;
		Velocity.x = -450.f;
		m_ActiveTears.push_back(new Tear{ &m_TearTexture,Velocity,pos });
		soundmanager->PlayshootingSound();
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

void TearManager::UpdateTears(float elapsedSec, const SoundManager* soundManager)
{
	for (int i{ 0 }; i < m_ActiveTears.size(); ++i)
	{
		m_ActiveTears[i]->UpdateTear(elapsedSec, m_Window);
		if (m_ActiveTears[i]->getAliveState() == false)
		{
			DeleteTear(i);
			soundManager->PlaytearDestroySound();
		}
	}
}

void TearManager::SetPlayerPostion(Point2f PlayerPos)
{
	m_Pos = PlayerPos;
}

Point2f TearManager::GetTearPosition(int tear) const
{
	return m_ActiveTears[tear]->GetPostion();
}

void TearManager::DeleteTear(size_t tear)
{
	delete m_ActiveTears[tear];
	m_ActiveTears[tear] = m_ActiveTears.back();
	m_ActiveTears.pop_back();
	std::cout << "Deleted a Tear" << std::endl;
}

int TearManager::GetAmountOfActiveTears() const
{
	return m_ActiveTears.size();
}

std::vector<Tear*>& TearManager::GetActiveTearsVector()
{
	return m_ActiveTears;
}