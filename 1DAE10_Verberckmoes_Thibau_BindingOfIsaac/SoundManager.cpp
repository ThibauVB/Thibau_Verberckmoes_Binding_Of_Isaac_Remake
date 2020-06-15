#include "pch.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
	m_StartingSound = new SoundEffect("../Resources/Sounds/StartSound.mp3");
	m_ShootingSound = new SoundEffect("../Resources/Sounds/TearShooting.mp3");
	m_TearDestroySound = new SoundEffect("../Resources/Sounds/TearDestroy.mp3");
	m_FlySound = new SoundEffect("../Resources/Sounds/AttackFly.mp3");
	m_GruntSound = new SoundEffect("../Resources/Sounds/Grunt.mp3");
	m_WinSound = new SoundEffect("../Resources/Sounds/isaacbosswin.mp3");
	m_DieSound = new SoundEffect("../Resources/Sounds/isaacdies.mp3");
}

SoundManager::~SoundManager()
{
	delete m_TearDestroySound;
	delete m_ShootingSound;
	delete m_StartingSound;
	delete m_FlySound;
	delete m_GruntSound;
	delete m_DieSound;
	delete m_WinSound;
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

void SoundManager::StopLoopedFlySound()
{
	m_FlySound->StopAll();
}

void SoundManager::PlayGruntSound() const
{
	m_GruntSound->SetVolume(50);
	m_GruntSound->Play(false);
}

void SoundManager::IncrementSound()
{
	int sound;
	sound = m_FlySound->GetVolume();
	sound += 1;
	m_FlySound->SetVolume(sound);
	sound = m_ShootingSound->GetVolume();
	sound += 1;
	m_ShootingSound->SetVolume(sound);
	sound = m_TearDestroySound->GetVolume();
	sound += 1;
	m_TearDestroySound->SetVolume(sound);
	sound = m_StartingSound->GetVolume();
	sound += 1;
	m_StartingSound->SetVolume(sound);
	sound = m_GruntSound->GetVolume();
	sound += 1;
	m_GruntSound->SetVolume(sound);
}

void SoundManager::DecrementSound()
{
	int sound;
	sound = m_FlySound->GetVolume();
	sound -= 1;
	m_FlySound->SetVolume(sound);
	sound = m_ShootingSound->GetVolume();
	sound -= 1;
	m_ShootingSound->SetVolume(sound);
	sound = m_TearDestroySound->GetVolume();
	sound -= 1;
	m_TearDestroySound->SetVolume(sound);
	sound = m_StartingSound->GetVolume();
	sound -= 1;
	m_StartingSound->SetVolume(sound);
	sound = m_GruntSound->GetVolume();
	sound -= 1;
	m_GruntSound->SetVolume(sound);
}

void SoundManager::MuteSound()
{
	m_SoundValueBeforeMute = m_FlySound->GetVolume();
	m_ShootingSound->SetVolume(0);
	m_StartingSound->SetVolume(0);
	m_TearDestroySound->SetVolume(0);
	m_FlySound->SetVolume(0);
	m_GruntSound->SetVolume(0);
}

void SoundManager::UnmuteSound()
{
	m_ShootingSound->SetVolume(m_SoundValueBeforeMute);
	m_StartingSound->SetVolume(m_SoundValueBeforeMute);
	m_TearDestroySound->SetVolume(m_SoundValueBeforeMute);
	m_FlySound->SetVolume(m_SoundValueBeforeMute);
	m_GruntSound->SetVolume(m_SoundValueBeforeMute);
}

std::string SoundManager::GetSoundLevel()
{
	std::string soundlevel;

	soundlevel = std::to_string(m_FlySound->GetVolume());
	return soundlevel;
}

void SoundManager::PlayWinSound() const
{
	m_WinSound->Play(false);
}

void SoundManager::PlayDieSoud() const
{
	m_DieSound->Play(false);
}

