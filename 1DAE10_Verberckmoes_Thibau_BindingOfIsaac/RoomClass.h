#pragma once
#include "Texture.h"
#include "utils.h"
#include <vector>
class RoomClass
{
public:
	explicit RoomClass(Point2f center, float width, float height, utils::roomDirection direction, Texture* texture, Texture* TopDoor, Texture* RightDoor, Texture* BottomDoor, Texture* LeftDoor, utils::CameFromDoor CameFrom);
	explicit RoomClass(Point2f center, float width, float height, Texture* roomtexture);
	~RoomClass();
	void InitAsStartRoom();
	void InitRoom(bool top, bool left, bool right, bool bottom);
	void DrawRoom()const;
	void DrawBossRoom()const;
	void SetNewDoors(bool left, bool right, bool top, bool bottom);
	Point2f GetCenterPos();
	std::vector<bool> GetDoorValues();
	void SetDoorTextures(const Texture& texture);
	std::vector<Rectf> GetDoorPlace();
	void SetRoomRect(int x);
	utils::roomDirection GetDirection();
	utils::CameFromDoor GetLastDoor();
	Rectf GetRoomBorders();
private:
	utils::roomDirection m_Direction;
	utils::CameFromDoor m_CameFromDoor;
	Vector2f m_TextureScale;
	Point2f m_Center;
	float m_Width;
	float m_Height;
	Rectf m_RoomRect;
	bool m_IsStartRoom;
	bool m_Left, m_Right, m_Top, m_Bottom;
	Texture* m_RoomTexture;
	Texture* m_TopDoorTexture;
	Texture* m_RightDoorTexture;
	Texture* m_LeftDoorTexture;
	Texture* m_BottomDoorTexture;

	Vector2f m_Offset; Vector2f m_ExtraOffset;
	Rectf m_PlayArea{};
};