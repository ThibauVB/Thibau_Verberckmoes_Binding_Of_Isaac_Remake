#pragma once
#include "RoomClass.h"
#include "utils.h"
#include "Isaac.h"
#include "AiManager.h"
#include "TearManager.h"
#include "SoundManager.h"
class Tear;

class DungeonGenerator
{
public:
	explicit DungeonGenerator(Vector2f windowSize);
	~DungeonGenerator();
	void StartDungeonGeneration();
	bool GetDungeonCompletion();
	void DrawDungeon()const;
	void PrintAllCords();
	void UpdateCurrentshownRoom(Point2f PlayerPos, Isaac& Player, float elapsedSec, const TearManager& tearmanager, std::vector<Tear*>& activetears, const SoundManager& soundManager);
	void Changeroom(int x);
	void DrawCollisionBoxes(std::vector<Rectf> collisionRect)const;
	void DeleteEnemy();
	void DrawBossDoor()const;
	std::vector<Rectf> GetCollisionBoxes()const;
	int GetAmountOfEnemieAI();
	Rectf GetHitboxAI(int AI);
	Point2f GetCenterPositionAI(int Ai);
	void ResetDungeon();
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
	int m_CurrentRoomDrawnCounter;
	utils::roomDirection m_TempDirectionSave;
	std::vector<RoomClass> m_RoomsList;
	//RoomClass m_BossRoom;
	bool m_completion;
	Vector2f m_WindowSize;
	Texture m_RoomTexture{ "../Resources/Backgrounds/Room.png" };
	Texture m_TopDoorTexture{ "../Resources/Backgrounds/TopDoor.png" };
	Texture m_RightDoorTexture{ "../Resources/Backgrounds/RightDoor.png" };
	Texture m_LeftDoorTexture{ "../Resources/Backgrounds/LeftDoor.png" };
	Texture m_BottomDoorTexture{ "../Resources/Backgrounds/BottomDoor.png" };
	Texture m_BoosRoomTexture{ "../Resources/Backgrounds/BossRoom.png" };
	std::vector<utils::roomDirection> m_PossibleDirections;
	std::vector<Point2f> m_ExistingCenterPoints;
	int m_CurrentRoomDrawn;
	utils::roomDirection m_LastDirection;
	std::vector<Rectf> DoorCollisionBox{};
	int m_HighestRoomEntered;
	AiManager m_AImanager;
	//Private Helper Functions
	void CreateStartRoom();
	void CreateNormalRooms();
	Point2f GenerateNewRoomCenter();
	void InitDirections();
	bool IsAlreadyACenter(const Point2f& newCenter);
	void CheckForDoorConnections();
	void UpdateRoomsPosition(int direction);
	void FixStartRoom();
	void FixRooms();
	void UpdateCurrentRoomCounter(utils::roomDirection directionToCheck);
	Rectf GetCurrentRoomBorders();
	void SpawnEnemy();
	void UpdateDoors();
	bool m_OpenDoors;
};
