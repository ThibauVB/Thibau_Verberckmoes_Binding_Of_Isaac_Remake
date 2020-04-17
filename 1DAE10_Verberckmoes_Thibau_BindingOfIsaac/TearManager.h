#pragma once
#include "Texture.h"
#include "Tear.h"
class TearManager
{
public:
	//TearManager(const Texture& tearTexture);
	void CreateTear();
	
private:
	float m_Velocity;
	Texture& m_TearTexture;
	std::vector<Tear> m_ActiveTears;
};
