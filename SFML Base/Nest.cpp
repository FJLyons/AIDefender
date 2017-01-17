#include "Nest.h"

Nest::Nest()
{
}

Nest::Nest( sf::Vector2f pos)
{
	mTexture = ResourceLoader::instance()->getnestTexture();
	
	mPositon = pos;
	velocity = sf::Vector2f(10, 10);

	mSprite.setTexture(mTexture);
	mSprite.setPosition(mPositon);
	mSprite.setOrigin(sf::Vector2f(mSprite.getLocalBounds().width / 2,mSprite.getLocalBounds().height / 2));

	currentBehaviour = Behaviour::Wander;
	range = 700;
	srand(time(NULL));
	seekPoint = FindNewPoint();


	canShoot = true;
	shotTimer = 0;
	shotdelay = 2;

	spawnTimer = 0;
	

	collisionRect.setOrigin(mSprite.getGlobalBounds().width / 2, mSprite.getGlobalBounds().height / 2);
	collisionRect.setSize(sf::Vector2f(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height));
	collisionRect.setOutlineColor(sf::Color::Red);
	collisionRect.setFillColor(sf::Color::Transparent);
	collisionRect.setOutlineThickness(2);
	collisionRect.setPosition(mPositon);
	spawnDelay = (rand() % (10) + 5);
}

sf::Vector2f Nest::FindNewPoint()
{
	sf::Vector2f newPoint =sf::Vector2f(rand() % (1920 * 9) + 1, rand() % (500) + 1);
	return  newPoint;
}



void Nest::Wandering()
{
	sf::Vector2f Direction = seekPoint - mPositon;
	float length = sqrt((Direction.x * Direction.x) + (Direction.y * Direction.y));
	Direction = Direction / length;
	mPositon += sf::Vector2f(Direction.x * velocity.x, Direction.y * velocity.y);
	mSprite.setPosition(mPositon);

	if (CollisionManager::CheckRange(10,seekPoint, mPositon) == true)
	{
		seekPoint=FindNewPoint();
	}

}

void Nest::Evading()
{
	if (playerPosition.x > mPositon.x)
	{
		velocity = sf::Vector2f(-5, 0);
	}
	else
	{
		velocity = sf::Vector2f(5, 0);
	}
	
	mPositon += velocity;
	mSprite.setPosition(mPositon);


}
void Nest::Update(sf::RectangleShape  player, std::vector<Abductor*> &abductors)
{
	SpawnAbductors(abductors);
	playerPosition = player.getPosition();
	shotTimer += shotClock.getElapsedTime().asSeconds();
	sf::Time dt = shotClock.restart();

	if (shotTimer > shotdelay)
	{
		canShoot = true;
	}
	else
	{
		canShoot = false;
	}
	if (CollisionManager::CheckRange(400, playerPosition, mPositon)==true)
	{
		//currentBehaviour = Behaviour::Evade;
		
	}
	else
	{
		currentBehaviour = Behaviour::Wander;
		
	}
	if (CollisionManager::CheckRange(range, playerPosition, mPositon) == true && missileList.size() <3 && canShoot == true )
	{
		
		missileList.push_back(new InterceptorMissile(mPositon));
		shotTimer = 0;
	}
	

	for (int i = 0; i< missileList.size(); i++)
	{
		if (missileList[i]->Update(player) == false)
		{
			missileList.erase(missileList.begin() + i);
		}
	}

	if (currentBehaviour == Behaviour::Wander)
	{
		Wandering();
	}
	else if (currentBehaviour == Behaviour::Evade)
	{
		Evading();
	}

	collisionRect.setPosition(mPositon);
}
void Nest::Draw(sf::RenderWindow & window)
{
	window.draw(mSprite);

	if (myGlobalOptions->drawCollisionBox)
	{
		window.draw(collisionRect);
	}

	for (int i = 0; i < missileList.size(); i++)
	{
		missileList[i]->Draw(window);
	}
}

void Nest::SpawnAbductors(std::vector<Abductor*> &abductors)
{
	
	spawnTimer += spawnClock.getElapsedTime().asSeconds();
	spawnClock.restart();
	if (spawnTimer > spawnDelay)
	{
		spawnTimer = 0;
		spawnDelay = (rand() % (10) + 5);
		abductors.push_back(new Abductor(mPositon,false));
	}
}

//void Nest::calculateDrift()
//{
//	driftTimer += shotClock.getElapsedTime().asSeconds();
//	
//
//	if (driftTimer > 3)
//	{
//		int randomUpDown = rand() % (100) + 1;
//
//		if (randomUpDown % 2 == 0)
//		{
//			velocity.y = -velocity.y;
//			driftTimer = 0;
//		}
//		else
//		{
//			velocity.y = velocity.y;
//			driftTimer = 0;
//		}
//	}
//}

