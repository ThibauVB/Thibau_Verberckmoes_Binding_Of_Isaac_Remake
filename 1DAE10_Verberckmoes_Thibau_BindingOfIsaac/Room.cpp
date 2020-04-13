#include "pch.h"
#include "Room.h"

Room::Room()
{
	std::cout << "Default Room Constructor Called" << std::endl;
}

Room::Room(float width, float height, bool dLeft, bool dRight, bool dBottom, bool dTop, Point2f center) :
	m_Width(width)
	, m_Height(height)
	, m_LeftDoor(dLeft)
	, m_RightDoor(dRight)
	, m_TopDoor(dTop)
	, m_BottomDoor(dBottom)
	, m_CenterOfRoom(center)
{
	std::cout << "Room Constructor Called" << std::endl;
	InitRoom(m_CenterOfRoom);
}

void Room::DrawRoom() const
{
	utils::DrawRect(m_RoomShape, 2);
	DrawDoors();
}

void Room::DrawDoors() const
{
	const float doorWidth{ 20.f };
	const float doorHeight{ 50.f };

	//Place door on Room width or Height / 2 for now;
	//Room width and height 20x50px;
	Rectf tmpDoor;
	tmpDoor.width = doorWidth;
	tmpDoor.height = doorHeight;
	if (m_LeftDoor)
	{
		tmpDoor.left = m_RoomShape.left - doorWidth / 2;
		tmpDoor.bottom = m_RoomShape.bottom + m_RoomShape.height / 2 - doorHeight / 2;

		utils::FillRect(tmpDoor);
	}
	if (m_RightDoor)
	{
		tmpDoor.left = m_RoomShape.left + m_RoomShape.width - doorWidth / 2;
		tmpDoor.bottom = m_RoomShape.bottom + m_RoomShape.height / 2 - doorHeight / 2;

		utils::FillRect(tmpDoor);
	}
	if (m_TopDoor)
	{
		tmpDoor.left = m_RoomShape.left + m_RoomShape.width / 2 - doorHeight / 2;
		tmpDoor.bottom = m_RoomShape.bottom + m_RoomShape.height - doorWidth / 2;
		tmpDoor.width = doorHeight;
		tmpDoor.height = doorWidth;
		utils::FillRect(tmpDoor);
	}
	if (m_BottomDoor)
	{
		tmpDoor.left = m_RoomShape.left + m_RoomShape.width / 2 - doorHeight / 2;
		tmpDoor.bottom = m_RoomShape.bottom - doorWidth / 2;
		tmpDoor.width = doorHeight;
		tmpDoor.height = doorWidth;
		utils::FillRect(tmpDoor);
	}
}

void Room::InitRoom(Point2f centerPos)
{
	std::cout << "Room Initialized" << std::endl;
	m_RoomShape.left = centerPos.x - m_Width / 2;
	m_RoomShape.bottom = centerPos.y - m_Height / 2;
	m_RoomShape.height = m_Height;
	m_RoomShape.width = m_Width;
}

utils::RoomInfo Room::GetRoomInfo()
{
	utils::RoomInfo currentRoom;
	std::cout << "GetRoomInfo" << std::endl;
	//std::cout << m_LeftDoor << " : " << m_RightDoor << " : " << m_BottomDoor << " : " << m_TopDoor << std::endl;

	currentRoom.left = m_LeftDoor;
	currentRoom.right = m_RightDoor;
	currentRoom.bottom = m_BottomDoor;
	currentRoom.top = m_TopDoor;
	currentRoom.centerRoomPos = m_CenterOfRoom;
	return currentRoom;
}