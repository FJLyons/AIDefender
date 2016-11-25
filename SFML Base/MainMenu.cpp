#include "MainMenu.h"


MainMenu::MainMenu()
{
	init();
}


MainMenu::~MainMenu()
{
}

void MainMenu::init()
{
	//Art
	scaleFactor = sf::Vector2f(1, 1);

	if (!logoTexture.loadFromFile("content\\art\\other\\logo.png")){ std::cout << "Logo Art Error" << std::endl; }
	logoTexture.setSmooth(true);
	logoSprite.setTexture(logoTexture);
	logoSprite.setScale(scaleFactor);
	logoSprite.setOrigin(sf::Vector2f(screenSize.x / 2, screenSize.y / 2));
	logoSprite.setPosition(sf::Vector2f(screenSize.x / 2, screenSize.y / 2));

	// Index
	selectedItemIndex = 0;

	//Text
	font.loadFromFile("content\\fonts\\kenvector_future.TTF");
	
	text[0].setString("New Game");
	text[1].setString("Load Game");
	text[2].setString("Options");
	text[3].setString("Instructions");
	text[4].setString("Quit");

	for (int i = 0; i < MAX_INDEX; i++)
	{
		text[i].setFont(font);
		text[i].setPosition((screenSize.x / 2) - text[i].getLocalBounds().width / 3.5f, (screenSize.y / 2) + (48.0f * i) - text[i].getLocalBounds().height / 2.0f);
		text[i].setCharacterSize(18);
		text[i].setColor(sf::Color::White);
	}

	text[0].setColor(sf::Color::Red);
}

void MainMenu::update()
{

}

void MainMenu::draw(sf::RenderWindow &window)
{
	window.draw(logoSprite);

	for (int i = 0; i < MAX_INDEX; i++)
	{
		window.draw(text[i]);
	}
}

void MainMenu::swapScreen(sf::RenderWindow &window, OptionsLoader *options)
{
	if (getPressedItem() == 0) {
		options->setCurrentScreen(options->GAME);
		std::cout << "New Game" << std::endl;
	}

	else if (getPressedItem() == 1) {
		options->setCurrentScreen(options->LOAD);
		std::cout << "Load Game" << std::endl;
	}

	else if (getPressedItem() == 2) {
		options->setCurrentScreen(options->OPTIONS);
		std::cout << "Options" << std::endl;
	}

	else if (getPressedItem() == 3) {
		options->setCurrentScreen(options->INSTRUCTIONS);
		std::cout << "Instrctions" << std::endl;
	}

	if (getPressedItem() == 4)
	{
		std::cout << "Quit" << std::endl;
		window.close();
	}
}

void MainMenu::backScreen(OptionsLoader *options, int screen)
{
	options->setCurrentScreen(screen);
}

void MainMenu::moveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		text[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		text[selectedItemIndex].setColor(sf::Color::Red);
	}
	else
	{
		text[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex = MAX_INDEX - 1;
		text[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void MainMenu::moveDown()
{
	if (selectedItemIndex + 1 < MAX_INDEX)
	{
		text[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		text[selectedItemIndex].setColor(sf::Color::Red);
	}
	else
	{
		text[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex = 0;
		text[selectedItemIndex].setColor(sf::Color::Red);
	}
}

int MainMenu::getPressedItem()
{
	return selectedItemIndex;
}
