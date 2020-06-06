#include "pch.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
	m_StartingSound = new SoundStream("../Resources/Sounds/StartSound.mp3");
	m_ShootingSound = new SoundStream("../Resources/Sounds/TearShooting.mp3");
	m_TearDestroySound = new SoundStream("../Resources/Sounds/TearDestroy.mp3");
}

SoundManager::~SoundManager()
{
	delete m_TearDestroySound;
	delete m_ShootingSound;
	delete m_StartingSound;
}

void SoundManager::PlayStartingSound()const
{
	m_StartingSound->Play(false);
}

void SoundManager::PlayshootingSound()const
{
	m_ShootingSound->Play(false);
}

void SoundManager::PlaytearDestroySound()const
{
	m_TearDestroySound->Play(false);
}

