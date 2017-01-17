#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "SFML\Graphics.hpp"

#include "GlobalVariables.h"
#include "InputManager.h"

#include "Bullet.h"
#include "ResourceLoader.h"


class Player
{

private:
	GlobalVariables* myGlobalOptions = GlobalVariables::getInstance();

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPositon;
	sf::Vector2f maxVelocity;
	sf::Vector2f velocity;
	sf::Vector2f mScale;
	sf::RectangleShape collisionRect;
	std::vector<Bullet*> bulletList;
	bool playerFacingRight;
	bool canShoot;

	float flipSpeed;
	float shotdelay;
	float shotTimer;
	sf::Clock shotClock;

public:
	Player();
	Player(sf::Vector2f pos,sf::Vector2f maxVel);

	void FaceLeft();
	void FaceRight();

	void MoveUp(bool pressed);
	void MoveDown(bool pressed);
	void MoveLeft();
	void MoveRight();

	void Decelerate();

	void Shoot();

	void Update();
	void Draw(sf::RenderWindow &window);
	void Flip();

	sf::Vector2f getPosition();
	sf::RectangleShape getRect();
	bool teleport();
	bool teleportLeft = true;

	std::vector<Bullet*> getBullets();

	void deleteBullet(int index);

	int health = 1;
};

#endif
