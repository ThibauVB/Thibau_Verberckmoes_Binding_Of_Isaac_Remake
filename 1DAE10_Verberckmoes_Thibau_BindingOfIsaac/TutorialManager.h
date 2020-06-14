#pragma once
#include "pch.h"
#include "Texture.h"
#include "AiManager.h"
class TutorialManager
{
public:
	TutorialManager();
	~TutorialManager();

	void DrawRoom()const;
	void UpdateTutorialRoom(float elapsedSec,const Point2f& playerPos,const Rectf& Roomborders);
	void SpawnEnemy();
private:
	AiManager m_AiManager;
	Texture m_TutorialRoomTexture;
	Rectf m_dstRect;
	Rectf m_srcRect;

};
