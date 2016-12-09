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
	int previousY = 0;
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		pointsOnMap[i] = sf::Vertex(sf::Vector2f(i * 15, 1000 + previousY + rand() % 15 - 15));
		previousY = pointsOnMap[i].texCoords.y;
	}
}

void Terrain::update()
{

}

void Terrain::draw(sf::RenderWindow &window)
{
	window.draw(pointsOnMap, MAP_WIDTH, sf::LinesStrip);
}