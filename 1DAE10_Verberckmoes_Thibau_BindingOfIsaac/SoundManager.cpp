﻿#include "pch.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
	m_StartingSound = new SoundEffect("../Resources/Sounds/StartSound.mp3");
	m_ShootingSound = new SoundEffect("../Resources/Sounds/TearShooting.mp3");
	m_TearDestroySound = new SoundEffect("../Resources/Sounds/TearDestroy.mp3");
	m_FlySound = new SoundEffect("../Resources/Sounds/AttackFly.mp3");
}

SoundManager::~SoundManager()
{
	delete m_TearDestroySound;
	delete m_ShootingSound;
	delete m_StartingSound;
	delete m_FlySound;
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

void SoundManager::StartLoopedFlySound() const
{
	m_FlySound->Play(true);
}

void SoundManager::StopLoopedFlySoudn()
{
	m_FlySound->StopAll();
}



