#include "pch.h"
#include "DungeonGenerator.h"

DungeonGenerator::DungeonGenerator(Vector2f windowSize) :
	m_LeftChance(25),
	m_RightChance(25),
	m_TopChance(25),
	m_BottomChance(25),
	m_WidthNormal(1280.0f), //1280.0f
	m_HeightNormal(800.0f), //800.0f
	m_completion(false),
	m_WindowSize(windowSize),
	m_RoomCounter(0),
	m_TempDirectionSave(utils::all),
	m_TotalRoomsInDungeon(10),
	m_CurrentRoomDrawn(0)
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
	for (int x{0};x<m_RoomsList.size();++x)
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
	m_RoomsList.push_back(RoomClass{ center,m_WidthNormal,m_HeightNormal,utils::all,&m_RoomTexture,&m_TopDoorTexture,&m_RightDoorTexture,&m_BottomDoorTexture,&m_LeftDoorTexture});
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
	
}

Point2f DungeonGenerator::GenerateNewRoomCenter()
{
	Point2f newCenter{}, oldCenter{ m_ExistingCenterPoints[m_RoomCounter] };
	bool repeat{ true };

	utils::roomDirection newDirection;
	do
	{
		const int RandomPercentage{ rand() % 101 + 1 };
		newDirection ={ m_PossibleDirections[RandomPercentage] };
		
		switch (newDirection)
		{
		case utils::left:
			newCenter.x = oldCenter.x - m_WidthNormal;
			newCenter.y = oldCenter.y;
			if (IsAlreadyACenter(newCenter)==true)
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
			if (IsAlreadyACenter(newCenter)==true)
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
			if (IsAlreadyACenter(newCenter)==true)
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
			newCenter.y = oldCenter.y-m_HeightNormal;
			if (IsAlreadyACenter(newCenter)==true)
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
	for (size_t index{0}; index<m_LeftChance;++index)
	{
			m_PossibleDirections.push_back(utils::left);
	}
	for (size_t index{0}; index<m_RightChance;++index)
	{
			m_PossibleDirections.push_back(utils::right);
	}
	for (size_t index{0}; index<m_TopChance;++index)
	{
			m_PossibleDirections.push_back(utils::bottom);
	}
	for (size_t index{0}; index<m_BottomChance;++index)
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

void DungeonGenerator::UpdateCurrentshownRoom(Point2f PlayerPos)
{
	//to see wich doors are active
	//left , right , bottom , top
	std::vector<Rectf> DoorCollisionBox{};
	std::vector<bool> doorValues;
	doorValues = m_RoomsList[m_CurrentRoomDrawn].GetDoorValues();
	DoorCollisionBox = m_RoomsList[m_CurrentRoomDrawn].GetDoorPlace();
	//
	
	if (doorValues[0] == true)
	{
		if (PlayerPos.x<DoorCollisionBox[0].left+ DoorCollisionBox[0].width && PlayerPos.y>DoorCollisionBox[0].bottom && PlayerPos.y < DoorCollisionBox[0].bottom+ DoorCollisionBox[0].height)
		{
			std::cout << "Player is in Left Door" << std::endl;
			//UpdateRoomsPosition(1);
		}
	}
	if (doorValues[1] == true)
	{
		if (PlayerPos.x>DoorCollisionBox[1].left && PlayerPos.y>DoorCollisionBox[1].bottom&& PlayerPos.y < DoorCollisionBox[1].bottom + DoorCollisionBox[0].height)
		{
			std::cout << "Player is in Right Door" << std::endl;
			//UpdateRoomsPosition(3);

		}
	}
	if (doorValues[2] == true)
	{
		if (PlayerPos.x > DoorCollisionBox[2].left && PlayerPos.x < DoorCollisionBox[2].left+DoorCollisionBox[2].width && PlayerPos.y < DoorCollisionBox[2].bottom + DoorCollisionBox[2].height+215.f)
		{
			std::cout << "Player is in Bottom Door" << std::endl;
			//UpdateRoomsPosition(0);

		}
	}
	if (doorValues[3] == true)
	{
		if (PlayerPos.x > DoorCollisionBox[3].left&& PlayerPos.x < DoorCollisionBox[3].left + DoorCollisionBox[3].width && PlayerPos.y > DoorCollisionBox[3].bottom)
		{
			std::cout << "Player is in Top Door" << std::endl;
			//UpdateRoomsPosition(2);

		}
	}

}

void DungeonGenerator::UpdateRoomsPosition(int direction)
{
	for (int x{ 0 }; x < m_RoomsList.size(); ++x)
	{
		m_RoomsList[x].SetRoomRect(direction);
	}
}


bool DungeonGenerator::IsAlreadyACenter(const Point2f& center)
{
	for (int x{0}; x<m_RoomCounter;++x)
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
	bool test{false};
	std::vector<bool> values;
	Point2f CurrentRoomCenter;
	for (RoomClass rooms : m_RoomsList)
	{
		values = rooms.GetDoorValues();
		CurrentRoomCenter = { rooms.GetCenterPos() };
		for (size_t idX{0};idX<m_RoomCounter;++idX)
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
			if (CurrentRoomCenter.x == m_ExistingCenterPoints[idX].x && CurrentRoomCenter.y-m_HeightNormal == m_ExistingCenterPoints[idX].y)
			{
				test = true;
				rooms.SetNewDoors(values[0], values[1], values[2], true);
			};
			if (CurrentRoomCenter.x == m_ExistingCenterPoints[idX].x && CurrentRoomCenter.y+m_HeightNormal == m_ExistingCenterPoints[idX].y)
			{
				test = true;
				rooms.SetNewDoors(values[0], values[1], true, values[3]);
			};
			if (test) std::cout << "true" << std::endl;
			test = false;
		}
	}
}





