#pragma once
#include <vector>
class Room
{
public:

	explicit Room();
	explicit Room(float width, float height, bool dLeft, bool dRight, bool dBottom, bool dTop, Point2f center);
	void DrawRoom()const;
	void InitRoom(Point2f centerPos);
	utils::RoomInfo GetRoomInfo();
private:
	//Private Enum's
	enum Doorposition {
		top
		, right
		, down
		, left
	};

	//Private data
	float m_Width;
	float m_Height;
	Point2f m_CenterOfRoom;
	Rectf m_RoomShape;
	const int m_MaxDoors{ 4 };
	bool m_LeftDoor;
	bool m_RightDoor;
	bool m_TopDoor;
	bool m_BottomDoor;
	std::vector<Doorposition> m_ActiveDoors;
	//Private functions
	void DrawDoors()const;
};
