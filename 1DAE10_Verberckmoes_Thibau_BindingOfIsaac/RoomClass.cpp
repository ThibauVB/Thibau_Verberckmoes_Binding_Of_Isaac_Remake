#include "pch.h"
#include "RoomClass.h"

RoomClass::RoomClass(Point2f center, float width, float height, utils::roomDirection direction, Texture* texture, Texture* TopDoor, Texture* RightDoor, Texture* BottomDoor, Texture* LeftDoor,utils::CameFromDoor CameFrom) :
	m_Center(center),
	m_Width(width),
	m_Height(height),
	m_IsStartRoom(false),
	m_RoomTexture(texture),
	m_TextureScale(texture->GetWidth() / texture->GetWidth() * 160.f, texture->GetHeight() / texture->GetHeight() * 135.f),
	m_TopDoorTexture(TopDoor),
	m_RightDoorTexture(RightDoor),
	m_BottomDoorTexture(BottomDoor),
	m_LeftDoorTexture(LeftDoor),
	m_Direction(direction),
	m_CameFromDoor(CameFrom)
{
	switch (direction)
	{
	case utils::all:InitAsStartRoom(); break;
	case utils::bottom:InitRoom(true, false, false, false); break;
	case utils::top: InitRoom(false, false, false, true); break;
	case utils::right:InitRoom(false, true, false, false); break;
	case utils::left: InitRoom(false, false, true, false); break;
	}
	m_Offset.x = 150.f;
	m_Offset.y = 125.f;
	m_ExtraOffset.y = 85.f;
	m_ExtraOffset.x = 35;
	m_PlayArea.left = m_Offset.x - m_ExtraOffset.x;
	m_PlayArea.bottom = m_Offset.y;
	m_PlayArea.height = 800.0f - m_Offset.y - m_ExtraOffset.y;
	m_PlayArea.width = 1280.0f - m_Offset.x - m_ExtraOffset.y;
}
RoomClass::~RoomClass()
{
}

void RoomClass::InitAsStartRoom()
{
	//All doors are open for the starter room;
	InitRoom(true, true, true, true);
	m_IsStartRoom = true;
}

void RoomClass::InitRoom(bool top, bool left, bool right, bool bottom)
{
	m_RoomRect.bottom = m_Center.y - m_Height / 2;
	m_RoomRect.left = m_Center.x - m_Width / 2;
	m_RoomRect.height = m_Height;
	m_RoomRect.width = m_Width;

	m_Top = top;
	m_Left = left;
	m_Right = right;
	m_Bottom = bottom;
}

void RoomClass::DrawRoom() const
{
	//for door texture
	Rectf DoorRectf;
	Rectf DoorScale;
	float ScaleDoor{ 1.30f };
	DoorScale.bottom = 0;
	DoorScale.left = 0;
	DoorScale.height = m_TopDoorTexture->GetHeight();
	DoorScale.width = m_TopDoorTexture->GetWidth();
	//For Small Addons
	Vector2f offset; Vector2f ExtraOffset;
	offset.x = 150.f;
	offset.y = 125.f;
	ExtraOffset.y = 85.f;
	ExtraOffset.x = 0;

	if (!m_IsStartRoom)
	{
		utils::SetColor(Color4f{ 0.f,1.f,0.f,1.f });
	}
	else
	{
		utils::SetColor(Color4f{ 1.f,0.f,0.f,1.f });
	}

	utils::DrawRect(m_RoomRect, 2);
	Rectf destRect{};
	destRect.left = 0.f;
	destRect.height = 0.f;
	destRect.height = m_RoomTexture->GetHeight();
	destRect.width = m_RoomTexture->GetWidth();
	Rectf roomRect{};
	//roomRect.bottom = m_Center.y;
	//roomRect.left = m_Center.x;
	m_RoomTexture->Draw(m_RoomRect, destRect);
	const float doorWidth{ 20.f / 2 };
	const float doorHeight{ 50.f / 2 };

	Rectf tmpDoor;
	tmpDoor.width = doorWidth;
	tmpDoor.height = doorHeight;
	if (m_Left)
	{
		tmpDoor.left = (m_RoomRect.left - doorWidth / 2) + offset.x;
		tmpDoor.bottom = m_RoomRect.bottom + m_RoomRect.height / 2 - doorHeight / 2;

		DoorRectf.left = tmpDoor.left - 130.f;
		DoorRectf.bottom = tmpDoor.bottom - 50.f;
		DoorRectf.height = m_TopDoorTexture->GetHeight() * ScaleDoor;
		DoorRectf.width = m_TopDoorTexture->GetWidth() * ScaleDoor;
		m_LeftDoorTexture->Draw(DoorRectf, DoorScale);
		utils::FillRect(tmpDoor);
	}
	if (m_Right)
	{
		tmpDoor.left = (m_RoomRect.left + m_RoomRect.width - doorWidth / 2) - offset.x - 9.f;
		tmpDoor.bottom = m_RoomRect.bottom + m_RoomRect.height / 2 - doorHeight / 2 - 49.f;

		DoorRectf.left = tmpDoor.left;
		DoorRectf.bottom = tmpDoor.bottom;
		ScaleDoor = 1.30f;
		DoorRectf.height = m_TopDoorTexture->GetHeight() * ScaleDoor;
		DoorRectf.width = m_TopDoorTexture->GetWidth() * ScaleDoor;
		m_RightDoorTexture->Draw(DoorRectf, DoorScale);
		utils::FillRect(tmpDoor);
	}
	if (m_Top)
	{
		ScaleDoor = 1.30f;

		tmpDoor.left = m_RoomRect.left + m_RoomRect.width / 2 - doorHeight / 2;
		tmpDoor.bottom = (m_RoomRect.bottom + m_RoomRect.height - doorWidth / 2) - offset.y;
		tmpDoor.width = doorHeight;
		tmpDoor.height = doorWidth;

		DoorRectf.left = tmpDoor.left - m_TopDoorTexture->GetWidth() / 2 - 8.f;
		DoorRectf.bottom = tmpDoor.bottom - 12.f;
		DoorRectf.height = m_TopDoorTexture->GetHeight() * ScaleDoor;
		DoorRectf.width = m_TopDoorTexture->GetWidth() * ScaleDoor;
		m_TopDoorTexture->Draw(DoorRectf, DoorScale);
		utils::FillRect(tmpDoor);
	}
	if (m_Bottom)
	{
		tmpDoor.left = m_RoomRect.left + m_RoomRect.width / 2 - doorHeight / 2 - 50.f;
		tmpDoor.bottom = (m_RoomRect.bottom - doorWidth / 2) + 30.f;
		tmpDoor.width = doorHeight;
		tmpDoor.height = doorWidth;

		DoorRectf.left = tmpDoor.left;
		DoorRectf.bottom = tmpDoor.bottom;
		DoorRectf.height = m_TopDoorTexture->GetHeight() * ScaleDoor;
		DoorRectf.width = m_TopDoorTexture->GetWidth() * ScaleDoor;
		m_BottomDoorTexture->Draw(DoorRectf, DoorScale);
		utils::FillRect(tmpDoor);
	}
}

