#pragma once
#include "Texture.h"
class Tear
{
public:
	Tear(Texture* texture, float velocity, Point2f StartingPos);
	void DrawTear()const;
	void UpdateTear(float elapsedSec);
private:
	float m_Velocity;
	Point2f m_Pos;
	Texture* m_TearTexture;
};
