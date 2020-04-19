#include "pch.h"
#include "DungeonGenerator.h"

DungeonGenerator::DungeonGenerator(Vector2f windowSize) :
	m_LeftChance(25),
	m_RightChance(25),
	m_TopChance(25),
	m_BottomChance(25),
	m_WidthNormal(1280.f), //1280.0f
	m_HeightNormal(800.f), //800.0f
	m_completion(false),
	m_WindowSize(windowSize),
	m_RoomCounter(0),
	m_TempDirectionSave(utils::all),
	m_TotalRoomsInDungeon(10),
	m_CurrentRoomDrawn(0),
	m_LastDirection(utils::all)
{
	InitDirections();
}

void DungeonGenerator::StartDungeonGeneration()
{
	std::cout << "Started Creating dungeon's" << std::endl;
	CreateStartRoom();
	CreateNormalRooms();
}

bool DungeonGenerator::GetDungeonCompletion()
{
	return m_completion;
}

void DungeonGenerator::DrawDungeon() const
{
	for (int x{ 0 }; x < m_RoomsList.size(); ++x)
	{
		m_RoomsList[x].DrawRoom();
	}
}

DungeonGenerator::~DungeonGenerator()
{
}

void DungeonGenerator::CreateStartRoom()
{
	Point2f center;
	center.x = m_WindowSize.x / 2;
	center.y = m_WindowSize.y / 2;
	//std::cout << center.x << " " << center.y << std::endl;
	m_RoomsList.push_back(RoomClass{ center,m_WidthNormal,m_HeightNormal,utils::all,&m_RoomTexture,&m_TopDoorTexture,&m_RightDoorTexture,&m_BottomDoorTexture,&m_LeftDoorTexture });
	m_ExistingCenterPoints.push_back(center);
	std::cout << "Start Room Made" << std::endl;
}

void DungeonGenerator::CreateNormalRooms()
{
	std::cout << std::endl;
	std::cout << "Creating Normal Rooms" << std::endl;

	for (int index{ 0 }; index < m_TotalRoomsInDungeon; ++index)
	{
		Point2f pos{ GenerateNewRoomCenter() };
		m_RoomsList.push_back(RoomClass{ pos,m_WidthNormal,m_HeightNormal, m_TempDirectionSave,&m_RoomTexture,&m_TopDoorTexture,&m_RightDoorTexture,&m_BottomDoorTexture,&m_LeftDoorTexture });
		//std::cout << "Room: "  << "direction: " << m_TempDirectionSave <<" Created" << "On Pos:" << m_ExistingCenterPoints[m_RoomCounter-(1)].x << ":" << m_ExistingCenterPoints[m_RoomCounter-(1)].y <<std::endl;
		switch (m_TempDirectionSave)
		{
		case 0:std::cout << "left" << std::endl; break;
		case 1:std::cout << "right" << std::endl; break;
		case 2:std::cout << "bottom" << std::endl; break;
		case 3:std::cout << "top" << std::endl; break;
		}
		m_ExistingCenterPoints.push_back(pos);
		//	std::cout << pos.x << " " << pos.y << std::endl;
	}
	std::cout << std::endl;
	std::cout << "All Rooms Created" << std::endl;
	m_completion = true;
	std::cout << "Checking New doors" << std::endl;
	CheckForDoorConnections();
	std::cout << "Fixing StartingRoom" << std::endl;
	FixStartRoom();
	std::cout << "Fixing Roomspositions and doors" << std::endl;
	FixRooms();
	std::cout << "Dungeon Ready" << std::endl;
}

