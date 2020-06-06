#include "pch.h"
#include "AiManager.h"
#include "AttackFly.h"
AiManager::AiManager()
{
}

AiManager::~AiManager()
{
	for (int i{0};i<m_ActiveEnemies.size();++i)
	{
		delete m_ActiveEnemies[i];
		m_ActiveEnemies[i] = nullptr;
	}
}

void AiManager::CreateEnemy(Point2f SpawnPos,const Rectf& RoomBorders)
{
	m_ActiveEnemies.push_back(new AttackFly{&m_AttackFlyTexture,SpawnPos,Vector2f{100,50},5,5});
}

void AiManager::DrawEnemy() const
{
	for (int i{0};i<m_ActiveEnemies.size();++i)
	{
		m_ActiveEnemies[i]->Draw();
	}
}

void AiManager::UpdateEnemies(float elapsedSec, const Point2f& pos)
{
	for (int i{0};i<m_ActiveEnemies.size();++i)
	{
		m_ActiveEnemies[i]->Update(elapsedSec,pos);
	}
	CheckHealthStatus();
}

void AiManager::DeleteEnemy(int Enemy)
{
	delete m_ActiveEnemies[Enemy];
	m_ActiveEnemies[Enemy] = m_ActiveEnemies.back();
	m_ActiveEnemies.pop_back();
	std::cout << "Deleted Enemy" << std::endl;
}

void AiManager::TransferTearPositions(Point2f pos, std::vector<Tear*>& activetears,const SoundManager& soundManager)
{
	for (int i{0};i<m_ActiveEnemies.size();++i)
	{
		m_ActiveEnemies[i]->CheckIfHit(pos,activetears,soundManager);
	}
}

void AiManager::SetAmountOfEnemies(int flies)
{
	m_AmountOfCurrentFlies = flies;
}

void AiManager::CheckHealthStatus()
{
	for (int i{0};i<m_ActiveEnemies.size();++i)
	{
		if (m_ActiveEnemies[i]->GetHealth() <= 0)
		{
			std::cout << "Destroy Enemy" << std::endl;
			DeleteEnemy(i);
		}
	}
}

