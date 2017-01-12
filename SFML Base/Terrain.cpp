#include "Terrain.h"



Terrain::Terrain()
{
	
	init();
}


Terrain::~Terrain()
{
}

void Terrain::init()
{
	pointsOnMap = new sf::Vertex[MAP_WIDTH];
	int previousY = 720;
	bool goingUp = true;
	int maxCount = rand() % 32;

	for (int i = 0; i < MAP_WIDTH; i++)
	{
		if (goingUp == true)
		{
			pointsOnMap[i] = sf::Vertex(sf::Vector2f(i * 10, previousY - rand() % 10));
			previousY = pointsOnMap[i].position.y;
			maxCount--;

			if (pointsOnMap[i].position.y <= 600) // Start - 120
			{
				maxCount = 0;
			}
		}

		if (goingUp == false)
		{
			pointsOnMap[i] = sf::Vertex(sf::Vector2f(i * 10, previousY + rand() % 10));
			previousY = pointsOnMap[i].position.y;
			maxCount--;

			if (pointsOnMap[i].position.y >= 840) // Start + 120
			{
				maxCount = 0;
			}
		}

		if (maxCount == 0)
		{
			maxCount = rand() % 32;
			goingUp = !goingUp;
		}

		if (i == MAP_WIDTH)
		{
			pointsOnMap[i].position.y = pointsOnMap[0].position.y;
		}
	}
}

void Terrain::update()
{

}

void Terrain::draw(sf::RenderWindow &window)
{
	window.draw(pointsOnMap, MAP_WIDTH, sf::LinesStrip);
}

sf::Vertex* Terrain::getPoints()
{
	return  pointsOnMap;
}

