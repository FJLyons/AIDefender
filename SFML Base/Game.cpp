#include "Game.h"

Game::Game(InputManager* im)
{
	inputManager = im;
	terrain = new Terrain();
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

	player1 = new Player(playershipTexture, sf::Vector2f(200, 200), sf::Vector2f(20, 20));//set up player
	human1 = new Human(humanTexture,terrain->getPoints());
}

void Game::update()
{
	player1->Update();
	human1->Update();
}

void Game::draw(sf::RenderWindow &window)
{
	//window.draw(text);
	player1->Draw(window);
	human1->Draw(window);
	terrain->draw(window);
}

void Game::input(sf::Event Event)
{
	inputManager->update(Event);
	controller(Event);
}

void Game::backScreen(OptionsLoader *options, int screen)
{
	options->setCurrentScreen(screen);
}

void Game::controller(sf::Event Event)
{
	if (inputManager->KeyPressed(sf::Keyboard::A))
	{
		player1->MoveLeft(true);
	}
	else if (inputManager->KeyReleased(sf::Keyboard::A))
	{
		player1->MoveLeft(false);
	}

	if (inputManager->KeyPressed(sf::Keyboard::D))
	{
		player1->MoveRight(true);
	}
	else if (inputManager->KeyReleased(sf::Keyboard::D))
	{
		player1->MoveRight(false);
	}

	if (inputManager->KeyPressed(sf::Keyboard::W))
	{
		player1->MoveUp(true);
	}
	else if (inputManager->KeyReleased(sf::Keyboard::W))
	{
		player1->MoveUp(false);
	}

	if (inputManager->KeyPressed(sf::Keyboard::S))
	{
		player1->MoveDown(true);
	}
	else if (inputManager->KeyReleased(sf::Keyboard::S))
	{
		player1->MoveDown(false);
	}

	if (inputManager->KeyPressed(sf::Keyboard::Space))
	{
		player1->Shoot(bulletTexture);
	}
}