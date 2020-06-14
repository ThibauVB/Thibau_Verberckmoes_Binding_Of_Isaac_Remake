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
}

void TutorialManager::UpdateTutorialRoom(float elapsedSec)
{
}