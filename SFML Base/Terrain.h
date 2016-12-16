#pragma once

// SFML Headers
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h> 

#define MAP_WIDTH  128

class Terrain
{
public:
	Terrain();
	~Terrain();

	void init();
	void update();
	void draw(sf::RenderWindow &window);
	sf::Vertex* getPoints();
	//sf::Vector2f pointsOnMap[100]

	

private:
	sf::Vertex* pointsOnMap;
	

};

