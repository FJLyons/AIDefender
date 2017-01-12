#include "Camera.h"

Camera::Camera()
{
	init();
}


Camera::~Camera()
{
}

void Camera::init()
{
	// View
	view.setSize(screenSize);
	view.setCenter(screenCenter);
}

void Camera::update(Player *player)
{
	view.setCenter(sf::Vector2f(player->getPosition().x, screenSize.y / 2));
}

void Camera::draw(sf::RenderWindow &window)
{
	window.setView(view);
}

sf::View Camera::getView()
{
	return view;
}

void Camera::setViewCenter(sf::Vector2f *position)
{
	view.setCenter(*position);
}

void Camera::resetView()
{
	if (view.getCenter() != screenCenter)
	{
		view.setCenter(screenCenter);
	}
}