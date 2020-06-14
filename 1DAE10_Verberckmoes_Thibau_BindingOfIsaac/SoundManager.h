#pragma once
#include "SoundEffect.h"

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void PlayStartingSound()const;
	void PlayshootingSound()const;
	void PlaytearDestroySound()const;
	void StartLoopedFlySound()const;
	void StopLoopedFlySound();
	void PlayGruntSound()const;
	void IncrementSound();
	void DecrementSound();
	void MuteSound();
	void UnmuteSound();
	std::string GetSoundLevel();
private:
	int m_SoundValueBeforeMute;
	SoundEffect* m_StartingSound;
	SoundEffect* m_ShootingSound;
	SoundEffect* m_TearDestroySound;
	SoundEffect* m_FlySound;
	SoundEffect* m_GruntSound;
};
