#include "SceneManager.h"

SceneManager::SceneManager()
{
	init();
}

SceneManager::~SceneManager()
{
}

void SceneManager::init()
{
	optionsLoader = new OptionsLoader();
	inputManager = new InputManager();

	splashScreen = new SplashScreen();
	mainMenu = new MainMenu();
	game = new Game(inputManager);
	load = new LoadScreen();
	optionsMenu = new OptionsMenu();
	instructions = new InstructionsScreen();
}

void SceneManager::update()
{
	if (optionsLoader->getCurrentScreen() == optionsLoader->SPLASH){ splashScreen->update(); }
	else if (optionsLoader->getCurrentScreen() == optionsLoader->MAINMENU){ mainMenu->update(); }
	else if (optionsLoader->getCurrentScreen() == optionsLoader->GAME){ game->update(); }
	else if (optionsLoader->getCurrentScreen() == optionsLoader->LOAD) { load->update(); }
	else if (optionsLoader->getCurrentScreen() == optionsLoader->OPTIONS){ optionsMenu->update(); }
	else if (optionsLoader->getCurrentScreen() == optionsLoader->INSTRUCTIONS) { instructions->update(); }
}

void SceneManager::draw(sf::RenderWindow &window)
{
	if (optionsLoader->getCurrentScreen() == optionsLoader->SPLASH){ splashScreen->draw(window); }
	else if (optionsLoader->getCurrentScreen() == optionsLoader->MAINMENU){ mainMenu->draw(window); }
	else if (optionsLoader->getCurrentScreen() == optionsLoader->GAME){ game->draw(window); }
	else if (optionsLoader->getCurrentScreen() == optionsLoader->LOAD) { load->draw(window); }
	else if (optionsLoader->getCurrentScreen() == optionsLoader->OPTIONS){ optionsMenu->draw(window); }
	else if (optionsLoader->getCurrentScreen() == optionsLoader->INSTRUCTIONS) { instructions->draw(window); }
}

void SceneManager::input(sf::RenderWindow &window, sf::Event &Event)
{
	inputManager->update(Event);
	swapScenes(window, Event);
}

void SceneManager::swapScenes(sf::RenderWindow &window, sf::Event &Event)
{
	if (optionsLoader->getCurrentScreen() == optionsLoader->SPLASH) // Splash
	{
		if (Event.type == sf::Event::KeyPressed)
		{
			splashScreen->swapScreen(optionsLoader);
		}
	}

	else if (optionsLoader->getCurrentScreen() == optionsLoader->MAINMENU) // Main Menu
	{
		// Main menu movement
		if (inputManager->KeyPressed(sf::Keyboard::Up)) { mainMenu->moveUp(); }
		else if (inputManager->KeyPressed(sf::Keyboard::Down)) { mainMenu->moveDown(); }

		// Enter New Screen
		if (inputManager->KeyPressed(sf::Keyboard::Return))
		{
			mainMenu->swapScreen(window, optionsLoader);
		}

		// Return to previous screen
		if (inputManager->KeyPressed(sf::Keyboard::BackSpace))
		{
			mainMenu->backScreen(optionsLoader, optionsLoader->SPLASH);
			splashScreen->init();
		}
	}

	else if (optionsLoader->getCurrentScreen() == optionsLoader->GAME) // Game
	{
		if (inputManager->KeyPressed(sf::Keyboard::BackSpace))
		{
			optionsMenu->backScreen(optionsLoader, optionsLoader->MAINMENU);
		}
	}

	else if (optionsLoader->getCurrentScreen() == optionsLoader->LOAD) // Load
	{
		if (inputManager->KeyPressed(sf::Keyboard::BackSpace))
		{
			optionsMenu->backScreen(optionsLoader, optionsLoader->MAINMENU);
		}
	}

	else if (optionsLoader->getCurrentScreen() == optionsLoader->OPTIONS) // Options menu movement
	{
		// Main menu movement
		if (inputManager->KeyPressed(sf::Keyboard::Up)) { optionsMenu->moveUp(); }
		else if (inputManager->KeyPressed(sf::Keyboard::Down)) { optionsMenu->moveDown(); }

		// Options Function
		if (inputManager->KeyPressed(sf::Keyboard::Return))
		{
			// Option functions
		}

		if (inputManager->KeyPressed(sf::Keyboard::BackSpace))
		{
			optionsMenu->backScreen(optionsLoader, optionsLoader->MAINMENU);
		}
	}

	else if (optionsLoader->getCurrentScreen() == optionsLoader->INSTRUCTIONS) // Game
	{
		if (inputManager->KeyPressed(sf::Keyboard::BackSpace))
		{
			optionsMenu->backScreen(optionsLoader, optionsLoader->MAINMENU);
		}
	}
}