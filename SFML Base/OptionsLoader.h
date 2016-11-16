#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <iostream>

class OptionsLoader
{
public:
	OptionsLoader();
	~OptionsLoader();

	void init();
	void update();
	void draw(sf::RenderWindow &window);

	int getCurrentScreen();
	void setCurrentScreen(int current);

	enum GameStates { CONTINUE, GAME, LOAD, OPTIONS, INSTRUCTIONS, PAUSE, GAMEOVER, MAINMENU, SPLASH };

private:
	sf::Vector2f screenSize = sf::Vector2f(1920, 1080);

	int currentScreen;
};

