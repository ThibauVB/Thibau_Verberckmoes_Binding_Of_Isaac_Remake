#pragma once
#include "Texture.h"
#include "BasicAI.h"
class AiManager
{
public:
	explicit AiManager();
	~AiManager();
	void CreateEnemy(Point2f pos);
	void DrawEnemy()const;
	void UpdateEnemies(float elapsedSec);
	void DeleteEnemy(int Enemy);
private:
	std::vector<BasicAI*> m_ActiveEnemies;
	//EnemyTextures
	Texture m_AttackFlyTexture {"../Resources/Enemies/AttackFly.png"};
};
