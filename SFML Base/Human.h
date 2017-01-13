#pragma once
#pragma once
#ifndef HUMAN_H
#define HUMAN_H

#include "SFML\Graphics.hpp"

#define MAP_WIDTH  192 * 10
#define HALF_SCREEN_WIDTH 192 / 2

class Human
{


private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPositon;
	sf::Vector2f velocity;
	sf::Vertex* targetPoints;
	int currentPoint;

public:
	Human();
	Human(sf::Texture& tex, sf::Vertex* points);
	
	void Update();
	void Draw(sf::RenderWindow &window, bool mini);

	void setPoint(int index);
};

#endif
