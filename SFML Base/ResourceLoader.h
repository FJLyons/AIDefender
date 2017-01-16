#pragma once
#define SDL_MAIN_HANDLED
#ifdef __APPLE__

#elif defined(_WIN64) || defined(_WIN32)

#endif

#include "SFML\Graphics.hpp"
class ResourceLoader
{
public:
	ResourceLoader();
	~ResourceLoader();

	static ResourceLoader* instance();
	sf::Texture& getplayershipTexture();
	sf::Texture& getbackgroundTexture();
	sf::Texture& getbulletTexture();
	sf::Texture& gethumanTexture();
	sf::Texture& getnestTexture();
	sf::Texture& getinterceptorTexture();
	sf::Texture& getabductorTexture();
	sf::Texture& getobstacleTexture();

private:
	static ResourceLoader* _instance;
	sf::Texture playershipTexture, backgroundTexture, bulletTexture, humanTexture, nestTexture, interceptorTexture, abductorTexture, obstacleTexture;
};