#pragma once
#ifndef HUMAN_H
#define HUMAN_H

#include "SFML\Graphics.hpp"
#include "ResourceLoader.h"
#include "GlobalVariables.h"

class Human
{

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPositon;
	sf::Vector2f velocity;
	sf::Vertex* targetPoints;
	sf::RectangleShape collisionRect;
	int currentPoint;

public:
	GlobalVariables* myGlobalOptions = GlobalVariables::getInstance();

	Human();
	Human( sf::Vertex* points);
	
	void Update();
	void Draw(sf::RenderWindow &window, bool mini);

	int getPoint();
	void setPoint(int index);

	sf::RectangleShape getRect();
};

#endif
