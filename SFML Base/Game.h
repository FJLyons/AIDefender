#pragma once

// SFML Headers
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h> 

#include "OptionsLoader.h"

class Game
{
public:
	Game();
	~Game();

	void init();
	void update();
	void draw(sf::RenderWindow &window);


	void backScreen(OptionsLoader *options, int screen);

private:
	sf::Vector2f screenSize = sf::Vector2f(1920, 1080);

	sf::Font font;
	sf::Text text;
};

