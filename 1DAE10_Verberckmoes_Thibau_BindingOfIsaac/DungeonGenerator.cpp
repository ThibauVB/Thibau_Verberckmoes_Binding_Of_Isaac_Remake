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
	m_LastDirection(utils::all),
	m_OpenDoors(false)
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
	m_AImanager.DrawEnemy();
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
	m_RoomsList.push_back(RoomClass{ center,m_WidthNormal,m_HeightNormal,utils::all,&m_RoomTexture,&m_TopDoorTexture,&m_RightDoorTexture,&m_BottomDoorTexture,&m_LeftDoorTexture,utils::StartingRoom });
	m_ExistingCenterPoints.push_back(center);
	std::cout << "Start Room Made" << std::endl;
}

void DungeonGenerator::CreateNormalRooms()
{
	std::cout << std::endl;
	std::cout << "Creating Normal Rooms" << std::endl;

	for (int index{ 0 }; index < m_TotalRoomsInDungeon; ++index)
	{
		utils::CameFromDoor tmpCamefrom;
		Point2f pos{ GenerateNewRoomCenter() };
		switch (m_TempDirectionSave)
		{
		case 0:
			std::cout << "left" << std::endl;
			tmpCamefrom = utils::DoorRight;
			break;
		case 1:
			std::cout << "right" << std::endl;
			tmpCamefrom = utils::DoorLeft;
			break;
		case 2:
			std::cout << "bottom" << std::endl;
			tmpCamefrom = utils::DoorUp;
			break;
		case 3:
			std::cout << "top" << std::endl;
			tmpCamefrom = utils::DoorDown;
			break;
		}
		m_RoomsList.push_back(RoomClass{ pos,m_WidthNormal,m_HeightNormal, m_TempDirectionSave,&m_RoomTexture,&m_TopDoorTexture,&m_RightDoorTexture,&m_BottomDoorTexture,&m_LeftDoorTexture , tmpCamefrom});
		//std::cout << "Room: "  << "direction: " << m_TempDirectionSave <<" Created" << "On Pos:" << m_ExistingCenterPoints[m_RoomCounter-(1)].x << ":" << m_ExistingCenterPoints[m_RoomCounter-(1)].y <<std::endl;
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

void DungeonGenerator::UpdateCurrentshownRoom(Point2f PlayerPos, Isaac& Player,float elapsedSec,const TearManager& tearmanager,std::vector<Tear*>& activetears,const SoundManager& soundManager)
{	
	//UPDATE AI
	m_AImanager.UpdateEnemies(elapsedSec,PlayerPos);
	Point2f tearPosition;
	for (int i{0};i<tearmanager.GetAmountOfActiveTears();++i)
	{
		tearPosition = tearmanager.GetTearPosition(i);
		std::cout << tearPosition.x << " " << tearPosition.y << std::endl;
		m_AImanager.TransferTearPositions(tearPosition,activetears,soundManager);
	}

	UpdateDoors();
	
	Rectf collisionBox;
	std::vector<bool> DoorValues;
	//This gets the current room player is in the 4 door states
	DoorValues = m_RoomsList[m_CurrentRoomDrawnCounter].GetDoorValues();
	//Test 0: Down, 1: Left, 2:Top,3:Right
	
	//is left door active
	if (m_OpenDoors == true)
	{
		if (DoorValues[0] == true)
		{
			collisionBox.left = 137.5f;
			collisionBox.bottom = m_HeightNormal / 2 - collisionBox.height / 2;
			collisionBox.height = 50.f;
			collisionBox.width = 25.f;

			if (utils::IsPointInRect(PlayerPos, collisionBox))
			{
				std::cout << "Player went in Left Door" << std::endl;
				UpdateRoomsPosition(1);
				Player.SetPlayerPos(Point2f{ m_WidthNormal / 2, m_HeightNormal / 2 });
				if (m_RoomsList[m_CurrentRoomDrawnCounter].GetLastDoor() == utils::DoorLeft)
				{
					--m_CurrentRoomDrawnCounter;
				}
				else
				{
					++m_CurrentRoomDrawnCounter;
					if (m_CurrentRoomDrawnCounter > m_HighestRoomEntered)
					{
						std::cout << "spawn enemy" << std::endl;
						++m_HighestRoomEntered;
						SpawnEnemy();
					}
				}
			}

		}
		//is right door active
		if (DoorValues[1] == true)
		{
			collisionBox.left = m_WidthNormal - 160.f;
			collisionBox.bottom = m_HeightNormal / 2 - collisionBox.height / 2;
			collisionBox.height = 50.f;
			collisionBox.width = 25.f;

			if (utils::IsPointInRect(PlayerPos, collisionBox))
			{
				std::cout << "Player went in Right Door" << std::endl;
				UpdateRoomsPosition(3);
				Player.SetPlayerPos(Point2f{ m_WidthNormal / 2, m_HeightNormal / 2 });
				if (m_RoomsList[m_CurrentRoomDrawnCounter].GetLastDoor() == utils::DoorRight)
				{
					--m_CurrentRoomDrawnCounter;
				}
				else
				{
					++m_CurrentRoomDrawnCounter;
					if (m_CurrentRoomDrawnCounter > m_HighestRoomEntered)
					{
						std::cout << "spawn enemy" << std::endl;
						++m_HighestRoomEntered;
						SpawnEnemy();
					}
				}

			}
		}
		//is bottom door active
		if (DoorValues[2] == true)
		{
			collisionBox.left = m_WidthNormal / 2 - collisionBox.width / 2;
			collisionBox.bottom = 188.f;
			collisionBox.width = 50.f;
			collisionBox.height = 25.f;
			if (utils::IsPointInRect(PlayerPos, collisionBox))
			{
				std::cout << "Player went in Bottom Door" << std::endl;
				UpdateRoomsPosition(0);
				Player.SetPlayerPos(Point2f{ m_WidthNormal / 2, m_HeightNormal / 2 });
				if (m_RoomsList[m_CurrentRoomDrawnCounter].GetLastDoor() == utils::DoorDown)
				{
					--m_CurrentRoomDrawnCounter;
				}
				else
				{
					++m_CurrentRoomDrawnCounter;
					if (m_CurrentRoomDrawnCounter > m_HighestRoomEntered)
					{
						std::cout << "spawn enemy" << std::endl;
						++m_HighestRoomEntered;
						SpawnEnemy();
					}
				}
			}
		}
		//is top door active
		if (DoorValues[3] == true)
		{
			collisionBox.left = m_WidthNormal / 2 - collisionBox.width / 2;
			collisionBox.bottom = m_HeightNormal - 140.f;
			collisionBox.width = 50.f;
			collisionBox.height = 25.f;
			if (utils::IsPointInRect(PlayerPos, collisionBox))
			{
				std::cout << "Player went in Top Door" << std::endl;
				UpdateRoomsPosition(2);
				Player.SetPlayerPos(Point2f{ m_WidthNormal / 2, m_HeightNormal / 2 });
				if (m_RoomsList[m_CurrentRoomDrawnCounter].GetLastDoor() == utils::DoorUp)
				{
					--m_CurrentRoomDrawnCounter;
				}
				else
				{
					++m_CurrentRoomDrawnCounter;
					if (m_CurrentRoomDrawnCounter > m_HighestRoomEntered)
					{
						std::cout << "spawn enemy" << std::endl;
						++m_HighestRoomEntered;
						SpawnEnemy();
					}
				}
			}
		}
	}
	

}

void DungeonGenerator::Changeroom(int x)
{
	UpdateRoomsPosition(x);
}

void DungeonGenerator::DrawCollisionBoxes(std::vector<Rectf> collisionRect)const
{
	for (size_t idX{ 0 }; idX < collisionRect.size(); ++idX)
	{
		utils::SetColor(Color4f{ 0,1,1,1 });
		utils::DrawRect(collisionRect[idX]);
	}

}

std::vector<Rectf> DungeonGenerator::GetCollisionBoxes() const
{
	return DoorCollisionBox;
}

int DungeonGenerator::GetAmountOfEnemieAI()
{
	return m_AImanager.GetAmountOfActiveEnemies();
}

Rectf DungeonGenerator::GetHitboxAI(int AI)
{
	return m_AImanager.GetHitBoxAI(AI);
}

Point2f DungeonGenerator::GetCenterPositionAI(int Ai)
{
	return m_AImanager.GetCenterPositionAI(Ai);
}

void DungeonGenerator::ResetDungeon()
{
	
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
		if (m_CurrentRoomDrawn<0)
		{
			m_CurrentRoomDrawn = 1;
		}
	}
	else
	{
		++m_CurrentRoomDrawn;
	}
}

Rectf DungeonGenerator::GetCurrentRoomBorders()
{
	return m_RoomsList[m_CurrentRoomDrawn].GetRoomBorders();
}

void DungeonGenerator::SpawnEnemy()
{
	int randomAmount;
	randomAmount = rand() % 5 + 1;
	Point2f RandomPos;
	Rectf RoomBorder;
	RoomBorder = GetCurrentRoomBorders();
	m_AImanager.SetAmountOfEnemies(randomAmount);
	for (int i{0};i<randomAmount;++i)
	{
		RandomPos.x = rand() % static_cast<int>(RoomBorder.width) + (RoomBorder.left);
		RandomPos.y = rand() % static_cast<int>(RoomBorder.height) + (RoomBorder.bottom);
		m_AImanager.CreateEnemy(RandomPos, GetCurrentRoomBorders());
	}
}

void DungeonGenerator::UpdateDoors()
{
	if (m_CurrentRoomDrawnCounter==0)
	{
		m_OpenDoors = true;;
	}else
	{
		if (m_AImanager.GetAmountOfActiveEnemies()==0)
		{
			m_OpenDoors = true;
		}else
		{
			m_OpenDoors = false;
		}
		//close doors unless all AI are dead
	}
}
