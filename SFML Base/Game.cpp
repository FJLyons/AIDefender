#include "Game.h"

Game::Game(Camera* cam)
{
	camera = cam;
	init();
}

Game::~Game()
{
}

void Game::init()
{
	playershipTexture.loadFromFile("assets/player/PlayerShip.png");
	playershipTexture.setSmooth(true);
	humanTexture.loadFromFile("assets/ai/human.png");
	humanTexture.setSmooth(true);
	backgroundTexture.loadFromFile("assets/background/background.png");
	bulletTexture.loadFromFile("assets/player/bullet.png");
	font.loadFromFile("content\\fonts\\kenvector_future.TTF");

	terrain = new Terrain();
	player = new Player(playershipTexture, screenSize * 0.5f, sf::Vector2f(30, 30));//set up player
	human = new Human(humanTexture,terrain->getPoints());
}

void Game::update()
{
	player->Update();
	teleport();
	human->Update();
	camera->update(player);

}

void Game::draw(sf::RenderWindow &window)
{
	//Game
	camera->drawGame(window);
	terrain->draw(window);
	player->Draw(window);
	human->Draw(window, false);

	// Mini Map
	camera->drawRadar(window);
	terrain->draw(window);
	player->Draw(window);
	human->Draw(window, true);
}

void Game::goToScene(int scene)
{
	myGlobalOptions->setCurrentScene(scene);
}

void Game::input(sf::Event Event)
{
	if (Event.type == sf::Event::KeyPressed)
	{
		std::cout << Event.key.code << std::endl;
	}

	if (inputManager->KeyPressed(sf::Keyboard::BackSpace))
	{
		camera->resetView();
		std::cout << "Back Space" << std::endl;
		goToScene(myGlobalOptions->MAINMENU);
	}

	controller(Event);
}

void Game::controller(sf::Event Event)
{
	// Left
	if (inputManager->KeyPressed(sf::Keyboard::A))
	{
		player->FaceLeft();
	}
	else if (inputManager->KeyHeld(sf::Keyboard::A))
	{
		player->MoveLeft();
	}
	else if (inputManager->KeyReleased(sf::Keyboard::A))
	{
		//player->MoveLeft();
	}

	// Right
	if (inputManager->KeyPressed(sf::Keyboard::D))
	{
		player->FaceRight();
	}
	else if (inputManager->KeyHeld(sf::Keyboard::D))
	{
		player->MoveRight();
	}
	else if (inputManager->KeyReleased(sf::Keyboard::D))
	{
		//player->MoveRight();
	}

	// Up
	if (inputManager->KeyPressed(sf::Keyboard::W))
	{
		player->MoveUp(true);
	}
	else if (inputManager->KeyReleased(sf::Keyboard::W))
	{
		player->MoveUp(false);
	}

	// Down
	if (inputManager->KeyPressed(sf::Keyboard::S))
	{
		player->MoveDown(true);
	}
	else if (inputManager->KeyReleased(sf::Keyboard::S))
	{
		player->MoveDown(false);
	}

	// Shoot
	if (inputManager->KeyPressed(sf::Keyboard::Space))
	{
		player->Shoot(bulletTexture);
	}
}

void Game::teleport()
{
	if (player->teleport())
	{
		if (human->getPoint() < HALF_SCREEN_WIDTH * 2 && player->teleportLeft == true)
		{
			human->setPoint(human->getPoint() + MAP_WIDTH);
		}

		else if (human->getPoint() > FULL_WIDTH - (HALF_SCREEN_WIDTH * 2) && player->teleportLeft == false)
		{
			human->setPoint(human->getPoint() - MAP_WIDTH);
		}
	}
}