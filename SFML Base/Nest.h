#pragma once
#ifndef NEST_H
#define NEST_H

#include "SFML\Graphics.hpp"
#include "GlobalVariables.h"
#include "CollisionManager.h"
#include <time.h>
#include "InterceptorMissile.h"
#include "Bullet.h"
#include "Abductor.h"
#include "ResourceLoader.h"
#include <iostream>
class Nest
{

private:
	GlobalVariables* myGlobalOptions = GlobalVariables::getInstance();

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPositon;
	sf::Vector2f velocity;
	sf::Vector2f playerPosition;
	int maxNoOfMinions;
	int NoOfMinions;
	int currentBehaviour;
	float range;
	sf::RectangleShape collisionRect;
	sf::Vector2f seekPoint;
	std::vector<InterceptorMissile*> missileList;
	bool canShoot;
	float shotdelay;
	float shotTimer;
	sf::Clock shotClock;

	float spawnDelay;
	float spawnTimer;
	sf::Clock spawnClock;

	//sf::Vector2f seekPoint;
	enum Behaviour { Wander, Evade };
	

public:
	Nest( sf::Vector2f pos);
	~Nest();

	sf::Vector2f FindNewPoint();
	void Wandering();
	void Evading();
	void Update(sf::RectangleShape  player, std::vector<Abductor*> &abductors);
	void Draw(sf::RenderWindow &window);
	void SpawnAbductors( std::vector<Abductor*> &abductors);
	//void calculateDrift();

	sf::RectangleShape getRect();
	int health = 2;
};

#endif