Point2f DungeonGenerator::GenerateNewRoomCenter()
{
	Point2f newCenter{}, oldCenter{ m_ExistingCenterPoints[m_RoomCounter] };
	bool repeat{ true };

	utils::roomDirection newDirection;
	do
	{
		const int RandomPercentage{ rand() % 101 + 1 };
		newDirection = { m_PossibleDirections[RandomPercentage] };

		switch (newDirection)
		{
		case utils::left:
			newCenter.x = oldCenter.x - m_WidthNormal;
			newCenter.y = oldCenter.y;
			if (IsAlreadyACenter(newCenter) == true)
			{
				repeat = true;
				break;
			}

			m_LeftChance -= 9;
			m_RightChance += 3;
			m_TopChance += 3;
			m_BottomChance += 3;
			if (m_LeftChance < 0)	m_LeftChance = 0;
			InitDirections();
			repeat = false;
			std::cout << "Direction Created" << std::endl;
			break;
		case utils::right:
			newCenter.x = oldCenter.x + m_WidthNormal;
			newCenter.y = oldCenter.y;
			if (IsAlreadyACenter(newCenter) == true)
			{
				repeat = true;

				break;
			}

			m_LeftChance += 3;
			m_RightChance -= 9;
			m_TopChance += 3;
			m_BottomChance += 3;
			if (m_RightChance < 0)	m_RightChance = 0;
			InitDirections();
			repeat = false;
			std::cout << "Direction Created" << std::endl;
			break;
		case utils::top:
			newCenter.x = oldCenter.x;
			newCenter.y = oldCenter.y + m_HeightNormal;
			if (IsAlreadyACenter(newCenter) == true)
			{
				repeat = true;

				break;
			}
			m_LeftChance += 3;
			m_RightChance += 3;
			m_TopChance -= 9;
			m_BottomChance += 3;
			if (m_TopChance < 0)	m_TopChance = 0;
			InitDirections();
			repeat = false;
			std::cout << "Direction Created" << std::endl;
			break;
		case utils::bottom:
			newCenter.x = oldCenter.x;
			newCenter.y = oldCenter.y - m_HeightNormal;
			if (IsAlreadyACenter(newCenter) == true)
			{
				repeat = true;
				break;
			}
			m_LeftChance += 3;
			m_RightChance += 3;
			m_TopChance += 3;
			m_BottomChance -= 9;
			if (m_BottomChance < 0)	m_BottomChance = 0;
			InitDirections();
			repeat = false;
			std::cout << "Direction Created" << std::endl;
			break;
		}
	} while (repeat == true);

	m_TempDirectionSave = newDirection;
	++m_RoomCounter;
	return newCenter;
}

void DungeonGenerator::InitDirections()
{
	for (size_t index{ 0 }; index < m_LeftChance; ++index)
	{
		m_PossibleDirections.push_back(utils::left);
	}
	for (size_t index{ 0 }; index < m_RightChance; ++index)
	{
		m_PossibleDirections.push_back(utils::right);
	}
	for (size_t index{ 0 }; index < m_TopChance; ++index)
	{
		m_PossibleDirections.push_back(utils::bottom);
	}
	for (size_t index{ 0 }; index < m_BottomChance; ++index)
	{
		m_PossibleDirections.push_back(utils::top);
	}
}

void DungeonGenerator::PrintAllCords()
{
	for (auto items : m_ExistingCenterPoints)
	{
		std::cout << items.x << " : " << items.y << std::endl;
	}
}

