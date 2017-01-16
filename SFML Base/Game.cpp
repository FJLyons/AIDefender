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

	obstacleTexture.loadFromFile("assets/obstacles/meteor.png");
	obstacleTexture.setSmooth(true);

	font.loadFromFile("content\\fonts\\kenvector_future.TTF");

	terrain = new Terrain();
	player = new Player(playershipTexture, screenSize * 0.5f, sf::Vector2f(30, 30));//set up player
	human = new Human(humanTexture,terrain->getPoints());
	meteor = new Obstacles(obstacleTexture);
}

void Game::update()
{
	player->Update();
	human->Update();
	meteor->Update();
	camera->update(player);


	teleport();

}

void Game::draw(sf::RenderWindow &window)
{
	//Game
	camera->drawGame(window);
	terrain->draw(window);
	player->Draw(window);
	meteor->Draw(window);
	human->Draw(window, false);

	// Mini Map
	camera->drawRadar(window);
	terrain->draw(window);
	player->Draw(window);
	meteor->Draw(window);
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
	else if (inputManager->KeyHeld(sf::Keyboard::A) && !inputManager->KeyHeld(sf::Keyboard::D))
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
	else if (inputManager->KeyHeld(sf::Keyboard::D) && !inputManager->KeyHeld(sf::Keyboard::A))
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
	if (inputManager->KeyHeld(sf::Keyboard::Space))
	{
		player->Shoot(bulletTexture);
	}
}

void Game::teleport()
{
	if (player->teleport())
	{
		// Human
		if (human->getPoint() < (SCREEN_WIDTH_POINTS) && player->teleportLeft == true)
		{
			human->setPoint(human->getPoint() + MAP_WIDTH_POINTS);
		}

		else if (human->getPoint() > FULL_WIDTH_POINTS - (SCREEN_WIDTH_POINTS) && player->teleportLeft == false)
		{
			human->setPoint(human->getPoint() - MAP_WIDTH_POINTS);
		}

		// Obstacle
		if (meteor->getPosition().x < (SCREEN_WIDTH_PIXEL) && player->teleportLeft == true)
		{
			meteor->setPosition(sf::Vector2f(meteor->getPosition().x + (MAP_WIDTH_PIXEL), meteor->getPosition().y));
		}

		else if (meteor->getPosition().x > (FULL_WIDTH_PIXEL) - (HALF_SCREEN_WIDTH_PIXEL * 3) && player->teleportLeft == false)
		{
			meteor->setPosition(sf::Vector2f(meteor->getPosition().x - (MAP_WIDTH_PIXEL), meteor->getPosition().y));
		}
	}
}