#pragma once
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
	Point2f GetPostion();
	void SetPlayerPos(Point2f pos);
private:
	Rectf m_srcRectBody;
	Rectf m_dstRectBody;
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
	float m_TimePassedForAnimation;
	float m_FramesPerSec;
	int m_AnimFrame;
	int m_NrOfFramesForBody;
	WalkingDirection m_IsaacDirection;
	const float m_MoventSpeed{ 310.f };
	const float m_SideMoventDecrement{ 27.f };
	const float m_Width{ 20.f };
	const float m_Height{ 20.f };
	Texture m_IsaacTexture{ "../Resources/Isaac/Isaac.png" };
	void CheckPosition();
	void TimeCounter(float elapsedTime);
};
