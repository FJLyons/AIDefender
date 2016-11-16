#include "OptionsLoader.h"


OptionsLoader::OptionsLoader()
{
	init();
}


OptionsLoader::~OptionsLoader()
{
}

void OptionsLoader::init()
{
	currentScreen = GameStates::SPLASH;
}

void OptionsLoader::update()
{

}

void OptionsLoader::draw(sf::RenderWindow &window)
{

}

int OptionsLoader::getCurrentScreen(){ return currentScreen; }
void OptionsLoader::setCurrentScreen(int current){ currentScreen = current; }
