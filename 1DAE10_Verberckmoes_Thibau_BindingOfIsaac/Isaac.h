﻿#pragma once
#include "Texture.h"
#include "utils.h"
class Isaac
{
public:
	enum WalkingDirection
	{
		movingUp,
		movingDown,
		movingRight,
		movingLeft,
		notMoving,
		MovingRightUP,
		MovingLeftUp,
		MovingRightDown,
		MovingLeftDown
	};
	explicit Isaac(Point2f StartingPoint, Point2f windowSize);
	void DrawIsaac()const;
	void UpdateIsaac(float elapsedSec);
	void SetDirection(WalkingDirection direction);
	Rectf GetShape()const;
	bool GetMotionState();
	
private:
	Rectf m_SrcRect;
    Rectf m_dstRect;
	Point2f m_WindowSize;
	void initRoomSize();
	Rectf m_StartingWindowGrid;
	enum ShootingDirection
	{
		shootingUp,
		shootingDown,
		shootingLeft,
		shootingRight,
		notShooting
	};
	Point2f m_CenterPos;
	Point2f m_CenterPosForHead;
	WalkingDirection m_IsaacDirection;
	const float m_MoventSpeed{230.f};
	const float m_SideMoventDecrement{27.f};
	const float m_Width{ 20.f };
	const float m_Height{ 20.f };
	Texture m_IsaacTexture{"../Resources/Isaac/Isaac.png"};
	void CheckPosition();
};