void RoomClass::SetNewDoors(bool left, bool right, bool top, bool bottom)
{
	m_Left = left;
	m_Right = right;
	m_Top = top;
	m_Bottom = bottom;
}

Point2f RoomClass::GetCenterPos()
{
	return m_Center;
}

std::vector<bool> RoomClass::GetDoorValues()
{
	std::vector<bool> values;
	//left,right,bottom,top
	values.push_back(m_Left);
	values.push_back(m_Right);
	values.push_back(m_Bottom);
	values.push_back(m_Top);
	return values;
}

std::vector<Rectf> RoomClass::GetDoorPlace()
{
	std::vector<Rectf> DoorPlacement;
	std::vector<bool> DoorValues{};
	DoorValues = GetDoorValues();
	//left , right , bottom , top
	const float doorWidth{ 20.f / 2 };
	const float doorHeight{ 50.f / 2 };
	Rectf BaseDoor;
	BaseDoor.width = doorWidth;
	BaseDoor.height = doorHeight;
	Vector2f offset;
	offset.x = 150.f;
	offset.y = 125.f;
	if (DoorValues[0] == true)
	{
		BaseDoor.left = (m_RoomRect.left - doorWidth / 2) + offset.x;
		BaseDoor.bottom = m_RoomRect.bottom + m_RoomRect.height / 2 - doorHeight / 2;
		DoorPlacement.push_back(BaseDoor);
	}
	if (DoorValues[1] == true)
	{
		BaseDoor.left = (m_RoomRect.left + m_RoomRect.width - doorWidth / 2) - offset.x - 9.f;
		BaseDoor.bottom = m_RoomRect.bottom + m_RoomRect.height / 2 - doorHeight / 2;
		DoorPlacement.push_back(BaseDoor);
	}
	if (DoorValues[2] == true)
	{
		BaseDoor.left = m_RoomRect.left + m_RoomRect.width / 2 - doorHeight / 2;
		BaseDoor.bottom = (m_RoomRect.bottom - doorWidth / 2) + 30.f;
		DoorPlacement.push_back(BaseDoor);
	}
	if (DoorValues[3] == true)
	{
		BaseDoor.left = m_RoomRect.left + m_RoomRect.width / 2 - doorHeight / 2;
		BaseDoor.bottom = (m_RoomRect.bottom + m_RoomRect.height - doorWidth / 2) - offset.y;
		DoorPlacement.push_back(BaseDoor);
	}
	return std::vector<Rectf>(DoorPlacement);
}

void RoomClass::SetRoomRect(int x)
{
	//0=>RoomsGoUp
	//1=>RoomsGotRight
	//2=>RoomsGoDown
	//3=>RoomsGotLeft
	
	switch (x)
	{
	case 0:
		m_RoomRect.bottom += m_Height;
		break;
	case 1:
		m_RoomRect.left += m_Width;
		break;
	case 2:
		m_RoomRect.bottom -= m_Height;
		break;
	case 3:
		m_RoomRect.left -= m_Width;
		break;
	}
}

utils::roomDirection RoomClass::GetDirection()
{
	return m_Direction;
}

utils::CameFromDoor RoomClass::GetLastDoor()
{
	return m_CameFromDoor;
}

Rectf RoomClass::GetRoomBorders()
{
	return m_PlayArea;
}
