#include "pch.h"
#include "Isaac.h"
Isaac::Isaac(Point2f StartingPoint, Point2f windowSize) : m_CenterPos(StartingPoint),
m_WindowSize(windowSize),
m_TimePassedForAnimation(0),
m_FramesPerSec(13),
m_NrOfFramesForBody(5),
m_AnimFrame(0),
m_health(3)
{
	initRoomSize();
}

void Isaac::DrawIsaac()const
{
	m_IsaacTexture.Draw(m_dstRectBody, m_srcRectBody);
	//utils::DrawPoint(m_CenterPos, 10);
}

void Isaac::UpdateIsaac(float elapsedSec)
{
	m_srcRectBody.width = 28.6;
	m_srcRectBody.height = 36;
	m_dstRectBody.width = 95.f;
	m_dstRectBody.height = 105.f;
	m_dstRectBody.left = m_CenterPos.x - 51.f;
	m_dstRectBody.bottom = m_CenterPos.y - m_srcRectBody.height - 10.f;
	TimeCounter(elapsedSec);
	switch (m_IsaacDirection)
	{
	case MovingRightUP:
		m_CenterPos.x += elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_CenterPos.y += elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_srcRectBody.left = (m_srcRectBody.width * m_AnimFrame);
		m_srcRectBody.bottom = 0;
		break;
	case MovingRightDown:
		m_CenterPos.x += elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_CenterPos.y -= elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_srcRectBody.left = (m_srcRectBody.width * m_AnimFrame);
		m_srcRectBody.bottom = 129.5;
		break;
	case MovingLeftUp:
		m_CenterPos.x -= elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_CenterPos.y += elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_srcRectBody.left = (m_srcRectBody.width * m_AnimFrame);
		m_srcRectBody.bottom = 0;
		break;
	case MovingLeftDown:
		m_CenterPos.x -= elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_CenterPos.y -= elapsedSec * (m_MoventSpeed - m_SideMoventDecrement);
		m_srcRectBody.left = (m_srcRectBody.width * m_AnimFrame);
		m_srcRectBody.bottom = 129.5;
		break;
	case movingUp:
		m_CenterPos.y += elapsedSec * m_MoventSpeed;
		m_srcRectBody.left = (m_srcRectBody.width * m_AnimFrame);
		m_srcRectBody.bottom = 0;
		break;
	case movingDown:
		m_CenterPos.y -= elapsedSec * m_MoventSpeed;
		m_srcRectBody.left = (m_srcRectBody.width * m_AnimFrame);
		m_srcRectBody.bottom = 129.5;
		break;
	case movingLeft:
		m_CenterPos.x -= elapsedSec * m_MoventSpeed;
		m_srcRectBody.left = (m_srcRectBody.width * m_AnimFrame);
		m_srcRectBody.bottom = 58.5;
		break;
	case movingRight:
		m_CenterPos.x += elapsedSec * m_MoventSpeed;
		m_srcRectBody.left = (m_srcRectBody.width * m_AnimFrame);
		m_srcRectBody.bottom = 94;
		break;
	case notMoving:
		m_srcRectBody.left = (m_srcRectBody.width * 0);
		m_srcRectBody.bottom = 129.5;;
		break;
	}
	CheckPosition(m_ActiveColisionBox);
}

void Isaac::SetDirection(WalkingDirection direction)
{
	m_IsaacDirection = direction;
}

Rectf Isaac::GetShape()const
{
	Rectf isaacShape;
	isaacShape.left = m_CenterPos.x - m_Width / 2;
	isaacShape.bottom = m_CenterPos.y - m_Height / 2;
	isaacShape.width = m_Width;
	isaacShape.height = m_Height;
	return isaacShape;
}

bool Isaac::GetMotionState()
{
	if (m_IsaacDirection == Isaac::notMoving)
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

void Isaac::DamageIsaac()
{
	--m_health;
}

int Isaac::GetHealth() const
{
	return m_health;
}

Rectf Isaac::GetShapeForCamera()const
{
	return m_srcRectBody;
}

void Isaac::SetActiveColisionBox(bool isActive)
{
	m_ActiveColisionBox = isActive;
}
void Isaac::initRoomSize()
{
}

void Isaac::CheckPosition(bool activeHitbox)
{
	if (activeHitbox == true)
	{
		Vector2f offset; Vector2f ExtraOffset;
		offset.x = 150.f;
		offset.y = 125.f;
		ExtraOffset.y = 40.f;
		ExtraOffset.x = 0;

		if (m_CenterPos.x > 1512.f - offset.x)
		{
			m_CenterPos.x = 1512.f - offset.x;
		}
		if (m_CenterPos.y > 905.f - offset.y)
		{
			m_CenterPos.y = 905.f - offset.y;
		}
		if (m_CenterPos.x < offset.x)
		{
			m_CenterPos.x = offset.x;
		}
		if (m_CenterPos.y < offset.y+ExtraOffset.y)
		{
			m_CenterPos.y = offset.y + ExtraOffset.y;
		}
	}else
	{
		Vector2f offset; Vector2f ExtraOffset;
		offset.x = 150.f;
		offset.y = 125.f;
		ExtraOffset.y = 85.f;
		ExtraOffset.x = 0;

		if (m_CenterPos.x > m_WindowSize.x - offset.x)
		{
			m_CenterPos.x = m_WindowSize.x - offset.x;
		}
		if (m_CenterPos.y > m_WindowSize.y - offset.y)
		{
			m_CenterPos.y = m_WindowSize.y - offset.y;
		}
		if (m_CenterPos.x < offset.x)
		{
			m_CenterPos.x = offset.x;
		}
		if (m_CenterPos.y < offset.y + ExtraOffset.y)
		{
			m_CenterPos.y = offset.y + ExtraOffset.y;
		}
	}
	
}

void Isaac::TimeCounter(float elapsedTime)
{
	m_TimePassedForAnimation += elapsedTime;
	if (m_TimePassedForAnimation >= 1.f / m_FramesPerSec)
	{
		m_AnimFrame++;
		if (m_AnimFrame >= m_NrOfFramesForBody)
		{
			m_AnimFrame = 0;
		}
		m_TimePassedForAnimation = 0;
	}
}