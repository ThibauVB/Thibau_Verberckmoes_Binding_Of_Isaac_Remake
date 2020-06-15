#pragma once
#include "pch.h"
#include "Texture.h"
class UImanager
{
public:
	UImanager(Vector2f windowSize);
	~UImanager();
	void DrawHeart()const;
	void UpdateHeart(int lives);
	//void DrawHealthBarBoss()const;
	//void UpdateHealthBarBoss(int health);
private:
	Texture* m_HeartTexture;
	int m_lives;
	int m_BossHealth;
	Vector2f m_windowSize;
};
