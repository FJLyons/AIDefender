#include "Player.h"
#include <iostream>

Player::Player()
{

}

Player::Player(sf::Texture& tex, sf::Vector2f pos, sf::Vector2f maxVel)
{
	mTexture = tex;
	mPositon = pos;
	maxVelocity = maxVel;

	mSprite.setTexture(mTexture);
	mSprite.setPosition(mPositon);
	mSprite.setOrigin(sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2));
	mScale = sf::Vector2f(1.f, 1.f);

	flipSpeed = 0.15f;
	playerFacingRight = true;
	canShoot = true;
	shotTimer = 0;
	shotdelay = 0.3;
	
}

void Player::Update()
{
	shotTimer += shotClock.getElapsedTime().asSeconds();
	sf::Time dt = shotClock.restart();

	if (shotTimer > shotdelay)
	{
		canShoot = true;
	}
	else
	{
		canShoot = false;
	}

	Flip();

	mSprite.setScale(mScale);
	mPositon += velocity;
	mSprite.setPosition(mPositon);


	for (int i = 0; i< bulletList.size(); i++)
	{
		if (bulletList[i]->Update() == false)
		{
			bulletList.erase(bulletList.begin() + i);
		}
	}
}

void Player::Draw(sf::RenderWindow &window)
{
	window.draw(mSprite);

	for (int i = 0; i < bulletList.size(); i++)
	{
		bulletList[i]->Draw(window);
	}

}


void Player::MoveUp(bool pressed)
{
	if (pressed == true)
	{
		if (velocity.y > -maxVelocity.y)
		{
			velocity.y = -20.5;
			playerFacingUp = true;
		}
	}
	else
	{
		velocity.y = 0;
		/*if (velocity.y < 0)
		{
			velocity.y += 2.5;
		}*/
	}
}
void Player::MoveDown(bool pressed)
{
	if (pressed == true)
	{
		if (velocity.y < maxVelocity.y)
		{
			playerFacingUp = false;
			velocity.y = 20.5;
		}
	}
	else
	{
		velocity.y = 0;
	/*	if (velocity.y > 0)
		{
			velocity.y -= 2.5;
		}*/
	}
}
void Player::MoveLeft(bool pressed)
{
	if (pressed == true)
	{
		if (velocity.x > -maxVelocity.x)
		{
			velocity.x -= 1.5;
			playerFacingRight = false;
		}
	}
	else
	{
		if (velocity.x < 0)
		{
			velocity.x += 1.5;
		}
	}
}
void Player::MoveRight(bool pressed)

{
	if (pressed == true)
	{
		if (velocity.x < maxVelocity.x)
		{
			velocity.x += 1.5;
			playerFacingRight = true;

		}
	}
	else
	{
		if (velocity.x > 0)
		{
			velocity.x -= 1.5;
		}
	}
}
void Player::Shoot(sf::Texture& tex)
{	
	if (canShoot == true)
	{
		bulletList.push_back(new Bullet(mPositon, tex, playerFacingRight, velocity));
		shotTimer = 0;
	}
	
}

void Player::Flip()
{

	if (playerFacingRight == false)
	{
		if (mScale.x > -1)
			mScale.x -= flipSpeed;
	}
	else if (playerFacingRight == true)
	{
		if (mScale.x < 1)
			mScale.x += flipSpeed;
	}



	/*if (playerFacingUp == true)
	{
		if (mScale.y > -1)
			mScale.y -= flipSpeed;
	}
	else if (playerFacingUp == false)
	{
		if (mScale.y < 1)
			mScale.y += flipSpeed;
	}*/

}

sf::Vector2f Player::getPosition()
{
	return mPositon;
}