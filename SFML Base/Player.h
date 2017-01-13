#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "SFML\Graphics.hpp"
#include "InputManager.h"
#include "Bullet.h"

class Player
{


private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPositon;
	sf::Vector2f maxVelocity;
	sf::Vector2f velocity;
	sf::Vector2f mScale;

	std::vector<Bullet*> bulletList;
	bool playerFacingRight;
	bool playerFacingUp;
	bool canShoot;

	float flipSpeed;
	float shotdelay;
	float shotTimer;

	sf::Clock shotClock;

public:
	Player();
	Player(sf::Texture& tex,sf::Vector2f pos,sf::Vector2f maxVel);
	void MoveUp(bool pressed);
	void MoveDown(bool pressed);
	void MoveLeft(bool pressed);
	void MoveRight(bool pressed);
	void Shoot(sf::Texture& tex);
	void Update();
	void Draw(sf::RenderWindow &window);
	void Flip();

	sf::Vector2f getPosition();

	void teleport();


};

#endif
