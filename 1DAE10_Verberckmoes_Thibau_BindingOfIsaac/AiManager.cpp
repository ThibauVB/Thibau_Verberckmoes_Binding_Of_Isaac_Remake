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

void AiManager::CreateEnemy(Point2f SpawnPos)
{
	m_ActiveEnemies.push_back(new AttackFly{&m_AttackFlyTexture,SpawnPos,Vector2f{50,50},50,50});
}

void AiManager::DrawEnemy() const
{
	for (int i{0};i<m_ActiveEnemies.size();++i)
	{
		m_ActiveEnemies[i]->Draw();
	}
}

void AiManager::UpdateEnemies(float elapsedSec)
{
	
}

void AiManager::DeleteEnemy(int Enemy)
{
	delete m_ActiveEnemies[Enemy];
	m_ActiveEnemies[Enemy] = m_ActiveEnemies.back();
	m_ActiveEnemies.pop_back();
	std::cout << "Deleted Enemy" << std::endl;
}

