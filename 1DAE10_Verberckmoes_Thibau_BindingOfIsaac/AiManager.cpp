#include "pch.h"
#include "AiManager.h"
#include "AttackFly.h"
#include "Spider.h"
AiManager::AiManager() : m_AttackFlyTexture("../Resources/Enemies/AttackFly.png"),
m_SpiderTexture("../Resources/Enemies/Spider.png")
{
}

AiManager::~AiManager()
{
	for (int i{ 0 }; i < m_ActiveEnemies.size(); ++i)
	{
		delete m_ActiveEnemies[i];
		m_ActiveEnemies[i] = nullptr;
	}
}

void AiManager::CreateEnemy(Point2f SpawnPos, const Rectf& RoomBorders, int enemy)
{
	switch (2)
	{
	case 1:
		m_ActiveEnemies.push_back(new AttackFly{ &m_AttackFlyTexture,SpawnPos,Vector2f{100,50},5,5 });
		break;
	case 2:
		//m_ActiveEnemies.push_back(new AttackFly{ &m_AttackFlyTexture,SpawnPos,Vector2f{100,50},5,5 });
		m_ActiveEnemies.push_back(new Spider{ &m_SpiderTexture,SpawnPos,Vector2f{100,50},5,5 });
		break;
	}
}

void AiManager::DrawEnemy() const
{
	for (int i{ 0 }; i < m_ActiveEnemies.size(); ++i)
	{
		m_ActiveEnemies[i]->Draw();
	}
}

void AiManager::UpdateEnemies(float elapsedSec, const Point2f& pos)
{
	for (int i{ 0 }; i < m_ActiveEnemies.size(); ++i)
	{
		m_ActiveEnemies[i]->Update(elapsedSec, pos);
	}
	CheckHealthStatus();
	SetAmountOfEnemies(m_ActiveEnemies.size());

	//CheckOverlappingAI();
}

void AiManager::DeleteEnemy(int Enemy)
{
	delete m_ActiveEnemies[Enemy];
	m_ActiveEnemies[Enemy] = m_ActiveEnemies.back();
	m_ActiveEnemies.pop_back();
	std::cout << "Deleted Enemy" << std::endl;
}

void AiManager::TransferTearPositions(Point2f pos, std::vector<Tear*>& activetears, const SoundManager& soundManager)
{
	for (int i{ 0 }; i < m_ActiveEnemies.size(); ++i)
	{
		m_ActiveEnemies[i]->CheckIfHit(pos, activetears, soundManager);
	}
}

void AiManager::SetAmountOfEnemies(int flies)
{
	m_AmountOfCurrentFlies = flies;
}

int AiManager::GetAmountOfActiveEnemies()
{
	return m_ActiveEnemies.size();
}

Rectf AiManager::GetHitBoxAI(int Ai) const
{
	return m_ActiveEnemies[Ai]->GetHitbox();
}

Point2f AiManager::GetCenterPositionAI(int Ai) const
{
	return m_ActiveEnemies[Ai]->GetCenterPos();
}

void AiManager::CheckHealthStatus()
{
	for (int i{ 0 }; i < m_ActiveEnemies.size(); ++i)
	{
		if (m_ActiveEnemies[i]->GetHealth() <= 0)
		{
			std::cout << "Destroy Enemy" << std::endl;
			DeleteEnemy(i);
		}
	}
}

void AiManager::CheckOverlappingAI()
{
	Vector2f vectorA, vectorB, delta;
	Point2f pos1, pos2;
	for (size_t idX{ 0 }; idX < m_ActiveEnemies.size(); ++idX)
	{
		vectorA.x = m_ActiveEnemies[idX]->GetCenterPos().x;
		vectorA.y = m_ActiveEnemies[idX]->GetCenterPos().y;

		for (size_t idY{ 0 }; idY < m_ActiveEnemies.size(); ++idY)
		{
			vectorB.x = m_ActiveEnemies[idY]->GetCenterPos().x;
			vectorB.y = m_ActiveEnemies[idY]->GetCenterPos().y;
			if (vectorA.x != vectorB.x && vectorA.y != vectorB.y)
			{
				delta = vectorB - vectorA;
				if (abs(delta.x) < 10 || abs(delta.y) < 10)
				{
					//change pos of ai
					m_ActiveEnemies[idY]->SetUpdatePositionBool(false);
				}
				else
				{
					m_ActiveEnemies[idY]->SetUpdatePositionBool(true);
				}
			}
		}
	}
}