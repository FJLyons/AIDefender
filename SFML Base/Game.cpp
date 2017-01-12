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
	player = new Player(playershipTexture, sf::Vector2f(200, 200), sf::Vector2f(20, 20));//set up player
	human1 = new Human(humanTexture,terrain->getPoints());
}

void Game::update()
{
	player->Update();
	human1->Update();
	camera->update(player);
}

void Game::draw(sf::RenderWindow &window)
{
	//window.draw(text);
	camera->draw(window);
	player->Draw(window);
	human1->Draw(window);
	terrain->draw(window);
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
		player->MoveLeft(true);
	}
	else if (inputManager->KeyReleased(sf::Keyboard::A))
	{
		player->MoveLeft(false);
	}

	// Right
	if (inputManager->KeyPressed(sf::Keyboard::D))
	{
		player->MoveRight(true);
	}
	else if (inputManager->KeyReleased(sf::Keyboard::D))
	{
		player->MoveRight(false);
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