#pragma once
#include "RoomClass.h"
#include "utils.h"
class DungeonGenerator
{
public:
	DungeonGenerator(Vector2f windowSize);
	~DungeonGenerator();
	void StartDungeonGeneration();
	bool GetDungeonCompletion();
	void DrawDungeon()const;
	void PrintAllCords();
	//void CleanDungeon();
private:
	int m_LeftChance;
	int m_RightChance;
	int m_TopChance;
	int m_BottomChance;
	int m_RoomCounter;
	int m_TotalRoomsInDungeon;
	float m_WidthNormal;
	float m_HeightNormal;
	utils::roomDirection m_TempDirectionSave;
	std::vector<RoomClass> m_RoomsList;
	bool m_completion;
	Vector2f m_WindowSize;
	Texture m_RoomTexture {"../Resources/Backgrounds/Room.png"};
	Texture m_TopDoorTexture { "../Resources/Backgrounds/TopDoor.png" };
	Texture m_RightDoorTexture { "../Resources/Backgrounds/RightDoor.png" };
	Texture m_LeftDoorTexture { "../Resources/Backgrounds/LeftDoor.png" };
	Texture m_BottomDoorTexture { "../Resources/Backgrounds/BottomDoor.png" };
	std::vector<utils::roomDirection> m_PossibleDirections;
	std::vector<Point2f> m_ExistingCenterPoints;
	//Private Helper Functions
	void CreateStartRoom();
	void CreateNormalRooms();
	Point2f GenerateNewRoomCenter();
	void InitDirections();
	bool IsAlreadyACenter(const Point2f& newCenter);
	void CheckForDoorConnections();
	int visRoom;
};
