#include "Game.h"

Game::Game(Camera* cam)
{
	camera = cam;
	init();
}

Game::~Game()
{
}

void Game::init()
{
	font.loadFromFile("content\\fonts\\kenvector_future.TTF");

	terrain = new Terrain();
	player = new Player(screenSize * 0.5f, sf::Vector2f(30, 30));//set up player

	spawn();

	meteorSpwanTimer = 0;
	meteorSpawnDelay = rand() % 5;
}

void Game::update()
{
	camera->update(player);
	player->Update();
	if (player->health <= 0) 
	{
		resource->explosion.play();
		gameOver(false); 
		player->health += 1;
	}

	// Human
	for (int i = 0; i < humans.size(); i++)
	{
		humans[i]->Update(player->getPosition());

		// Collisions
		// Player
		if (collisionManager->RectangleCollision(player->getRect(), humans[i]->getRect()))
		{
			resource->menuSelect.play();

			humansToDelete.push_back(humans[i]); // For Memory Clean up
			humans.erase(humans.begin() + i);

			i--;
			continue;
		}
	}

	// Meteor
	for (int i = 0; i < meteors.size(); i++)
	{
		meteors[i]->Update();

		// Death
		if (meteors[i]->getPosition().y >= 1080)
		{
			resource->hit.play();

			meteorsToDelete.push_back(meteors[i]); // For Memory Clean up
			meteors.erase(meteors.begin() + i);
		}

		// Collisions
		// Player
		if (collisionManager->RectangleCollision(player->getRect(), meteors[i]->getRect()))
		{
			resource->hit.play();

			player->health--;

			meteorsToDelete.push_back(meteors[i]); // For Memory Clean up
			meteors.erase(meteors.begin() + i);
			
			i--;
			continue;
		}

		// Bullets
		bool checkNext = true;
		for (int j = 0; checkNext && j < player->getBullets().size(); j++)
		{
			if (collisionManager->RectangleCollision(player->getBullets().at(j)->getRect(), meteors[i]->getRect()))
			{
				resource->hit.play();

				player->deleteBullet(j);

				meteorsToDelete.push_back(meteors[i]); // For Memory Clean up
				meteors.erase(meteors.begin() + i);

				j--;
				i--;
				checkNext = false;
				continue;
			}
		}
	}


	// Enemies with Health 
	// Nest
	for (int i = 0; i < nests.size(); i++)
	{
		nests[i]->Update(player->getRect(), abductors,meteors);

		// Collisions
		// Player
		if (collisionManager->RectangleCollision(player->getRect(), nests[i]->getRect()))
		{
			resource->hit.play();

			player->health--;

			// Die
			resource->explosion.play();
			nestsToDelete.push_back(nests[i]); // For Memory Clean up
			nests.erase(nests.begin() + i);

			i--;
			continue;
		}

		// Bullets
		bool checkNext = true;
		for (int j = 0; checkNext && j < player->getBullets().size(); j++)
		{
			if (collisionManager->RectangleCollision(player->getBullets().at(j)->getRect(), nests[i]->getRect()))
			{
				resource->hit.play();

				player->deleteBullet(j);

				nests[i]->health--;

				// Die
				if (nests[i]->health <= 0)
				{
					resource->explosion.play();
					nestsToDelete.push_back(nests[i]); // For Memory Clean up
					nests.erase(nests.begin() + i);
				}

				j--;
				i--;
				checkNext = false;
				continue;
			}
		}

		// Meteor
		for (int j = 0; checkNext && j < meteors.size(); j++)
		{
			if (collisionManager->RectangleCollision(meteors[j]->getRect(), nests[i]->getRect()))
			{
				resource->hit.play();

				meteorsToDelete.push_back(meteors[j]); // For Memory Clean up
				meteors.erase(meteors.begin() + j);

				nests[i]->health--;

				// Die
				if (nests[i]->health <= 0)
				{
					resource->explosion.play();
					nestsToDelete.push_back(nests[i]); // For Memory Clean up
					nests.erase(nests.begin() + i);
				}

				j--;
				i--;
				checkNext = false;
				continue;
			}
		}
	}
	
	// Abductors
	for (int i = 0; i < abductors.size(); i++)
	{
		abductors[i]->Update(abductors, i,meteors,humans,player->getPosition());

		// Create Mutant
		if (abductors[i]->getAlive() == false)//if an abductor has successfully abducted a human
		{
			resource->back.play();

			mutants.push_back(new Mutant(abductors[i]->getPosition()));
			mutants.back()->health = currentLevel * 2;

			abductorsToDelete.push_back(abductors[i]); // For Memory Clean up
			abductors.erase(abductors.begin() + i);

			i--;
			continue;
		}

		// Collisions
		// Player
		if (collisionManager->RectangleCollision(player->getRect(), abductors[i]->getRect()))
		{
			resource->hit.play();

			player->health--;

			// Die
			resource->explosion.play();
			abductors[i]->DropHuman(humans);
			abductorsToDelete.push_back(abductors[i]); // For Memory Clean up
			abductors.erase(abductors.begin() + i);			

			i--;
			continue;
		}	

		// Bullets
		bool checkNext = true;
		for (int j = 0; checkNext && j < player->getBullets().size(); j++)
		{
			if (collisionManager->RectangleCollision(player->getBullets().at(j)->getRect(), abductors[i]->getRect()))
			{
				resource->hit.play();

				player->deleteBullet(j);

				abductors[i]->health--;

				// Die
				if (abductors[i]->health <= 0)
				{
					resource->explosion.play();
					abductors[i]->DropHuman(humans);
					abductorsToDelete.push_back(abductors[i]); // For Memory Clean up
					abductors.erase(abductors.begin() + i);
				}

				j--;
				i--;
				checkNext = false;
				continue;
			}
		}

		// Meteor
		for (int j = 0; checkNext && j < meteors.size(); j++)
		{
			if (collisionManager->RectangleCollision(meteors[j]->getRect(), abductors[i]->getRect()))
			{
				resource->hit.play();

				meteorsToDelete.push_back(meteors[j]); // For Memory Clean up
				meteors.erase(meteors.begin() + j);

				abductors[i]->DropHuman(humans);

				abductors[i]->health--;

				// Die
				if (abductors[i]->health <= 0)
				{
					resource->explosion.play();
					abductorsToDelete.push_back(abductors[i]); // For Memory Clean up
					abductors.erase(abductors.begin() + i);
				}

				j--;
				i--;
				checkNext = false;
				continue;
			}
		}
	}

	//Mutants
	for (int i = 0; i < mutants.size(); i++)
	{
		mutants[i]->Update(mutants,i, meteors, player->getPosition(),player->getVelocity());

		// Collisions
		// Player
		if (collisionManager->RectangleCollision(player->getRect(), mutants[i]->getRect()))
		{
			resource->hit.play();

			player->health--;

			// Die
			resource->explosion.play();
			mutantsToDelete.push_back(mutants[i]); // For Memory Clean up
			mutants.erase(mutants.begin() + i);

			i--;
			continue;
		}

		// Bullets
		bool checkNext = true;
		for (int j = 0; checkNext && j < player->getBullets().size(); j++)
		{
			if (collisionManager->RectangleCollision(player->getBullets().at(j)->getRect(), mutants[i]->getRect()))
			{
				resource->hit.play();

				player->deleteBullet(j);

				mutants[i]->health--;

				// Die
				if (mutants[i]->health <= 0)
				{
					resource->explosion.play();
					mutantsToDelete.push_back(mutants[i]); // For Memory Clean up
					mutants.erase(mutants.begin() + i);
				}

				j--;
				i--;
				checkNext = false;
				continue;
			}
		}

		// Meteor
		for (int j = 0; checkNext && j < meteors.size(); j++)
		{
			if (collisionManager->RectangleCollision(meteors[j]->getRect(), mutants[i]->getRect()))
			{
				resource->hit.play();

				meteorsToDelete.push_back(meteors[j]); // For Memory Clean up
				meteors.erase(meteors.begin() + j);

				mutants[i]->health--;

				// Die
				if (mutants[i]->health <= 0)
				{
					resource->explosion.play();
					mutantsToDelete.push_back(mutants[i]); // For Memory Clean up
					mutants.erase(mutants.begin() + i);
				}

				j--;
				i--;
				checkNext = false;
				continue;
			}
		}
	}

	if (mutants.empty() && abductors.empty() && nests.empty())
	{
		resource->levelUp.play();
		humans.clear();
		nextLevel();
	}

	teleport();
	MeteorSpawn();
}

