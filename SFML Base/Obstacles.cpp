#include "Obstacles.h"

Obstacles::Obstacles(sf::Texture& tex)
{
	mTexture = tex;
	mPositon = sf::Vector2f(rand() % MAP_WIDTH_PIXEL, -540);

	maxVelocity = sf::Vector2f(10, 20);

	mTexture.setSmooth(true);

	mSprite.setTexture(mTexture);
	mSprite.setPosition(mPositon);
	mSprite.setOrigin(sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2));
	mScale = sf::Vector2f(1.f, 1.f);

	direction = sf::Vector2f((rand() % 11 - 5), 5);
}


Obstacles::~Obstacles()
{
}

void Obstacles::Update()
{
	mPositon += direction;
	mSprite.setPosition(mPositon);

	// Teleport right
	if (mPositon.x > FULL_WIDTH_PIXEL)
	{
		mPositon.x = HALF_SCREEN_WIDTH_PIXEL * 3;
	}

	// teleport left
	if (mPositon.x < 0 - HALF_SCREEN_WIDTH_PIXEL)
	{
		mPositon.x = FULL_WIDTH_PIXEL - SCREEN_WIDTH_PIXEL;
	}


	mSprite.rotate(direction.x);
}

void Obstacles::Draw(sf::RenderWindow &window)
{
	window.draw(mSprite);
}

sf::Vector2f Obstacles::getPosition()
{
	return mPositon;
}

void Obstacles::setPosition(sf::Vector2f position)
{
	mPositon = position;
}