void DungeonGenerator::UpdateCurrentshownRoom(Point2f PlayerPos, Isaac& Player)
{
	//	Movement Dungeon
	//	Test 0: Down, 1: Left, 2:Top,3:Right

	//left,right,bottom,top
	std::vector<Rectf> DoorCollisionBox{};
	std::vector<bool> doorValues;
	doorValues = m_RoomsList[m_CurrentRoomDrawn].GetDoorValues();
	DoorCollisionBox = m_RoomsList[m_CurrentRoomDrawn].GetDoorPlace();
	Point2f pos{ m_WidthNormal / 2,m_HeightNormal / 2 };

	//if (doorValues[0] == true)
	//{
	//	for (Rectf doors : DoorCollisionBox)
	//	{
	//		if (PlayerPos.x<doors.left + doors.width && PlayerPos.y>doors.bottom&& PlayerPos.y < doors.bottom + doors.height)
	//		{
	//			std::cout << "Player is in Left Door" << std::endl;
	//			UpdateCurrentRoomCounter(utils::left);
	//			m_LastDirection = utils::right;
	//			std::cout << m_CurrentRoomDrawn << std::endl;
	//			UpdateRoomsPosition(1);
	//			Player.SetPlayerPos(pos);
	//		}
	//	}
	//}else
	//if (doorValues[1] == true)
	//{
	//	for (Rectf doors : DoorCollisionBox)
	//	{
	//		if (PlayerPos.x > doors.left&& PlayerPos.y > doors.bottom&& PlayerPos.y < doors.bottom + doors.height)
	//		{
	//			std::cout << "Player is in Right Door" << std::endl;
	//			UpdateCurrentRoomCounter(utils::right);
	//			m_LastDirection = utils::left;
	//			std::cout << m_CurrentRoomDrawn << std::endl;
	//			UpdateRoomsPosition(3);
	//			Player.SetPlayerPos(pos);

	//		}
	//	}
	//}else
	//if (doorValues[2] == true)
	//{
	//	for (Rectf doors : DoorCollisionBox)
	//	{
	//		if (PlayerPos.x > doors.left&& PlayerPos.x < doors.left + doors.width && PlayerPos.y < doors.bottom + doors.height + 215.f)
	//		{
	//			std::cout << "Player is in Bottom Door" << std::endl;
	//			UpdateCurrentRoomCounter(utils::bottom);
	//			m_LastDirection = utils::top;
	//			std::cout << m_CurrentRoomDrawn << std::endl;
	//			UpdateRoomsPosition(0);
	//			Player.SetPlayerPos(pos);
	//		}
	//	}
	//}else
	//if (doorValues[3] == true)
	//{
	//	for (Rectf doors : DoorCollisionBox)
	//	{
	//		if (PlayerPos.x > doors.left&& PlayerPos.x < doors.left + doors.width && PlayerPos.y > doors.bottom)
	//		{
	//			std::cout << "Player is in Top Door" << std::endl;
	//			UpdateCurrentRoomCounter(utils::top);
	//			m_LastDirection = utils::bottom;
	//			std::cout << m_CurrentRoomDrawn << std::endl;
	//			UpdateRoomsPosition(2);
	//			Player.SetPlayerPos(pos);

	//		}
	//	}
	//}

	for (int x{ 0 }; x < DoorCollisionBox.size(); ++x)
	{
		if (doorValues[0] == true)
		{
			if (PlayerPos.x<DoorCollisionBox[x].left + DoorCollisionBox[x].width && PlayerPos.y>DoorCollisionBox[x].bottom&& PlayerPos.y < DoorCollisionBox[x].bottom + DoorCollisionBox[x].height)
			{
				std::cout << "Player is in Left Door" << std::endl;
				UpdateCurrentRoomCounter(utils::left);
				m_LastDirection = utils::right;
				std::cout << m_CurrentRoomDrawn << std::endl;
				UpdateRoomsPosition(1);
				Player.SetPlayerPos(pos);
			}
		}

		if (doorValues[1] == true)
		{
			if (PlayerPos.x > DoorCollisionBox[x].left&& PlayerPos.y > DoorCollisionBox[x].bottom&& PlayerPos.y < DoorCollisionBox[x].bottom + DoorCollisionBox[x].height)
			{
				std::cout << "Player is in Right Door" << std::endl;
				UpdateCurrentRoomCounter(utils::right);
				m_LastDirection = utils::left;
				std::cout << m_CurrentRoomDrawn << std::endl;
				UpdateRoomsPosition(3);
				Player.SetPlayerPos(pos);
			}
		}
		if (doorValues[2] == true)
		{
			if (PlayerPos.x > DoorCollisionBox[x].left&& PlayerPos.x < DoorCollisionBox[x].left + DoorCollisionBox[x].width && PlayerPos.y < DoorCollisionBox[x].bottom + DoorCollisionBox[x].height + 215.f)
			{
				std::cout << "Player is in Bottom Door" << std::endl;
				UpdateCurrentRoomCounter(utils::bottom);
				m_LastDirection = utils::top;
				std::cout << m_CurrentRoomDrawn << std::endl;
				UpdateRoomsPosition(0);
				Player.SetPlayerPos(pos);
			}
		}
		if (doorValues[3] == true)
		{
			if (PlayerPos.x > DoorCollisionBox[x].left&& PlayerPos.x < DoorCollisionBox[x].left + DoorCollisionBox[x].width && PlayerPos.y > DoorCollisionBox[x].bottom)
			{
				std::cout << "Player is in Top Door" << std::endl;
				UpdateCurrentRoomCounter(utils::top);
				m_LastDirection = utils::bottom;
				std::cout << m_CurrentRoomDrawn << std::endl;
				UpdateRoomsPosition(2);
				Player.SetPlayerPos(pos);
			}
		}
	}
}

