#pragma once
#pragma once
#ifndef HUMAN_H
#define HUMAN_H

#include "SFML\Graphics.hpp"


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
	void Draw(sf::RenderWindow &window);

};

#endif
