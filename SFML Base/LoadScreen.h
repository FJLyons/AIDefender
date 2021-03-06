#pragma once

// SFML Headers
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <iostream>

#include "GlobalVariables.h"
#include "InputManager.h"
#include "ResourceLoader.h"

class LoadScreen
{
private:
	GlobalVariables* myGlobalOptions = GlobalVariables::getInstance();
	InputManager* inputManager = InputManager::getInstance();
	ResourceLoader* resource = ResourceLoader::instance();

public:
	LoadScreen();
	~LoadScreen();

	void init();
	void update();
	void draw(sf::RenderWindow &window);
	void input(sf::Event Event);


private:
	sf::Vector2f screenSize = myGlobalOptions->screenSize;

	void goToScene(int screen);

	sf::Font font;
	sf::Text text;
};