void Game::draw(sf::RenderWindow &window)
{
	//Game
	camera->drawGame(window);
	terrain->draw(window);
	player->Draw(window);
	for (int i = 0; i < meteors.size(); i++)
	{
		meteors[i]->Draw(window);
	}
	for (int i = 0; i < humans.size(); i++)
	{
		humans[i]->Draw(window, false);
	}
	for (int i = 0; i < nests.size(); i++)
	{
		nests[i]->Draw(window);
	}
	for (int i = 0; i < abductors.size(); i++)
	{
		abductors[i]->Draw(window);
	}
	for (int i = 0; i < mutants.size(); i++)
	{
		mutants[i]->Draw(window);
	}

	// Mini Map
	camera->drawRadar(window);
	terrain->draw(window);
	player->Draw(window);
	for (int i = 0; i < meteors.size(); i++)
	{
		meteors[i]->Draw(window);
	}
	for (int i = 0; i < humans.size(); i++)
	{
		humans[i]->Draw(window, true);
	}
	for (int i = 0; i < nests.size(); i++)
	{
		nests[i]->Draw(window);
	}
	for (int i = 0; i < abductors.size(); i++)
	{
		abductors[i]->Draw(window);
	}
}

void Game::goToScene(int scene)
{
	myGlobalOptions->setCurrentScene(scene);
}

