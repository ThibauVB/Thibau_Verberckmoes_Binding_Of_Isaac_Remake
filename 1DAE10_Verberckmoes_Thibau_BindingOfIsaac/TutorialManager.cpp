#include "pch.h"
#include "TutorialManager.h"

TutorialManager::TutorialManager() :
	m_TutorialRoomTexture("../Resources/Backgrounds/TutorialRoom.png"),
	m_srcRect(0, 0, 1512.f, 800.f),
	m_dstRect(0, 0, 1512.f, 905)
{
}

TutorialManager::~TutorialManager()
{
}

void TutorialManager::DrawRoom() const
{
	m_TutorialRoomTexture.Draw(m_dstRect, m_dstRect);
	m_AiManager.DrawEnemy();
}

void TutorialManager::UpdateTutorialRoom(float elapsedSec,const Point2f& playerPos, const Rectf& Roomborders)
{
	m_AiManager.UpdateEnemies(elapsedSec,playerPos);
}

void TutorialManager::SpawnEnemy()
{
	Point2f RandomPos;
	RandomPos.x = rand() % static_cast<int>(1512.f) + (150.f);
	RandomPos.y = rand() % static_cast<int>(905.f) + (165.f);
	
	int randomAI;
	randomAI = rand() % 2 + 1;
	m_AiManager.CreateEnemy(RandomPos, Rectf{}, randomAI);
}
