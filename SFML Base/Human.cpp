#include "Human.h"

Human::Human()
{

}

Human::Human(sf::Texture& tex, sf::Vertex* points)
{
	targetPoints = points;
	currentPoint = 1;
	mTexture = tex;
	mPositon = points[0].position;
	velocity = sf::Vector2f(1, 1);
	

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

	if (mPositon.x > targetPoints[currentPoint].position.x)
	{
		currentPoint++;
	}
}

void Human::Draw(sf::RenderWindow &window)
{
	window.draw(mSprite);



}