void Game::input(sf::Event Event)
{
	if (Event.type == sf::Event::KeyPressed)
	{
		std::cout << Event.key.code << std::endl;
	}

	if (inputManager->KeyPressed(sf::Keyboard::BackSpace))
	{
		camera->resetView();
		std::cout << "Back Space" << std::endl;
		goToScene(myGlobalOptions->MAINMENU);
		resource->musicMenu.play();
		resource->musicGame.pause();
	}

	if (inputManager->KeyPressed(sf::Keyboard::Num0))
	{
	}

	controller(Event);
}

void Game::controller(sf::Event Event)
{
	// Left
	if (inputManager->KeyPressed(sf::Keyboard::A))
	{
		player->FaceLeft();
	}
	else if (inputManager->KeyHeld(sf::Keyboard::A) && !inputManager->KeyHeld(sf::Keyboard::D))
	{
		player->MoveLeft();
	}
	else if (inputManager->KeyReleased(sf::Keyboard::A) || !inputManager->KeyHeld(sf::Keyboard::D))
	{
		player->Decelerate();
	}

	// Right
	if (inputManager->KeyPressed(sf::Keyboard::D))
	{
		player->FaceRight();
	}
	else if (inputManager->KeyHeld(sf::Keyboard::D) && !inputManager->KeyHeld(sf::Keyboard::A))
	{
		player->MoveRight();
	}
	else if (inputManager->KeyReleased(sf::Keyboard::D) || !inputManager->KeyHeld(sf::Keyboard::A))
	{
		player->Decelerate();
	}

	// Up
	if (inputManager->KeyPressed(sf::Keyboard::W))
	{
		player->MoveUp(true);
	}
	else if (inputManager->KeyReleased(sf::Keyboard::W))
	{
		player->MoveUp(false);
	}

	// Down
	if (inputManager->KeyPressed(sf::Keyboard::S))
	{
		player->MoveDown(true);
	}
	else if (inputManager->KeyReleased(sf::Keyboard::S))
	{
		player->MoveDown(false);
	}

	// Shoot
	if (inputManager->KeyHeld(sf::Keyboard::Space))
	{
		player->Shoot();
	}
	if (inputManager->KeyHeld(sf::Keyboard::Num1)&& player->getbombLoaded() == true&& player->getBombfired() == false)
	{
		player->setBombfired(true);
		
	}
}

