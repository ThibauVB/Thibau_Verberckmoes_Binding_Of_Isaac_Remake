#include "pch.h"
#include "Camera.h"

Camera::Camera(float width, float height) :
	m_Width{ width },
	m_Height{ height }
{
	m_LevelBoundaries = Rectf{ 0,0,m_Width,m_Height };
}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

void Camera::Draw(const Rectf& target) const
{
	Point2f drawPos{};
	drawPos = Track(target);
	Clamp(drawPos);
	glTranslatef(-drawPos.x, -drawPos.y, 0);
}

Point2f Camera::Track(const Rectf& target) const
{
	Point2f newPos{ target.left + (target.width / 2) - m_Width / 2,target.bottom + (target.height / 2) - m_Height / 2 };
	return  newPos;
}

void Camera::Clamp(Point2f& bottomLeftPos) const
{
	if (bottomLeftPos.x < m_LevelBoundaries.left)
	{
		bottomLeftPos.x = m_LevelBoundaries.left;
	}
	if (bottomLeftPos.y < m_LevelBoundaries.bottom)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom;
	}
	if (bottomLeftPos.x + m_Width > m_LevelBoundaries.left + m_LevelBoundaries.width)
	{
		bottomLeftPos.x = (m_LevelBoundaries.left + m_LevelBoundaries.width) - m_Width;
	}
	if (bottomLeftPos.y + m_Height > m_LevelBoundaries.bottom + m_LevelBoundaries.height)
	{
		bottomLeftPos.y = (m_LevelBoundaries.bottom + m_LevelBoundaries.height) - m_Height;
	}
}