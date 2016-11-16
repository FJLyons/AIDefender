#include "InstructionsScreen.h"



InstructionsScreen::InstructionsScreen()
{
	init();
}


InstructionsScreen::~InstructionsScreen()
{
}

void InstructionsScreen::init()
{
	font.loadFromFile("content\\fonts\\kenvector_future.TTF");
	text.setFont(font);
	text.setString("Instructions");
	text.setPosition(screenSize.x / 2, screenSize.y / 2);
	text.setCharacterSize(18);
}

void InstructionsScreen::update()
{

}

void InstructionsScreen::draw(sf::RenderWindow &window)
{
	window.draw(text);
}

void InstructionsScreen::backScreen(OptionsLoader *options, int screen)
{
	options->setCurrentScreen(screen);
}