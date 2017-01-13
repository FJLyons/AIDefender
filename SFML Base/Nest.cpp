#include "Nest.h"

Nest::Nest()
{
}

Nest::Nest(sf::Texture & tex, sf::Vector2f pos)
{
	mTexture = tex;
	mPositon = pos;
	velocity = sf::Vector2f(10, 0);

	mSprite.setTexture(mTexture);
	mSprite.setPosition(mPositon);
	mSprite.setOrigin(sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2));

	currentBehaviour = Behaviour::Wander;

}

void Nest::Wandering()
{
}

void Nest::Evading()
{
}

void Nest::Update()
{
	if (currentBehaviour == Behaviour::Wander)
	{
		Wandering();
	}
	else if (currentBehaviour == Behaviour::Evade)
	{
		Evading();
	}
}

void Nest::Draw(sf::RenderWindow & window)
{
	window.draw(mSprite);

}
