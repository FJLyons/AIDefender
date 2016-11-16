#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <iostream>
#include <conio.h>
#include <windows.h>

#include "OptionsLoader.h"

class SplashScreen
{
public:
	SplashScreen();
	~SplashScreen();

	void init();
	void update();
	void draw(sf::RenderWindow &window);

	void swapScreen(OptionsLoader *options);

	void print(const std::string &str, int delay_time);
	void fade();
	

private:
	sf::Vector2f screenSize = sf::Vector2f(1920, 1080);

	// Art
	sf::Texture logoTexture;
	sf::Sprite logoSprite;

	// Font
	sf::Font font;
	sf::Text text;

	// Variables
	int alphaFade; // Fade Image Alpha
	float fadeMultiply; // Increase fade speed
	sf::Vector2f scaleFactor; // Resolution vs Screen

	sf::Clock clock;
	std::string pressAny;
	int currentLetter;
	bool printed;

	int textFade;
	bool fading;
};

