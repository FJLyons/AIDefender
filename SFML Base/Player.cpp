#include "Player.h"
#include <iostream>

Player::Player()
{

}

Player::Player(sf::Vector2f pos, sf::Vector2f maxVel)
{
	mTexture = ResourceLoader::instance()->getplayershipTexture();
	mPositon = pos;
	maxVelocity = maxVel;

	mTexture.setSmooth(true);

	mSprite.setTexture(mTexture);
	mSprite.setPosition(mPositon);
	mSprite.setOrigin(sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2));
	mScale = sf::Vector2f(1.f, 1.f);

	flipSpeed = 0.15f;
	playerFacingRight = true;
	canShoot = true;
	shotTimer = 0;
	shotdelay = 0.3;

	collisionRect.setOrigin(mSprite.getGlobalBounds().width / 2, mSprite.getGlobalBounds().height / 2);
	collisionRect.setSize(sf::Vector2f(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height));
	collisionRect.setOutlineColor(sf::Color::Red);
	collisionRect.setFillColor(sf::Color::Transparent);
	collisionRect.setOutlineThickness(2);
	collisionRect.setPosition(mPositon);

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

	if (abs(velocity.x) <= 1) { velocity.x = 0; }

	// Flip
	if (velocity.x > 0) { FaceRight(); }
	if (velocity.x < 0) { FaceLeft(); }

	for (int i = 0; i< bulletList.size(); i++)
	{
		if (bulletList[i]->Update() == false)
		{
			bulletList.erase(bulletList.begin() + i);
		}
	}

	// Top and Bottom wall collision
	if (mPositon.y <= 0)
	{
		velocity.y = 0;
		mPositon.y = 0;
	}

	if (mPositon.y >= 1080)
	{
		velocity.y = 0;
		mPositon.y = 1080;
	}

	collisionRect.setPosition(mPositon);
}

void Player::Draw(sf::RenderWindow &window)
{
	window.draw(mSprite);

	if (myGlobalOptions->drawCollisionBox)
	{
		window.draw(collisionRect);
	}

	for (int i = 0; i < bulletList.size(); i++)
	{
		bulletList[i]->Draw(window);
	}
}

void Player::FaceLeft()
{
	if (playerFacingRight != false)
	{
		velocity.x = 0;
		playerFacingRight = false;
	}
}

void Player::FaceRight()
{
	if (playerFacingRight != true)
	{
		velocity.x = 0;
		playerFacingRight = true;
	}
}

void Player::MoveUp(bool pressed)
{
	if (pressed == true)
	{
		if (velocity.y > -maxVelocity.y)
		{
			velocity.y = -20.5f;
		}
	}
	else
	{
		velocity.y = 0;
	}
}
void Player::MoveDown(bool pressed)
{
	if (pressed == true)
	{
		if (velocity.y < maxVelocity.y)
		{
			velocity.y = 20.5f;
		}
	}
	else
	{
		velocity.y = 0;
	}
}
void Player::MoveLeft()
{
	if (velocity.x > -maxVelocity.x)
	{
		velocity.x -= 1.5f - (velocity.x / 10);
	}
	else
	{
		velocity.x = -maxVelocity.x;
	}
}
void Player::MoveRight()
{
	if (velocity.x < maxVelocity.x)
	{
		velocity.x += 1.5f + (velocity.x / 10);
	}
	else
	{
		velocity.x = maxVelocity.x;
	}
}

void Player::Shoot()
{
	if (canShoot == true)
	{
		bulletList.push_back(new Bullet(mPositon, ResourceLoader::instance()->getbulletTexture(), playerFacingRight, velocity));
		shotTimer = 0;
	}
}

void Player::Flip()
{
	if (playerFacingRight == false)
	{
		if (mScale.x > -1)
		{
			mScale.x -= flipSpeed;
		}
	}
	else if (playerFacingRight == true)
	{
		if (mScale.x < 1)
		{
			mScale.x += flipSpeed;
		}
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

sf::Vector2f Player::getVelocity()
{
	return velocity;
}

sf::Vector2f Player::getPosition()
{
	return mPositon;
}
sf::RectangleShape Player::getRect()
{
	return collisionRect;
}

bool Player::teleport()
{
	// Wrap around teleport
	if (mPositon.x < 0)
	{
		mPositon.x = 1920 * 9;
		teleportLeft = true;
		return true;
	}

	else if (mPositon.x > 1920 * 9)
	{
		mPositon.x = 0;
		teleportLeft = false;
		return true;
	}

	else
	{
		return false;
	}
}


void Player::Decelerate()
{
	if (velocity.x != 0) { velocity.x *= 0.9f; }
}

std::vector<Bullet*> Player::getBullets()
{
	return bulletList;
}

void Player::deleteBullet(int index)
{
	bulletList.erase(bulletList.begin() + index);
	bulletList.shrink_to_fit();
}