#pragma once
#include "Texture.h"
#include "Tear.h"
#include "SoundManager.h"
class TearManager
{
public:
	explicit TearManager(Window window);
	~TearManager();
	void CreateTear(Point2f pos, utils::ShootingDirection, const SoundManager* soundManager);
	void DrawTears()const;
	void UpdateTears(float elapsedSec, const SoundManager* soundManager);
	void SetPlayerPostion(Point2f PlayerPos);
	Point2f GetTearPosition(int tear)const;
	int GetAmountOfActiveTears()const;
	std::vector<Tear*>& GetActiveTearsVector();
private:
	Window m_Window;
	Point2f m_Pos;
	float m_Velocity;
	float m_TimeToShootNewTear;
	Texture m_TearTexture{ "../Resources/Isaac/Tear.png" };
	std::vector<Tear*> m_ActiveTears;
	void DeleteTear(size_t tear);
};
