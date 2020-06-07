#pragma once
#include "Room.h"
#include "DungeonGenerator.h"
#include "Isaac.h"
#include "Camera.h"
#include "TearManager.h"
#include "AiManager.h"
#include "SoundManager.h"
#include "UImanager.h"
class Game
{
public:
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update(float elapsedSec);
	void Draw() const;
	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

private:
	const Window m_Window;
	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;
	void DrawStartScreen() const;
	void DrawEndScreen()const;
	void ShowControls();
	void TestDrawCollisionBoxes()const;
	void InitializeGame();
	void CheckIfGameStart(Point2f pos);
	void CheckIfPlayerIsHit(float ElapsedSec);
	void CheckKeysPressed();
	void FullGameReset();
	Rectf StartButton;
	Isaac m_Isaac;
	Camera m_Camera;
	bool m_StartScreen;
	Texture m_TextureStartScreen;
	Texture m_TextureDeathNote;
	float m_TimeCounter;
	bool TestBoolForDoor{ false };
	bool m_CanGetHit;
	float m_ElapsedTimeSinceHit;
	//Managers/Generators
	DungeonGenerator m_DungeonGenerator;
	TearManager m_TearManager;
	Rectf m_HitboxButton;
	SoundManager m_SoundManager;
	UImanager m_UImanager;
};