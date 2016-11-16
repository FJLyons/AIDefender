#include "OptionsMenu.h"

OptionsMenu::OptionsMenu()
{
	init();
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::init()
{
	//Art
	scaleFactor = sf::Vector2f((1280.0f / 1920.0f), (720.0f / 1080.0f));

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

	text[0].setString("test");

	for (int i = 0; i < MAX_INDEX; i++)
	{
		text[i].setString("test");
		text[i].setFont(font);
		text[i].setPosition((screenSize.x / 2) - text[i].getLocalBounds().width / 3.5f, (screenSize.y / 2) + (48.0f * i) - text[i].getLocalBounds().height / 2.0f);
		text[i].setCharacterSize(18);
		text[i].setColor(sf::Color::White);
	}

	text[0].setColor(sf::Color::Red);
}

void OptionsMenu::update()
{

}

void OptionsMenu::draw(sf::RenderWindow &window)
{
	window.draw(logoSprite);

	for (int i = 0; i < MAX_INDEX; i++)
	{
		window.draw(text[i]);
	}
}

void OptionsMenu::swapScreen(OptionsLoader *options)
{
	options->setCurrentScreen(options->MAINMENU);
}

void OptionsMenu::backScreen(OptionsLoader *options, int screen)
{
	options->setCurrentScreen(screen);
}

void OptionsMenu::moveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		text[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		text[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void OptionsMenu::moveDown()
{
	if (selectedItemIndex + 1 < MAX_INDEX)
	{
		text[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		text[selectedItemIndex].setColor(sf::Color::Red);
	}
}

int OptionsMenu::getPressedItem()
{
	return selectedItemIndex;
}

