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
#include "CollisionManager.h"

#include "Camera.h"
#include "Player.h"
#include "Human.h"
#include "Terrain.h"
#include "Obstacles.h"
#include "Nest.h"
#include "Abductor.h"

class Game
{
private:
	GlobalVariables* myGlobalOptions = GlobalVariables::getInstance();
	InputManager* inputManager = InputManager::getInstance();
	CollisionManager* collisionManager = new CollisionManager();

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

	
	sf::Sprite backgroundSprite;

	void teleport();

	int currentLevel = 1;

	void MeteorSpawn();
	sf::Clock meteorSpawnClock;
	float meteorSpwanTimer;
	float meteorSpawnDelay;

	void clearVectors();
	void nextLevel();
	void gameOver();

protected:
	Camera* camera;
	Player* player;
	Terrain* terrain;

	std::vector<Human*> humans;
	std::vector<Obstacles*> meteors;
	std::vector<Abductor*> abductors;
	std::vector<Nest*> nests;

	std::vector<Obstacles*> meteorsToDelete;
	std::vector<Abductor*> abductorsToDelete;
	std::vector<Nest*> nestsToDelete;
};

