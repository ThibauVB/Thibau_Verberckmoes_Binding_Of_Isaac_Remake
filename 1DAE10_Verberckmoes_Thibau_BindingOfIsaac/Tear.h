#pragma once
#include "Texture.h"
#include "SoundManager.h"
class Tear
{
public:
	explicit Tear(Texture* texture, Vector2f velocity, Point2f StartingPos);
	~Tear();
	void DrawTear()const;
	void UpdateTear(float elapsedSec, const Window& window,bool TutorialRoom);
	bool getAliveState()const;
	Point2f GetPostion()const;
	void SetAliveState(bool state);
private:
	SoundManager m_SoundManager;
	Vector2f m_Velocity;
	Point2f m_Pos;
	Texture* m_TearTexture;
	Point2f m_tearAlivePos;
	const Vector2f m_MaxLifeTime{ 1.6f,1.6f };
	bool m_KeepAlive{ true };
	float m_LifeTime;
	void CheckLifeTime();
	void CheckIfWall(const Window& window,bool TutorialRoom);
	void DrawHitBox()const;
	//test vars
	bool test;
};
