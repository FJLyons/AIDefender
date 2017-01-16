#include "ResourceLoader.h"


ResourceLoader *ResourceLoader::_instance = 0;

ResourceLoader::ResourceLoader()
{
		playershipTexture.loadFromFile("assets/player/PlayerShip.png");
		playershipTexture.setSmooth(true);
		nestTexture.loadFromFile("assets/enemies/nest.png");
		nestTexture.setSmooth(true);
		interceptorTexture.loadFromFile("assets/enemies/interceptor.png");
		interceptorTexture.setSmooth(true);
		humanTexture.loadFromFile("assets/ai/human.png");
		humanTexture.setSmooth(true);
		backgroundTexture.loadFromFile("assets/background/background.png");
		bulletTexture.loadFromFile("assets/player/bullet.png");
		abductorTexture.loadFromFile("assets/enemies/abductor.png");
		obstacleTexture.loadFromFile("assets/obstacles/meteor.png");
		obstacleTexture.setSmooth(true);
}

ResourceLoader::~ResourceLoader()
{
	delete _instance;
}

/**Singleton instance*/
ResourceLoader* ResourceLoader::instance()
{
	if (_instance == nullptr)
	{//if our instance hasn't been initialized
	 //initialize it
		_instance = new ResourceLoader();
	}
	//return the instance.
	return _instance;
}

sf::Texture&  ResourceLoader::getplayershipTexture()
{
	return playershipTexture;
}

sf::Texture& ResourceLoader::getbackgroundTexture()
{
	return backgroundTexture;
}

sf::Texture& ResourceLoader::getbulletTexture()
{
	return bulletTexture;
}

sf::Texture& ResourceLoader::gethumanTexture()
{
	return humanTexture;
}

sf::Texture& ResourceLoader::getnestTexture()
{
	return nestTexture;
}

sf::Texture& ResourceLoader::getinterceptorTexture()
{
	return interceptorTexture;
}

sf::Texture& ResourceLoader::getabductorTexture()
{
	return abductorTexture;
}

sf::Texture & ResourceLoader::getobstacleTexture()
{
	return obstacleTexture;
}






