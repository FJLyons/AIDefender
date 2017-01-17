#pragma once
#ifndef ABDUCTOR_H
#define ABDUCTOR_H

#include "SFML\Graphics.hpp"
#include "GlobalVariables.h"
#include "CollisionManager.h"

#include <time.h>

#include "Bullet.h"
#include "ResourceLoader.h"

class Abductor
{
private:
	GlobalVariables* myGlobalOptions = GlobalVariables::getInstance();

private:
	sf::Texture mTexture;
	sf::Texture bulletTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPositon;
	sf::Vector2f velocity;
	int currentBehaviour;
	float range;
	bool canShoot;


	sf::Vector2f Direction;
	float shotdelay;
	float shotTimer;
	sf::Clock shotClock;
	sf::Vector2f seekPoint;
	sf::RectangleShape collisionRect;
	sf::RectangleShape FeildofView;
	enum Behaviour { Wander,Flock,Abduct };
	int neighbourRange;
	sf::Vector2f alignment;
	sf::Vector2f cohesion;
	sf::Vector2f seperation;
	int neighbourcount;
	int myIndex;
	bool leader;

public:
	Abductor(sf::Vector2f pos, bool lead);
	~Abductor();

	sf::Vector2f FindNewPoint();
	void Wandering(std::vector<Abductor*>& abductors);
	sf::Vector2f ComputeAlignment(std::vector<Abductor*>& abductors);
	sf::Vector2f ComputeCohesion(std::vector<Abductor*>& abductors);
	sf::Vector2f ComputeSeperation(std::vector<Abductor*>& abductors);
	void Flocking();
	void Abducting();
	void Update(std::vector<Abductor*>& abductors, int indexofCurrentAbductor);
	void Draw(sf::RenderWindow &window);
	sf::Vector2f getVelocity();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f);
	sf::RectangleShape getRect();
	sf::RectangleShape getFOVRect();
	sf::Vector2f getseekPoint();
	void  setseekPoint(sf::Vector2f point);
	bool getLeader();


	int health = 1;
};

#endif
