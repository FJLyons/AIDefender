#include "SplashScreen.h"


SplashScreen::SplashScreen()
{
	init();
}


SplashScreen::~SplashScreen()
{
}

void SplashScreen::init()
{
	// Art
	scaleFactor = sf::Vector2f(1, 1);

	if (!logoTexture.loadFromFile("content\\art\\other\\logo.png")){ std::cout << "Logo Art Error" << std::endl; }
	logoTexture.setSmooth(true);
	logoSprite.setTexture(logoTexture);
	//logoSprite.setScale(scaleFactor);
	logoSprite.setOrigin(sf::Vector2f(screenSize.x / 2, screenSize.y / 2));
	logoSprite.setPosition(sf::Vector2f(screenSize.x / 2, screenSize.y / 2));
	logoSprite.setColor(sf::Color(255, 255, 255, 0));

	alphaFade = 0;
	fadeMultiply = 1.0f;

	// Writing
	pressAny = "Press Any Button to Continue!";
	currentLetter = 0;

	font.loadFromFile("content\\fonts\\kenvector_future.TTF");
	text.setFont(font);
	text.setString("");
	text.setPosition(screenSize.x / 2, screenSize.y / 2);
	text.setCharacterSize(18);

	printed = false;
	textFade = 255;
	fading = false;
}

void SplashScreen::update()
{
	// Fade in image
	fade();
}

void SplashScreen::draw(sf::RenderWindow &window)
{
	window.draw(logoSprite);
	window.draw(text);
}

void SplashScreen::swapScreen(OptionsLoader *options)
{
	options->setCurrentScreen(options->MAINMENU);
}

void SplashScreen::print(const std::string& str, int delay) 
{
	if (clock.getElapsedTime().asMilliseconds() > delay && currentLetter < str.size())
	{
		clock.restart();
		currentLetter++;
		text.setString(sf::String(str.substr(0, currentLetter)));
		text.setPosition((screenSize.x / 2) - text.getLocalBounds().width / 2.0f, (screenSize.y / 2) - text.getLocalBounds().height / 2.0f);
	}

	if (currentLetter >= str.size())
	{
		printed = true;
		fading = true;
	}
}

void SplashScreen::fade()
{
	if (alphaFade < 255)
	{
		logoSprite.setColor(sf::Color(255, 255, 255, alphaFade));
		alphaFade += fadeMultiply;
		fadeMultiply *= 1.007f; // 1.98333 seconds // License to kill
	}

	// Check if string has finished printing
	if (printed == false) { print(pressAny, 100); }

	// If string has printed, change its alpha
	if (printed == true)
	{
		text.setColor(sf::Color(255, 255, 255, textFade));
		if (fading == true && textFade >= 50) { textFade -= 3; }
		else { fading = false; }

		if (fading == false && textFade <= 250) { textFade += 5; }
		else { fading = true; }
	}
}
