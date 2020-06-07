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
private:
	SoundEffect* m_StartingSound;
	SoundEffect* m_ShootingSound;
	SoundEffect* m_TearDestroySound;
	SoundEffect* m_FlySound;
};
