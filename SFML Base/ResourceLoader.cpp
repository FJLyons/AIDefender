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

		// Sounds
		if (!bufferMenuMove.loadFromFile("assets/audio/Blip_Move.ogg")) {}
		menuMove.setBuffer(bufferMenuMove);

		if (!bufferMenuSelect.loadFromFile("assets/audio/Blip_Select.ogg")) {}
		menuSelect.setBuffer(bufferMenuSelect);

		if (!bufferExplosion.loadFromFile("assets/audio/Explosion.ogg")) {}
		explosion.setBuffer(bufferExplosion);

		if (!bufferHit.loadFromFile("assets/audio/Hit_Hurt.ogg")) {}
		hit.setBuffer(bufferHit);

		if (!bufferShoot.loadFromFile("assets/audio/Laser_Shoot.ogg")) {}
		shoot.setBuffer(bufferShoot);

		if (!bufferLevelUp.loadFromFile("assets/audio/Levelup.ogg")) {}
		levelUp.setBuffer(bufferLevelUp);

		if (!musicMenu.openFromFile("assets/audio/THEME OF TATA.ogg")) {}
		if (!musicGame.openFromFile("assets/audio/RED ALERT.ogg")) {}
		
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






