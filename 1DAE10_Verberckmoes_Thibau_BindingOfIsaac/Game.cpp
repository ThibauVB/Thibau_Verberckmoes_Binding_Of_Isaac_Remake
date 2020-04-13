#include "pch.h"
#include "Game.h"

Game::Game(const Window& window)
	:m_Window{ window },
	m_DungeonGenerator(Vector2f{m_Window.width,m_Window.height}),
	m_Isaac(Point2f{ m_Window.width / 2,m_Window.height / 2 }, Point2f{m_Window.width,m_Window.height }),
	m_Camera(m_Window.width,m_Window.height),
	m_StartScreen(false),
	m_TextureStartScreen("../Resources/Backgrounds/StartingScreen.jpg")
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
}

void Game::Cleanup()
{
}

void Game::Update(float elapsedSec)
{
	// Check keyboard state
	if(m_StartScreen==false)
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



		if (pStates[SDL_SCANCODE_UP])
		{
			std::cout << "Shooting Up" << std::endl;
		}
		if (pStates[SDL_SCANCODE_RIGHT])
		{
			std::cout << "Shooting Right" << std::endl;
		}
		if (pStates[SDL_SCANCODE_DOWN])
		{
			std::cout << "Shooting Down" << std::endl;
		}
		if (pStates[SDL_SCANCODE_LEFT])
		{
			std::cout << "Shooting Left" << std::endl;
		}
		m_Isaac.UpdateIsaac(elapsedSec);
		m_Isaac.SetDirection(Isaac::notMoving);
	}
	else
	{
		
	}
	
}

void Game::Draw() const
{
	ClearBackground();
	if (m_StartScreen==false)
	{
		utils::SetColor(Color4f{ 1.f,1.f,1.f,1.f });
		utils::DrawPoint(Point2f{ m_Window.width / 2,m_Window.height / 2 }, 10);
		m_DungeonGenerator.DrawDungeon();
		m_Camera.Draw(m_Isaac.GetShape());
		m_Isaac.DrawIsaac();
	}else
	{
		DrawStartScreen();
	}

	
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
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

