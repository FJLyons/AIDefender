#include "InputManager.h"

InputManager* InputManager::inputManagerInstance = nullptr;

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

InputManager * InputManager::getInstance()
{
	if (inputManagerInstance == nullptr)
	{
		inputManagerInstance = new InputManager();
	}
	return inputManagerInstance;
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
		previousKey = key;
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
			previousKeys.push_back(keys[i]);
		}
	}
	previousKeys.empty();
	return false;
}

bool InputManager::KeyReleased(sf::Keyboard::Key key)
{
	if (Event.type == sf::Event::KeyReleased && Event.key.code == key)
	{
		return true;
		previousKey = sf::Keyboard::Key::Unknown;
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
			previousKeys.empty();
		}
	}
	return false;
}

bool InputManager::KeyHold(sf::RenderWindow &window, sf::Keyboard::Key key)
{
	if (previousKey == key)
	{
		if (Event.type == sf::Event::KeyPressed && Event.key.code == key)
		{
			return true;
			previousKey = key;
		}
	}
	return false;
}

bool InputManager::KeyHold(sf::RenderWindow &window, std::vector<sf::Keyboard::Key> keys)
{
	if (previousKeys == keys)
	{
		for (int i = 0; i < keys.size(); i++)
		{
			if (Event.key.code == keys[i])
			{
				return true;
				previousKeys.push_back(keys[i]);
			}
		}
	}
	previousKeys.empty();
	return false;
}
