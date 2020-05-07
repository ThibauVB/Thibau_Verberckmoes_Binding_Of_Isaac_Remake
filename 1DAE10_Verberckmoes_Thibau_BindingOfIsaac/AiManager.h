#pragma once
#include "Texture.h"
#include "BasicAI.h"
#include "TearManager.h"
class AiManager
{
public:
	explicit AiManager();
	~AiManager();
	void CreateEnemy(Point2f pos,const Rectf& RoomBorders);
	void DrawEnemy()const;
	void UpdateEnemies(float elapsedSec,const Point2f& pos);
	void DeleteEnemy(int Enemy);
	void TransferTearPositions(Point2f pos, std::vector<Tear*>& activetears);
private:
	std::vector<BasicAI*> m_ActiveEnemies;
	void CheckHealthStatus();
	//EnemyTextures
	Texture m_AttackFlyTexture {"../Resources/Enemies/AttackFly.png"};
};
