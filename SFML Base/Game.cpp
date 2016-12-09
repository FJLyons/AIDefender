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
	font.loadFromFile("content\\fonts\\kenvector_future.TTF");
	text.setFont(font);
	text.setString("Main Game");
	text.setPosition(screenSize.x / 2, screenSize.y / 2);
	text.setCharacterSize(18);
}

void Game::update()
{

}

void Game::draw(sf::RenderWindow &window)
{
	window.draw(text);
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
	if (Event.type == sf::Event::KeyPressed)
	{
		std::cout << Event.key.code << std::endl;
	}
	if (inputManager->KeyPressed(sf::Keyboard::A)) { std::cout << "A" << std::endl; }
}