#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <iostream>

#include "OptionsLoader.h"

#define MAX_INDEX 5

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void init();
	void update();
	void draw(sf::RenderWindow &window);

	void swapScreen(OptionsLoader *options);
	void backScreen(OptionsLoader *options, int screen);

	void moveUp();
	void moveDown();

	int getPressedItem();

	void exitGame(sf::RenderWindow &window);

private:
	sf::Vector2f screenSize = sf::Vector2f(1920, 1080);

	// Art
	sf::Texture logoTexture;
	sf::Sprite logoSprite;
	sf::Vector2f scaleFactor; // Resolution vs Screen

	// Index
	int selectedItemIndex;

	// Font
	sf::Font font;
	sf::Text text[MAX_INDEX];

};
