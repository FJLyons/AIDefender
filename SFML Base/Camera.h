#pragma once
#include "SFML/Graphics.hpp"  
#include "SFML/OpenGL.hpp" 
#include <iostream> 

#include "GlobalVariables.h"
#include "Player.h"


class Camera
{
public:
	Camera();
	~Camera();

	void init();
	void update(Player *player);
	void draw(sf::RenderWindow &window);

	sf::View getView();
	void setViewCenter(sf::Vector2f *position);

	void resetView();

	// View
	sf::View	view;

private:
	sf::Vector2f screenSize = sf::Vector2f(1920, 1080);
	sf::Vector2f screenCenter = sf::Vector2f(screenSize.x / 2, screenSize.y / 2);

	GlobalVariables* myGlobalOptions = GlobalVariables::getInstance();
};

