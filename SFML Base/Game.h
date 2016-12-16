#pragma once

// SFML Headers
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h> 

#include "OptionsLoader.h"
#include "InputManager.h"
#include "Player.h"
#include "Terrain.h"
#include "Human.h"

class Game
{
public:
	Game(InputManager* im);
	~Game();

	void init();
	void update();
	void draw(sf::RenderWindow &window);

	void input(sf::Event Event);

	void backScreen(OptionsLoader *options, int screen);

private:
	sf::Vector2f screenSize = sf::Vector2f(1920, 1080);

	Player *player1;
	Human *human1;
	sf::Texture playershipTexture, backgroundTexture, bulletTexture,humanTexture;
	sf::Sprite backgroundSprite;

	sf::Font font;
	sf::Text text;
	sf::Event *eve;
	InputManager* inputManager;
	void controller(sf::Event Event);

protected:
	Terrain* terrain;
};

