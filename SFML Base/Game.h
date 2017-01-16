#pragma once

// SFML Headers
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h> 

#include "GlobalVariables.h"
#include "InputManager.h"

#include "Camera.h"
#include "Player.h"
#include "Human.h"
#include "Terrain.h"
#include "Obstacles.h"

class Game
{
private:
	GlobalVariables* myGlobalOptions = GlobalVariables::getInstance();
	InputManager* inputManager = InputManager::getInstance();

public:
	Game(Camera* camera);
	~Game();

	void init();
	void update();
	void draw(sf::RenderWindow &window);
	void input(sf::Event Event);

private:
	sf::Vector2f screenSize = myGlobalOptions->screenSize;

	void goToScene(int screen);

	void controller(sf::Event Event);

	sf::Font font;
	sf::Text text;

	sf::Texture playershipTexture, backgroundTexture, bulletTexture, humanTexture, obstacleTexture;
	sf::Sprite backgroundSprite;

	void teleport();

	int currentLevel = 1;

	void MeteorSpawn();
	sf::Clock meteorSpawnClock;
	float meteorSpwanTimer;
	float meteorSpawnDelay;

protected:
	Camera* camera;
	Player* player;
	Terrain* terrain;

	std::vector<Human*> humans;
	std::vector<Obstacles*> meteors;
};

