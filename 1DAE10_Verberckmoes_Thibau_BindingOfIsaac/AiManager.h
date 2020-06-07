#pragma once
#include "Texture.h"
#include "BasicAI.h"
#include "TearManager.h"
#include "SoundManager.h"
class AiManager
{
public:
	explicit AiManager();
	~AiManager();
	void CreateEnemy(Point2f pos,const Rectf& RoomBorders);
	void DrawEnemy()const;
	void UpdateEnemies(float elapsedSec,const Point2f& pos);
	void DeleteEnemy(int Enemy);
	void TransferTearPositions(Point2f pos, std::vector<Tear*>& activetears,const SoundManager& soundManager);
	void SetAmountOfEnemies(int fies);
	int GetAmountOfActiveEnemies();
	Rectf GetHitBoxAI(int Ai)const;
	Point2f GetCenterPositionAI(int Ai)const;
private:
	std::vector<BasicAI*> m_ActiveEnemies;
	void CheckHealthStatus();
	void CheckOverlappingAI();
	int m_AmountOfCurrentFlies;
	//EnemyTextures
	Texture m_AttackFlyTexture {"../Resources/Enemies/AttackFly.png"};
};
