#include "Game.h"

Game::Game()
{
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
}

void Game::backScreen(OptionsLoader *options, int screen)
{
	options->setCurrentScreen(screen);
}


