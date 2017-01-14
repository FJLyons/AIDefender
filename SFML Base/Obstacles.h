#pragma once
#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "SFML\Graphics.hpp"

#include "GlobalVariables.h"

class Obstacles
{
public:
	GlobalVariables* myGlobalOptions = GlobalVariables::getInstance();

	Obstacles(sf::Texture& tex);
	~Obstacles();

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;

	sf::Vector2f mPositon;

	sf::Vector2f maxVelocity;
	sf::Vector2f velocity;
	sf::Vector2f direction;


	sf::Vector2f mScale;

public:
	void Update();
	void Draw(sf::RenderWindow &window);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);
};

#endif
