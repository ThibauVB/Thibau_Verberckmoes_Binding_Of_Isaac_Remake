#pragma once
#include "pch.h"
#include "Texture.h"

class TutorialManager
{
public:
	TutorialManager();
	~TutorialManager();

	void DrawRoom()const;
	void UpdateTutorialRoom(float elapsedSec);
private:
	Texture m_TutorialRoomTexture;
	Rectf m_dstRect;
	Rectf m_srcRect;
};
