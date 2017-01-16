#ifndef BULLET_H
#define BULLET_H

#include "SFML\Graphics.hpp"


class Bullet
{


private:

	//sf::Vector2f mPositon;
	//sf::Vector2f mVelocity;
	//sf::Texture mTexture;
	//sf::Sprite mSprite;

	//bool mfacingRight;
	//bool alive;

	//float ttl = 3;

	//sf::Clock deltaClock;
public:

	sf::Vector2f mPositon;
	sf::Vector2f mVelocity;
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::RectangleShape collisionRect;
	bool mfacingRight;
	bool alive;
	float ttl = 3;
	sf::Clock deltaClock;

	Bullet();
	Bullet(sf::Vector2f pos, sf::Texture& tex, bool facingRight, sf::Vector2f playerVelocity);
	bool Update();
	void Draw(sf::RenderWindow &window);
	sf::Sprite getSprite();


};

#endif