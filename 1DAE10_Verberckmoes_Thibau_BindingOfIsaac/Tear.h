#pragma once
#include "Texture.h"
class Tear
{
public:
	Tear(Texture* texture, Vector2f velocity, Point2f StartingPos);
	~Tear();
	void DrawTear()const;
	void UpdateTear(float elapsedSec);
	bool getAliveState();
private:
	Vector2f m_Velocity;
	Point2f m_Pos;
	Texture* m_TearTexture;
	Point2f m_tearAlive{};
	const Vector2f m_MaxLifeTime{ 1000.f,1000.f };
	bool m_KeepAlive{ true };
	void CheckLifeTime();
};