void DungeonGenerator::Changeroom(int x)
{
	UpdateRoomsPosition(x);
}

void DungeonGenerator::UpdateRoomsPosition(int direction)
{
	for (int x{ 0 }; x < m_RoomsList.size(); ++x)
	{
		m_RoomsList[x].SetRoomRect(direction);
	}
}

void DungeonGenerator::FixStartRoom()
{
	std::vector<bool> DoorValues{ m_RoomsList[1].GetDoorValues() };
	bool left{}, right{}, bottom{}, top{};
	if (DoorValues[0] == true)
	{
		right = true;
	}

	if (DoorValues[1] == true)
	{
		left = true;
	}

	if (DoorValues[2] == true)
	{
		top = true;
	}

	if (DoorValues[3] == true)
	{
		bottom = true;
	}
	m_RoomsList[0].SetNewDoors(left, right, top, bottom);
}

bool DungeonGenerator::IsAlreadyACenter(const Point2f& center)
{
	for (int x{ 0 }; x < m_RoomCounter; ++x)
	{
		if (center.x == m_ExistingCenterPoints[x].x && center.y == m_ExistingCenterPoints[x].y)
		{
			return true;
		}
	}
	return false;
}

void DungeonGenerator::CheckForDoorConnections()
{
	//LEFT RIGHT BOTTOM TOP
	//rooms.SetNewDoors(values[0], values[1], values[2], values[3]);
	bool test{ false };
	std::vector<bool> values;
	Point2f CurrentRoomCenter;
	for (RoomClass rooms : m_RoomsList)
	{
		values = rooms.GetDoorValues();
		CurrentRoomCenter = { rooms.GetCenterPos() };
		for (size_t idX{ 0 }; idX < m_RoomCounter; ++idX)
		{
			if (CurrentRoomCenter.x + m_WidthNormal == m_ExistingCenterPoints[idX].x && CurrentRoomCenter.y == m_ExistingCenterPoints[idX].y)
			{
				rooms.SetNewDoors(values[0], true, values[2], values[3]);
				test = true;
			};
			if (CurrentRoomCenter.x - m_WidthNormal == m_ExistingCenterPoints[idX].x && CurrentRoomCenter.y == m_ExistingCenterPoints[idX].y)
			{
				test = true;
				rooms.SetNewDoors(true, values[1], values[2], values[3]);
			};
			if (CurrentRoomCenter.x == m_ExistingCenterPoints[idX].x && CurrentRoomCenter.y - m_HeightNormal == m_ExistingCenterPoints[idX].y)
			{
				test = true;
				rooms.SetNewDoors(values[0], values[1], values[2], true);
			};
			if (CurrentRoomCenter.x == m_ExistingCenterPoints[idX].x && CurrentRoomCenter.y + m_HeightNormal == m_ExistingCenterPoints[idX].y)
			{
				test = true;
				rooms.SetNewDoors(values[0], values[1], true, values[3]);
			};
			if (test) std::cout << "true" << std::endl;
			test = false;
		}
	}
}

void DungeonGenerator::FixRooms()
{
	//left,right,bottom,top

	utils::roomDirection NextDirection{};
	std::vector<bool> doorvalues;

	for (size_t idX{ 0 }; idX < 10; ++idX)
	{
		if (idX + 1 < 10)
		{
			doorvalues = m_RoomsList[idX].GetDoorValues();
			NextDirection = m_RoomsList[idX + 1].GetDirection();
			if (NextDirection == utils::left)
			{
				doorvalues[0] = true;
			}
			if (NextDirection == utils::right)
			{
				doorvalues[1] = true;
			}
			if (NextDirection == utils::bottom)
			{
				doorvalues[2] = true;
			}
			if (NextDirection == utils::top)
			{
				doorvalues[3] = true;
			}
			m_RoomsList[idX].SetNewDoors(doorvalues[0], doorvalues[1], doorvalues[3], doorvalues[2]);
		}
	}
}

void DungeonGenerator::UpdateCurrentRoomCounter(utils::roomDirection directionToCheck)
{
	if (m_LastDirection == directionToCheck)
	{
		--m_CurrentRoomDrawn;
	}
	else
	{
		++m_CurrentRoomDrawn;
	}
}