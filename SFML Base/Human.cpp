#include "Human.h"

Human::Human()
{

}

Human::Human(sf::Texture& tex, sf::Vertex* points)
{
	targetPoints = points;
	currentPoint = HALF_SCREEN_WIDTH + 1;

	mTexture = tex;
	mPositon = points[HALF_SCREEN_WIDTH].position;
	velocity = sf::Vector2f(1, 1);	

	mTexture.setSmooth(true);

	mSprite.setTexture(mTexture);
	mSprite.setPosition(mPositon);
	mSprite.setOrigin(sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2));
	 
}

void Human::Update()
{
	sf::Vector2f Direction = targetPoints[currentPoint].position -mPositon;
	float length = sqrt((Direction.x * Direction.x) + (Direction.y * Direction.y));
	Direction = Direction / length;

	mPositon += sf::Vector2f(Direction.x * velocity.x, Direction.y * velocity.y);
	mSprite.setPosition(sf::Vector2f(mPositon.x,mPositon.y - mSprite.getLocalBounds().height/2));

	if (mPositon.x >= targetPoints[currentPoint].position.x)
	{
		currentPoint++;
	}

	// Teleport right
	if (currentPoint > MAP_WIDTH)
	{
		mPositon = targetPoints[HALF_SCREEN_WIDTH].position;
		currentPoint = HALF_SCREEN_WIDTH + 1;
	}

	// teleport left
	if (currentPoint < 0)
	{
		mPositon = targetPoints[MAP_WIDTH - HALF_SCREEN_WIDTH].position;
		currentPoint = MAP_WIDTH - HALF_SCREEN_WIDTH - 1;
	}
}

void Human::Draw(sf::RenderWindow &window, bool mini)
{
	if (mini == false)
	{
		mSprite.setScale(sf::Vector2f(1, 1));
		window.draw(mSprite);
	}

	if (mini == true)
	{
		mSprite.setScale(sf::Vector2f(4, 4));
		window.draw(mSprite);
	}
}

void Human::setPoint(int index)
{
	mPositon = targetPoints[index].position;
}