void Game::teleport()
{
	if (player->teleport())
	{
		// Human
		for (int i = 0; i < humans.size(); i++)
		{
			if (humans[i]->getPoint() < (SCREEN_WIDTH_POINTS) && player->teleportLeft == true)
			{
				humans[i]->setPoint(humans[i]->getPoint() + MAP_WIDTH_POINTS);
			}

			else if (humans[i]->getPoint() > FULL_WIDTH_POINTS - (SCREEN_WIDTH_POINTS) && player->teleportLeft == false)
			{
				humans[i]->setPoint(humans[i]->getPoint() - MAP_WIDTH_POINTS);
			}
		}

		// Obstacle
		for (int i = 0; i < meteors.size(); i++)
		{
			if (meteors[i]->getPosition().x < (SCREEN_WIDTH_PIXEL) && player->teleportLeft == true)
			{
				meteors[i]->setPosition(sf::Vector2f(meteors[i]->getPosition().x + (MAP_WIDTH_PIXEL), meteors[i]->getPosition().y));
			}

			else if (meteors[i]->getPosition().x > (FULL_WIDTH_PIXEL) -(HALF_SCREEN_WIDTH_PIXEL * 3) && player->teleportLeft == false)
			{
				meteors[i]->setPosition(sf::Vector2f(meteors[i]->getPosition().x - (MAP_WIDTH_PIXEL), meteors[i]->getPosition().y));
			}
		}
	}
}

void Game::MeteorSpawn()
{
	meteorSpwanTimer += 1.0f / 60.0f;

	if (meteorSpwanTimer >= meteorSpawnDelay / currentLevel)
	{
		meteors.push_back(new Obstacles());
		meteorSpawnDelay = rand() % 5;
		meteorSpwanTimer = 0;
	}
}

void Game::spawn()
{
	for (int i = 0; i < currentLevel; i++)
	{
		humans.push_back(new Human(terrain->getPoints()));
		nests.push_back(new Nest(sf::Vector2f(rand() % (1920 * 9) + 1, rand() % (500) + 1)));
		abductors.push_back(new Abductor(sf::Vector2f(rand() % (1920 * 8), 50)));
		abductors.push_back(new Abductor(sf::Vector2f(rand() % (1920 * 8), 50)));
		abductors.push_back(new Abductor(sf::Vector2f(rand() % (1920 * 8), 50)));
		abductors.push_back(new Abductor(sf::Vector2f(rand() % (1920 * 8), 50)));
	}
}

void Game::clearVectors()
{
	for (std::vector<Human*>::iterator it = humansToDelete.begin(); it != humansToDelete.end(); ++it)
	{
		delete *it;
	}
	humansToDelete.clear();

	for (std::vector<Obstacles*>::iterator it = meteorsToDelete.begin(); it != meteorsToDelete.end(); ++it)
	{
		delete *it;
	}
	meteorsToDelete.clear();

	for (std::vector<Abductor*>::iterator it = abductorsToDelete.begin(); it != abductorsToDelete.end(); ++it)
	{
		delete *it;
	}
	abductorsToDelete.clear();

	for (std::vector<Nest*>::iterator it = nestsToDelete.begin(); it != nestsToDelete.end(); ++it)
	{
		delete *it;
	}
	nestsToDelete.clear();

	for (std::vector<Mutant*>::iterator it = mutantsToDelete.begin(); it != mutantsToDelete.end(); ++it)
	{
		delete *it;
	}
	mutantsToDelete.clear();
}

void Game::nextLevel()
{
	clearVectors();

	player->health++;
	currentLevel++;

	spawn();

	for (int i = 0; i < abductors.size(); i++)
	{
		abductors[i]->health = currentLevel;
	}

	for (int i = 0; i < nests.size(); i++)
	{
		nests[i]->health = currentLevel + (currentLevel / 2);
	}
}

void Game::gameOver(bool win)
{

}