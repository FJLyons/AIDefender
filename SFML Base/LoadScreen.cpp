#include "LoadScreen.h"



LoadScreen::LoadScreen()
{
	init();
}


LoadScreen::~LoadScreen()
{
}

void LoadScreen::init()
{
	font.loadFromFile("content\\fonts\\kenvector_future.TTF");
	text.setFont(font);
	text.setString("Load Game");
	text.setPosition(screenSize.x / 2, screenSize.y / 2);
	text.setCharacterSize(18);
}

void LoadScreen::update()
{

}

void LoadScreen::draw(sf::RenderWindow &window)
{
	window.draw(text);
}

void LoadScreen::backScreen(OptionsLoader *options, int screen)
{
	options->setCurrentScreen(screen);
}