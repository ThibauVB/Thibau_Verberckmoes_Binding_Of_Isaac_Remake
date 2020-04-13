#include "pch.h"
#include "Isaac.h"

Isaac::Isaac(Point2f StartingPoint, Point2f windowSize) : m_CenterPos(StartingPoint),
m_WindowSize(windowSize)
{
	initRoomSize();
}

void Isaac::DrawIsaac()const
{	
	m_IsaacTexture.Draw(m_dstRect, m_SrcRect);
	utils::DrawPoint(m_CenterPos, 10);
}

void Isaac::UpdateIsaac(float elapsedSec)
{

	float OffsetX{ 35.f };
	float OffsetY{ 15.f };
	
	m_dstRect.width = 120.f;
	m_dstRect.height = 120.f;
	m_dstRect.left = m_CenterPos.x - m_SrcRect.width;
	m_dstRect.bottom = m_CenterPos.y - m_SrcRect.height;
	switch (m_IsaacDirection)
	{
	case MovingRightUP:
		m_CenterPos.x += elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_CenterPos.y += elapsedSec * (m_MoventSpeed- m_SideMoventDecrement);
		m_SrcRect.width = 40.f;
		m_SrcRect.height = 40.f;
		m_SrcRect.left = 200.f;
		m_SrcRect.bottom = 60.f;
		m_dstRect.left = m_CenterPos.x - m_SrcRect.width - OffsetX;
		break;
	case MovingRightDown:
		m_CenterPos.x += elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_CenterPos.y -= elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_SrcRect.width = 40.f;
		m_SrcRect.height = 40.f;
		m_SrcRect.left = 10.f;
		m_SrcRect.bottom = 60.f;
		break;
	case MovingLeftUp:
		m_CenterPos.x -= elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_CenterPos.y += elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_SrcRect.width = 40.f;
		m_SrcRect.height = 40.f;
		m_SrcRect.left = 200.f;
		m_SrcRect.bottom = 60.f;
		m_dstRect.left = m_CenterPos.x - m_SrcRect.width - OffsetX;
		break;
	case MovingLeftDown:
		m_CenterPos.x -= elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_CenterPos.y -= elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_SrcRect.width = 40.f;
		m_SrcRect.height = 40.f;
		m_SrcRect.left = 10.f;
		m_SrcRect.bottom = 60.f;
		break;
	case movingUp:
		m_CenterPos.y += elapsedSec * m_MoventSpeed;
		m_SrcRect.width = 40.f;
		m_SrcRect.height = 40.f;
		m_SrcRect.left = 200.f;
		m_SrcRect.bottom = 60.f;
		m_dstRect.left = m_CenterPos.x - m_SrcRect.width - OffsetX;
		m_dstRect.bottom = m_CenterPos.y - m_SrcRect.height - OffsetY;

		break;
	case movingDown:
		m_CenterPos.y -= elapsedSec * m_MoventSpeed;
		m_SrcRect.width = 40.f;
		m_SrcRect.height = 40.f;
		m_SrcRect.left = 10.f;
		m_SrcRect.bottom = 60.f;
		m_dstRect.left = m_CenterPos.x - m_SrcRect.width;
		m_dstRect.bottom = m_CenterPos.y - m_SrcRect.height - OffsetY;
		break;
	case movingLeft:
		m_CenterPos.x -= elapsedSec * m_MoventSpeed;
		m_SrcRect.width = 40.f;
		m_SrcRect.height = 40.f;
		m_SrcRect.left = 240.f;
		m_SrcRect.bottom = 60.f;
		m_dstRect.left = m_CenterPos.x - m_SrcRect.width - OffsetX;
		m_dstRect.bottom = m_CenterPos.y - m_SrcRect.height - OffsetY;

		break;
	case movingRight:
		m_CenterPos.x += elapsedSec * m_MoventSpeed;
		m_SrcRect.width = 40.f;
		m_SrcRect.height = 40.f;
		m_SrcRect.left = 80.f;
		m_SrcRect.bottom = 60.f;
		m_dstRect.left = m_CenterPos.x - m_SrcRect.width - OffsetX;
		m_dstRect.bottom = m_CenterPos.y - m_SrcRect.height-OffsetY;
		break;
	case notMoving:
		m_CenterPos.x += 0.f;
		m_CenterPos.y += 0.f;
		m_dstRect.left = m_CenterPos.x - m_SrcRect.width - OffsetX;
		m_dstRect.bottom = m_CenterPos.y - m_SrcRect.height - OffsetY;
		break;
	}
	CheckPosition();
}

void Isaac::SetDirection(WalkingDirection direction)
{
	m_IsaacDirection = direction;
}

Rectf Isaac::GetShape()const
{
	Rectf isaacShape;
	isaacShape.left = m_CenterPos.x - m_Width/2;
	isaacShape.bottom = m_CenterPos.y - m_Height / 2;
	isaacShape.width = m_Width;
	isaacShape.height = m_Height;
	return isaacShape;
}

bool Isaac::GetMotionState()
{
	if (m_IsaacDirection==Isaac::notMoving)
	{
		return true;
	}
	return false;
}

void Isaac::initRoomSize()
{

}

void Isaac::CheckPosition()
{
	Vector2f offset; Vector2f ExtraOffset;
	offset.x = 150.f;
	offset.y = 125.f;
	ExtraOffset.y = 85.f;
	ExtraOffset.x = 0;
	
	if (m_CenterPos.x > m_WindowSize.x-offset.x)
	{
		m_CenterPos.x = m_WindowSize.x-offset.x;
	}
	if (m_CenterPos.y > m_WindowSize.y-offset.y)
	{
		m_CenterPos.y = m_WindowSize.y-offset.y;
	}
	if (m_CenterPos.x < offset.x)
	{
		m_CenterPos.x = offset.x;
	}
	if (m_CenterPos.y < offset.y+ExtraOffset.y)
	{
		m_CenterPos.y = offset.y+ExtraOffset.y;
	}
}




