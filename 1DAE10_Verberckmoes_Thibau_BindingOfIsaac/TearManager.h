#pragma once
#include "Texture.h"
#include "Tear.h"
class TearManager
{
public:
	TearManager();
	~TearManager();
	void CreateTear(Point2f pos, utils::ShootingDirection);
	void DrawTears()const;
	void UpdateTears(float elapsedSec);
	void SetPlayerPostion(Point2f PlayerPos);
private:

	Point2f m_Pos;
	float m_Velocity;
	float m_TimeToShootNewTear;
	Texture m_TearTexture{ "../Resources/Isaac/Tear.png" };
	std::vector<Tear*> m_ActiveTears;
	void DeleteTear(size_t tear);
};
