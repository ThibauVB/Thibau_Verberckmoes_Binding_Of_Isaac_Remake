#include "pch.h"
#include "Isaac.h"
Isaac::Isaac(Point2f StartingPoint, Point2f windowSize) : m_CenterPos(StartingPoint),
m_WindowSize(windowSize)
{
	initRoomSize();
}

void Isaac::DrawIsaac()const
{
	m_IsaacTexture.Draw(m_dstRectBody, m_srcRectBody);
	m_IsaacTexture.Draw(m_dstRectHead, m_SrcRectHead);

	utils::DrawPoint(m_CenterPos, 10);
}

void Isaac::UpdateIsaac(float elapsedSec)
{

	float OffsetX{ 35.f };
	float OffsetY{ 15.f };
	
	m_dstRectHead.width = 120.f;
	m_dstRectHead.height = 120.f;
	m_dstRectHead.left = m_CenterPos.x - m_SrcRectHead.width;
	m_dstRectHead.bottom = m_CenterPos.y - m_SrcRectHead.height;

	m_dstRectBody.width = 90.f;
	m_dstRectBody.height = 90.f;
	m_dstRectBody.left = m_CenterPos.x - m_srcRectBody.width;
	m_dstRectBody.bottom = m_CenterPos.y - m_srcRectBody.height-OffsetY*4;
	
	switch (m_IsaacDirection)
	{
	case MovingRightUP:
		m_CenterPos.x += elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_CenterPos.y += elapsedSec * (m_MoventSpeed- m_SideMoventDecrement);
		m_SrcRectHead.width = 40.f;
		m_SrcRectHead.height = 40.f;
		m_SrcRectHead.left = 200.f;
		m_SrcRectHead.bottom = 60.f;
		m_dstRectHead.left = m_CenterPos.x - m_SrcRectHead.width - OffsetX;

		m_srcRectBody.width = 30.f;
		m_srcRectBody.height = 25.f;
		m_srcRectBody.left = 15.f;
		m_srcRectBody.bottom = 100.f;
		
		break;
	case MovingRightDown:
		m_CenterPos.x += elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_CenterPos.y -= elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_SrcRectHead.width = 40.f;
		m_SrcRectHead.height = 40.f;
		m_SrcRectHead.left = 10.f;
		m_SrcRectHead.bottom = 60.f;
		break;
	case MovingLeftUp:
		m_CenterPos.x -= elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_CenterPos.y += elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_SrcRectHead.width = 40.f;
		m_SrcRectHead.height = 40.f;
		m_SrcRectHead.left = 200.f;
		m_SrcRectHead.bottom = 60.f;
		m_dstRectHead.left = m_CenterPos.x - m_SrcRectHead.width - OffsetX;
		break;
	case MovingLeftDown:
		m_CenterPos.x -= elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_CenterPos.y -= elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_SrcRectHead.width = 40.f;
		m_SrcRectHead.height = 40.f;
		m_SrcRectHead.left = 10.f;
		m_SrcRectHead.bottom = 60.f;
		break;
	case movingUp:
		m_CenterPos.y += elapsedSec * m_MoventSpeed;
		m_SrcRectHead.width = 40.f;
		m_SrcRectHead.height = 40.f;
		m_SrcRectHead.left = 200.f;
		m_SrcRectHead.bottom = 60.f;
		m_dstRectHead.left = m_CenterPos.x - m_SrcRectHead.width - OffsetX;
		m_dstRectHead.bottom = m_CenterPos.y - m_SrcRectHead.height - OffsetY;

		break;
	case movingDown:
		m_CenterPos.y -= elapsedSec * m_MoventSpeed;
		m_SrcRectHead.width = 40.f;
		m_SrcRectHead.height = 40.f;
		m_SrcRectHead.left = 10.f;
		m_SrcRectHead.bottom = 60.f;
		m_dstRectHead.left = m_CenterPos.x - m_SrcRectHead.width-5.f;
		m_dstRectHead.bottom = m_CenterPos.y - m_SrcRectHead.height - OffsetY;
		break;
	case movingLeft:
		m_CenterPos.x -= elapsedSec * m_MoventSpeed;
		m_SrcRectHead.width = 40.f;
		m_SrcRectHead.height = 40.f;
		m_SrcRectHead.left = 240.f;
		m_SrcRectHead.bottom = 60.f;
		m_dstRectHead.left = m_CenterPos.x - m_SrcRectHead.width - OffsetX;
		m_dstRectHead.bottom = m_CenterPos.y - m_SrcRectHead.height - OffsetY;

		break;
	case movingRight:
		m_CenterPos.x += elapsedSec * m_MoventSpeed;
		m_SrcRectHead.width = 40.f;
		m_SrcRectHead.height = 40.f;
		m_SrcRectHead.left = 80.f;
		m_SrcRectHead.bottom = 60.f;
		m_dstRectHead.left = m_CenterPos.x - m_SrcRectHead.width - OffsetX;
		m_dstRectHead.bottom = m_CenterPos.y - m_SrcRectHead.height-OffsetY;
		break;
	case notMoving:
		m_CenterPos.x += 0.f;
		m_CenterPos.y += 0.f;
		m_dstRectHead.left = m_CenterPos.x - m_SrcRectHead.width - OffsetX;
		m_dstRectHead.bottom = m_CenterPos.y - m_SrcRectHead.height - OffsetY;
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

Point2f Isaac::GetPostion()
{
	return m_CenterPos;
}

void Isaac::SetPlayerPos(Point2f pos)
{
	m_CenterPos = pos;
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




