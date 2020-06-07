#include "pch.h"
#include "Game.h"

Game::Game(const Window& window)
	:m_Window{ window },
	m_DungeonGenerator(Vector2f{ m_Window.width,m_Window.height }),
	m_Isaac(Point2f{ m_Window.width / 2,m_Window.height / 2 }, Point2f{ m_Window.width,m_Window.height }),
	m_Camera(m_Window.width, m_Window.height),
	m_StartScreen(true),
	m_TextureStartScreen("../Resources/Backgrounds/StartingScreen.jpg"),
	m_TextureDeathNote("../Resources/Backgrounds/StartingScreen.jpg"),
	m_TearManager(m_Window),
	m_TimeCounter(0),
	m_SoundManager(),
	m_CanGetHit(true),
	m_ElapsedTimeSinceHit(0)
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_HitboxButton.width = 450.f;
	m_HitboxButton.height = 500.f;
	m_HitboxButton.left = m_Window.width / 2 - m_HitboxButton.width / 2;
	m_HitboxButton.bottom = m_Window.height / 2 - m_HitboxButton.height / 2 - 80.f;
}

void Game::Cleanup()
{
}

void Game::Update(float elapsedSec)
{
	

	// Check keyboard state
	if (m_StartScreen != true)
	{
		if (m_Isaac.GetHealth() != 0)
		{
			CheckKeysPressed();
			CheckIfPlayerIsHit(elapsedSec);
			m_TimeCounter += elapsedSec;
			m_Isaac.UpdateIsaac(elapsedSec);
			m_Isaac.SetDirection(Isaac::notMoving);
			m_TearManager.UpdateTears(elapsedSec, &m_SoundManager);
			m_DungeonGenerator.UpdateCurrentshownRoom(m_Isaac.GetPostion(), m_Isaac, elapsedSec, m_TearManager, m_TearManager.GetActiveTearsVector(), m_SoundManager);
		}else
		{
			//When Dead
		}
	}
}

void Game::Draw() const
{
	
	ClearBackground();
	if (m_StartScreen != true)
	{
		if (m_Isaac.GetHealth() !=0)
		{
			utils::SetColor(Color4f{ 1.f,1.f,1.f,1.f });
			utils::DrawPoint(Point2f{ m_Window.width / 2,m_Window.height / 2 }, 10);
			m_DungeonGenerator.DrawDungeon();
			m_Camera.Draw(m_Isaac.GetShape());
			m_Isaac.DrawIsaac();
			m_TearManager.DrawTears();
			m_UImanager.DrawHeart();
			TestDrawCollisionBoxes();
		}else
		{
			DrawEndScreen();
		}

	}
	else
	{
		DrawStartScreen();
		TestDrawCollisionBoxes();
	}
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.scancode)
	{
	case SDL_SCANCODE_I:ShowControls(); break;
	}
	if (m_StartScreen == true)
	{
		InitializeGame();
		m_StartScreen = false;
		m_SoundManager.PlayStartingSound();
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

	if (m_StartScreen == true)
	{
		switch (e.button)
		{
		case SDL_BUTTON_LEFT:
			CheckIfGameStart(Point2f{ static_cast<float>(e.x),static_cast<float>(e.y) });
			break;
		}
	}

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
	Rectf dstrect, roomsize;
	roomsize.left = 0;
	roomsize.bottom = 0;
	roomsize.width = m_Window.width;
	roomsize.height = m_Window.height;
	
	m_TextureStartScreen.Draw(roomsize,dstrect);
}

void Game::DrawEndScreen() const
{
	Rectf dstrect, roomsize;
	roomsize.left = 0;
	roomsize.bottom = 0;
	roomsize.width = m_Window.width;
	roomsize.height = m_Window.height;

	m_TextureDeathNote.Draw(roomsize, dstrect);
}

void Game::ShowControls()
{
	std::cout << "#############################################################" << std::endl;
	std::cout << "Move Up: W or Z key (depending on settings)" << std::endl;
	std::cout << "Move Right: D key" << std::endl;
	std::cout << "Move Down: S key" << std::endl;
	std::cout << "Move Left: A or Q key (depending on settings)" << std::endl;

	std::cout << "Shoot Up: ArrowUpKey" << std::endl;
	std::cout << "Shoot Right: ArrowRightKey" << std::endl;
	std::cout << "shoot Down: ArrowDownKey" << std::endl;
	std::cout << "Shoot Left: ArrowLeftKey" << std::endl;
	std::cout << "#############################################################" << std::endl;
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

void Game::InitializeGame()
{
	m_DungeonGenerator.StartDungeonGeneration();
	m_Camera.SetLevelBoundaries(Rectf{ 0,0,m_Window.width,m_Window.height });
}

void Game::CheckIfGameStart(Point2f pos)
{
	if (utils::IsPointInRect(pos,m_HitboxButton))
	{
		InitializeGame();
		m_StartScreen = false;
		m_SoundManager.PlayStartingSound();
	}
}

void Game::CheckIfPlayerIsHit(float ElapsedSec)
{
	m_ElapsedTimeSinceHit += ElapsedSec;
	if (m_ElapsedTimeSinceHit > 2) 
	{
		m_CanGetHit = true;
		m_ElapsedTimeSinceHit = 0;
	}
	if (m_CanGetHit)
	{
		Rectf enemyHitbox{};
		Rectf IsaacHitbox{};
		Point2f centerposIsaac{};
		Point2f centerPosAi{};
		int amountOfActiveAI{};
		IsaacHitbox = m_Isaac.GetShape();
		centerposIsaac = m_Isaac.GetPostion();

		IsaacHitbox.left = centerposIsaac.x - IsaacHitbox.width / 2;
		IsaacHitbox.bottom = centerposIsaac.y - IsaacHitbox.height / 2;
		for (size_t idX{ 0 }; idX < m_DungeonGenerator.GetAmountOfEnemieAI(); ++idX)
		{
			enemyHitbox = m_DungeonGenerator.GetHitboxAI(idX);
			centerPosAi = m_DungeonGenerator.GetCenterPositionAI(idX);

			enemyHitbox.left = centerPosAi.x - enemyHitbox.width / 2;
			enemyHitbox.bottom = centerPosAi.y - enemyHitbox.height / 2;

			if (utils::IsOverlapping(enemyHitbox, IsaacHitbox))
			{
				m_Isaac.DamageIsaac();
				m_CanGetHit = false;
				m_SoundManager.PlayGruntSound();
				break;
			}
		}
	}
	m_UImanager.UpdateHeart(m_Isaac.GetHealth());
}

void Game::CheckKeysPressed()
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
			m_TearManager.CreateTear(m_Isaac.GetPostion(), utils::ShootingUp, &m_SoundManager);
		}
		if (pStates[SDL_SCANCODE_RIGHT])
		{
			m_TearManager.CreateTear(m_Isaac.GetPostion(), utils::ShootingRight, &m_SoundManager);
		}
		if (pStates[SDL_SCANCODE_DOWN])
		{
			m_TearManager.CreateTear(m_Isaac.GetPostion(), utils::ShootingDown, &m_SoundManager);
		}
		if (pStates[SDL_SCANCODE_LEFT])
		{
			m_TearManager.CreateTear(m_Isaac.GetPostion(), utils::ShootingLeft, &m_SoundManager);
		}
		m_TimeCounter = 0;
	}
}

void Game::FullGameReset()
{
	
}
