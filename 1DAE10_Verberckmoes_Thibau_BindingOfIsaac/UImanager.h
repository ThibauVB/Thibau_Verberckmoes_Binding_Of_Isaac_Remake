#pragma once
#include "pch.h"
#include "Texture.h"
class UImanager
{
public:
	UImanager();
	~UImanager();
	void DrawHeart()const;
	void UpdateHeart(int lives);
private:
	Texture* m_HeartTexture;
	int m_lives;
};
