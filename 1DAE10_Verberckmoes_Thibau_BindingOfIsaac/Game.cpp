#include "pch.h"
#include "Game.h"

Game::Game(const Window& window)
	:m_Window{ window },
	m_DungeonGenerator(Vector2f{ m_Window.width,m_Window.height }),
	m_Isaac(Point2f{ m_Window.width / 2,m_Window.height / 2 }, Point2f{ m_Window.width,m_Window.height }),
	m_Camera(m_Window.width, m_Window.height),
	m_StartScreen(false),
	m_TextureStartScreen("../Resources/Backgrounds/StartingScreen.jpg"),
	m_TearManager(m_Window),
	m_TimeCounter(0)
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_DungeonGenerator.StartDungeonGeneration();
	m_Camera.SetLevelBoundaries(Rectf{ 0,0,m_Window.width,m_Window.height });
	m_AImanager.CreateEnemy(Point2f{ 100,100 });
}

void Game::Cleanup()
{
}

void Game::Update(float elapsedSec)
{
	// Check keyboard state
	if (m_StartScreen == false)
	{
		const Uint8* pStates = SDL_GetKeyboardState(nullptr);

		if (pStates[SDL_SCANCODE_W] == true && pStates[SDL_SCANCODE_D] == true)
		{
			m_Isaac.SetDirection(Isaac::MovingRightUP);
		}
		if (pStates[SDL_SCANCODE_W] == true && pStates[SDL_SCANCODE_A] == true)
		{
			m_Isaac.SetDirection(Isaac::MovingLeftUp);
		}
		if (pStates[SDL_SCANCODE_S] == true && pStates[SDL_SCANCODE_D] == true)
		{
			m_Isaac.SetDirection(Isaac::MovingRightDown);
		}
		if (pStates[SDL_SCANCODE_S] == true && pStates[SDL_SCANCODE_A] == true)
		{
			m_Isaac.SetDirection(Isaac::MovingLeftDown);
		}

		if (m_Isaac.GetMotionState())
		{
			if (pStates[SDL_SCANCODE_W])
			{
				m_Isaac.SetDirection(Isaac::movingUp);
			}

			if (pStates[SDL_SCANCODE_D])
			{
				m_Isaac.SetDirection(Isaac::movingRight);
			}

			if (pStates[SDL_SCANCODE_S])
			{
				m_Isaac.SetDirection(Isaac::movingDown);
			}

			if (pStates[SDL_SCANCODE_A])
			{
				m_Isaac.SetDirection(Isaac::movingLeft);
			}
		}

		//left , right , bottom , top
		if (m_TimeCounter > 0.3f)
		{
			if (pStates[SDL_SCANCODE_UP])
			{
				m_TearManager.CreateTear(m_Isaac.GetPostion(), utils::ShootingUp);
			}
			if (pStates[SDL_SCANCODE_RIGHT])
			{
				m_TearManager.CreateTear(m_Isaac.GetPostion(), utils::ShootingRight);
			}
			if (pStates[SDL_SCANCODE_DOWN])
			{
				m_TearManager.CreateTear(m_Isaac.GetPostion(), utils::ShootingDown);
			}
			if (pStates[SDL_SCANCODE_LEFT])
			{
				m_TearManager.CreateTear(m_Isaac.GetPostion(), utils::ShootingLeft);
			}
			m_TimeCounter = 0;
		}

		m_TimeCounter += elapsedSec;
		m_Isaac.UpdateIsaac(elapsedSec);
		m_Isaac.SetDirection(Isaac::notMoving);
		m_TearManager.UpdateTears(elapsedSec);
		m_DungeonGenerator.UpdateCurrentshownRoom(m_Isaac.GetPostion(), m_Isaac);
	}
	else
	{
	}
}

void Game::Draw() const
{
	ClearBackground();
	if (m_StartScreen == false)
	{
		utils::SetColor(Color4f{ 1.f,1.f,1.f,1.f });
		utils::DrawPoint(Point2f{ m_Window.width / 2,m_Window.height / 2 }, 10);
		m_DungeonGenerator.DrawDungeon();
		m_Camera.Draw(m_Isaac.GetShape());
		m_Isaac.DrawIsaac();
		m_TearManager.DrawTears();
		TestDrawCollisionBoxes();
		m_AImanager.DrawEnemy();
	}
	else
	{
		DrawStartScreen();
	}
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.scancode)
	{
	case SDL_SCANCODE_I:ShowControls(); break;
	}
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::DrawStartScreen() const
{
	m_TextureStartScreen.Draw(Point2f{ 0,0 });
}

void Game::ShowControls()
{
	std::cout << "Move Up: W or Z key (depending on settings)" << std::endl;
	std::cout << "Move Right: D" << std::endl;
	std::cout << "Move Down: S" << std::endl;
	std::cout << "Move Left: A or Q" << std::endl;

	std::cout << "Shoot Up: ArrowUpKey" << std::endl;
	std::cout << "Shoot Right: ArrowRightKey" << std::endl;
	std::cout << "shoot Down: ArrowDownKey" << std::endl;
	std::cout << "Shoot Left: ArrowLeftKey" << std::endl;
}

void Game::TestDrawCollisionBoxes() const
{
	Rectf collisionBox;
	collisionBox.width = 50.f;
	collisionBox.height = 25.f;
	//Middle Bottom
	collisionBox.left = m_Window.width / 2- collisionBox.width/2;
	collisionBox.bottom = 188.f;
	utils::DrawRect(collisionBox);

	//Middle Top
	collisionBox.left = m_Window.width / 2 - collisionBox.width / 2;
	collisionBox.bottom = m_Window.height - 140.f;
	utils::DrawRect(collisionBox);

	//LeftMiddle
	collisionBox.left = 137.5f;
	collisionBox.bottom = m_Window.height / 2 - collisionBox.height / 2;
	collisionBox.height = 50.f;
	collisionBox.width = 25.f;
	utils::DrawRect(collisionBox);

	//RightMiddle
	collisionBox.left = m_Window.width - 160.f;
	collisionBox.bottom = m_Window.height / 2 - collisionBox.height / 2;
	collisionBox.height = 50.f;
	collisionBox.width = 25.f;
	utils::DrawRect(collisionBox);




	Vector2f offset; Vector2f ExtraOffset;
	offset.x = 150.f;
	offset.y = 125.f;
	ExtraOffset.y = 85.f;
	ExtraOffset.x = 35;
	Rectf PlayArea{};
	PlayArea.left = offset.x- ExtraOffset.x;
	PlayArea.bottom = offset.y;
	PlayArea.height = m_Window.height - offset.y- ExtraOffset.y;
	PlayArea.width = m_Window.width - offset.x -ExtraOffset.y;
	utils::DrawRect(PlayArea);

	
}
