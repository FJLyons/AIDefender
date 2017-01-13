#pragma once
#ifndef NEST_H
#define NEST_H

#include "SFML\Graphics.hpp"


class Nest
{


private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPositon;
	sf::Vector2f velocity;
	int maxNoOfMinions;
	int NoOfMinions;
	int currentBehaviour;
	enum Behaviour { Wander, Evade };
	

public:
	Nest();
	Nest(sf::Texture& tex, sf::Vector2f pos );



	
	void Wandering();
	void Evading();
	void Update();
	void Draw(sf::RenderWindow &window);

};

#endif
