#pragma once
#include "SoundStream.h"
class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void PlayStartingSound()const;
	void PlayshootingSound()const;
	void PlaytearDestroySound()const;
private:
	SoundStream* m_StartingSound;
	SoundStream* m_ShootingSound;
	SoundStream* m_TearDestroySound;
	SoundStream* m_FlySound;
};
