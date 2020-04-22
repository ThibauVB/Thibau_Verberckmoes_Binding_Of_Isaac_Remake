﻿#include "pch.h"
#include "Tear.h"
#include <cmath>
Tear::Tear(Texture* texture, Vector2f velocity, Point2f StartingPos) : m_TearTexture(texture),
m_Velocity(velocity),
m_Pos(StartingPos),
m_tearAlivePos(StartingPos),
m_LifeTime(0)
{
}

Tear::~Tear()
{
}

void Tear::DrawTear() const
{
	m_TearTexture->Draw(m_Pos);
}

void Tear::UpdateTear(float elapsedSec,Window const&window)
{
	float fraction = 1.f;
	m_LifeTime += elapsedSec;
	//if (m_MaxLifeTime.x/2<m_LifeTime)
	//{
	//	m_Velocity.y = 100;
	//	m_Pos.x += (elapsedSec * m_Velocity.x)*fraction/(m_LifeTime*3);
	//	m_Pos.y -= elapsedSec * m_Velocity.y;
	//}else
	{
		/*m_Velocity.y = 0;*/
		m_Pos.y += elapsedSec * m_Velocity.y;
		m_Pos.x += elapsedSec * m_Velocity.x;
	}
	
	std::cout << m_Pos.x << " : " << m_Pos.y << std::endl;
	CheckIfWall(window);
	CheckLifeTime();
}

bool Tear::getAliveState()
{
	return m_KeepAlive;
}

void Tear::CheckLifeTime()
{
	if (m_LifeTime>m_MaxLifeTime.x)
	{
		std::cout << "Destroy Tear" << std::endl;
		m_KeepAlive = false;
	}
}

void Tear::CheckIfWall(const Window& window)
{
	Vector2f offset; Vector2f ExtraOffset;
	offset.x = 150.f;
	offset.y = 125.f;
	ExtraOffset.y = 85.f;
	ExtraOffset.x = 35;
	Rectf PlayArea{};
	PlayArea.left = offset.x - ExtraOffset.x;
	PlayArea.bottom = offset.y;
	PlayArea.height = window.height - offset.y - ExtraOffset.y;
	PlayArea.width = window.width - offset.x - ExtraOffset.y;


	if (m_Pos.x<PlayArea.left)
	{
		m_KeepAlive = false;
	}
	if (m_Pos.y<PlayArea.bottom)
	{
		m_KeepAlive = false;
	}
	if (m_Pos.x>PlayArea.left+PlayArea.width-ExtraOffset.x)
	{
		m_KeepAlive = false;
	}
	if (m_Pos.y>PlayArea.bottom+PlayArea.height-ExtraOffset.y/2)
	{
		m_KeepAlive = false;
	}
	
}
