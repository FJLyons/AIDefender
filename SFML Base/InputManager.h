// SFML Headers
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include<vector>

#pragma once
class InputManager
{
public:
	InputManager();
	~InputManager();

	void update(sf::Event event);

	bool KeyPressed(sf::Keyboard::Key key);
	bool KeyPressed(std::vector<sf::Keyboard::Key> keys);

	bool KeyReleased(sf::Keyboard::Key key);
	bool KeyReleased(std::vector<sf::Keyboard::Key> keys);

	bool KeyHold(sf::RenderWindow &window, sf::Keyboard::Key key);
	bool KeyHold(sf::RenderWindow &window, std::vector<sf::Keyboard::Key> keys);

private:

	sf::Event Event;
};

