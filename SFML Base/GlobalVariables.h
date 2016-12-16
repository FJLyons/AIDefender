#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <iostream>

class GlobalVariables
{
public:
	static GlobalVariables * getInstance();
private:
	static GlobalVariables * globalVariablesInstance;

public:
	GlobalVariables();
	~GlobalVariables();

	void init();
	void update();
	void draw(sf::RenderWindow &window);

	int getCurrentScene();
	void setCurrentScene(int current);

	enum GameStates {
		CONTINUE,
		GAME,
		LOAD,
		OPTIONS,
		INSTRUCTIONS,
		PAUSE,
		GAMEOVER,
		MAINMENU,
		SPLASH
	};

	sf::Vector2f screenSize = sf::Vector2f(1920, 1080);
	sf::RenderWindow* windowReference;

private:

	int currentScene;
};