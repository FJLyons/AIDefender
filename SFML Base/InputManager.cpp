#include "InputManager.h"



InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

//Gnereate events
void InputManager::update(sf::Event evn)
{
	Event = evn;
}

bool InputManager::KeyPressed(sf::Keyboard::Key key)
{
	if (Event.type == sf::Event::KeyPressed && Event.key.code == key)
	{
		return true;
	}
	return false;
}

bool InputManager::KeyPressed(std::vector<sf::Keyboard::Key> keys)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (Event.type == sf::Event::KeyPressed && Event.key.code == keys[i])
		{
			return true;
		}
	}
	return false;
}

bool InputManager::KeyReleased(sf::Keyboard::Key key)
{
	if (Event.type == sf::Event::KeyReleased && Event.key.code == key)
	{
		return true;
	}
	return false;
}

bool InputManager::KeyReleased(std::vector<sf::Keyboard::Key> keys)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (Event.type == sf::Event::KeyReleased && Event.key.code == keys[i])
		{
			return true;
		}
	}
	return false;
}

bool InputManager::KeyHold(sf::RenderWindow &window, sf::Keyboard::Key key)
{
	while (window.pollEvent(Event))
	{
		if (Event.key.code == key)
		{
			return true;
		}
	}
	return false;
}

bool InputManager::KeyHold(sf::RenderWindow &window, std::vector<sf::Keyboard::Key> keys)
{
	while (window.pollEvent(Event))
	{
		for (int i = 0; i < keys.size(); i++)
		{
			if (Event.key.code == keys[i])
			{
				return true;
			}
		}
	}
	return false;
}
