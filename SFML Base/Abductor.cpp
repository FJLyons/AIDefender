#include "Abductor.h"

Abductor::Abductor()
{
}
Abductor::Abductor(sf::Vector2f pos,bool lead)
{
	leader = lead;
	srand(time(NULL));
	mTexture = ResourceLoader::instance()->getabductorTexture();
	bulletTexture = ResourceLoader::instance()->getbulletTexture();
	mPositon = pos;
	velocity = sf::Vector2f(10,0.5);
	mSprite.setTexture(mTexture);
	mSprite.setPosition(mPositon);
	mSprite.setOrigin(sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2));
	currentBehaviour = Behaviour::Wander;
	
	range = 700;
	srand(time(NULL));
	//seekPoint = FindNewPoint();
	//if (leader == true)
	//{
			seekPoint = sf::Vector2f(2000, 500);
	//}

	canShoot = true;
	shotTimer = 0;
	shotdelay = 0.5;

	collisionRect.setOrigin(mSprite.getGlobalBounds().width / 2, mSprite.getGlobalBounds().height / 2);
	collisionRect.setSize(sf::Vector2f(mSprite.getGlobalBounds().width , mSprite.getGlobalBounds().height));
	collisionRect.setOutlineColor(sf::Color::Red);
	collisionRect.setFillColor(sf::Color::Transparent);
	collisionRect.setOutlineThickness(2);
	collisionRect.setPosition(mPositon);

	FeildofView.setOrigin(0, 150);
	FeildofView.setSize(sf::Vector2f(300, 300));
	FeildofView.setOutlineColor(sf::Color::Yellow);
	FeildofView.setFillColor(sf::Color::Transparent);
	FeildofView.setOutlineThickness(2);
	FeildofView.setPosition(mPositon);

	

	alignment = sf::Vector2f(0, 0);
	cohesion = sf::Vector2f(0, 0);
	seperation = sf::Vector2f(0, 0);
}
sf::Vector2f Abductor::FindNewPoint()
{
	sf::Vector2f newPoint = sf::Vector2f(rand() % (1920 * 9) + 1, 500);//rand() % (500) + 1);
	return  newPoint;
}
void Abductor::Wandering(std::vector<Abductor*>& abductors)
{

		alignment = ComputeAlignment(abductors);
		cohesion = ComputeCohesion(abductors);
		seperation = ComputeSeperation(abductors);
	
		sf::Vector2f Direction = seekPoint - mPositon;
		float length = sqrt((Direction.x * Direction.x) + (Direction.y * Direction.y));
		Direction = Direction / length;

		velocity.x += alignment.x + cohesion.x + seperation.x*3 + Direction.x;
		velocity.y += alignment.y + cohesion.y + seperation.y *3+ Direction.y;

		
		velocity = CollisionManager::NormaliseVector(velocity);
		velocity.x = velocity.x * 10;
		velocity.y = velocity.y * 10;

		mPositon += velocity;
		mSprite.setPosition(mPositon);
	
		if (CollisionManager::CheckRange(mSprite.getGlobalBounds().width, seekPoint, mPositon) == true)
		{
			seekPoint = FindNewPoint();
		}

}
sf::Vector2f Abductor::ComputeAlignment(std::vector<Abductor*>& abductors)
{
	sf::Vector2f m_alignment;
	neighbourcount = 0;
	for (int i = 0; i < abductors.size(); i++)
	{
		if (i != myIndex)
		{
			if (CollisionManager::RectangleCollision(FeildofView, abductors[i]->getFOVRect()) == true && CollisionManager::RectangleCollision(collisionRect, abductors[i]->getRect()) == false)//CollisionManager::CheckRange(neighbourRange, abductors[i]->getPosition(), mPositon) == true)
			{
			/*	if (abductors[i]->getLeader() == false)
				{
					leader == true;
				}*/
				m_alignment += abductors[i]->getVelocity();
				/*if (leader == true)
				{
					abductors[i]->setseekPoint(seekPoint);
				}*/
				neighbourcount++;
			}

		}
	
	}
	if (neighbourcount == 0)
	{
		
		return  sf::Vector2f(0, 0);
	}
	else
	{
		m_alignment.x = m_alignment.x / neighbourcount;
		m_alignment.y = m_alignment.y / neighbourcount;
		m_alignment = CollisionManager::NormaliseVector(m_alignment);
		return m_alignment;
	}

	

}
sf::Vector2f Abductor::ComputeCohesion(std::vector<Abductor*>& abductors)
{
	sf::Vector2f m_Cohesion;
	neighbourcount = 0;

	for (int i = 0; i < abductors.size(); i++)
	{
		if (i != myIndex)
		{
			if (CollisionManager::RectangleCollision(FeildofView,abductors[i]->getRect())==true && CollisionManager::RectangleCollision(collisionRect, abductors[i]->getRect()) == false)//CollisionManager::CheckRange(neighbourRange, abductors[i]->getPosition(), mPositon) == true && CollisionManager::RectangleCollision(collisionRect, abductors[i]->getRect()) == false)
			{
				m_Cohesion += abductors[i]->getPosition();
				neighbourcount++;
			}

		}
	}
	if (neighbourcount == 0)
	{
		return sf::Vector2f(0, 0);
	}
	else
	{
		m_Cohesion.x = m_Cohesion.x / neighbourcount;
		m_Cohesion.y = m_Cohesion.y / neighbourcount;
		m_Cohesion = m_Cohesion - mPositon;
		m_Cohesion = CollisionManager::NormaliseVector(m_Cohesion);
		return m_Cohesion;
	}

}
sf::Vector2f Abductor::ComputeSeperation(std::vector<Abductor*>& abductors)
{
	sf::Vector2f m_Seperation;
	neighbourcount = 0;

	for (int i = 0; i < abductors.size(); i++)
	{
		if (i != myIndex)
		{
			if (CollisionManager::RectangleCollision(collisionRect,abductors[i]->getRect()) == true)//CollisionManager::CheckRange(mSprite.getGlobalBounds().width, abductors[i]->getPosition(), mPositon) == true)
			{
				m_Seperation += abductors[i]->getPosition() - mPositon;
				neighbourcount++;
			}

		}
	}
	if (neighbourcount == 0)
	{
		return sf::Vector2f(0, 0);
	}
	else
	{
		m_Seperation.x = m_Seperation.x / neighbourcount;
		m_Seperation.y = m_Seperation.y / neighbourcount;
		m_Seperation.x *= -1;
		m_Seperation.y *= -1;
		
		m_Seperation = CollisionManager::NormaliseVector(m_Seperation);
		return m_Seperation;
	}
}
void Abductor::Flocking()
{
}
void Abductor::Abducting()
{
}
void Abductor::Update(std::vector<Abductor*>& abductors,int indexofCurrentAbductor)
{
	myIndex = indexofCurrentAbductor;

	if (currentBehaviour == Behaviour::Wander)
	{
		Wandering(abductors);
	}
	else if (currentBehaviour == Behaviour::Abduct)
	{
		Abducting();
	}
	else if (currentBehaviour == Behaviour::Flock)
	{
		Flocking();
	}
	float  angle = atan2(velocity.y,velocity.x);
	angle = angle * (180 / 3.14);
	mSprite.setRotation(angle);
	FeildofView.setRotation(angle);
	collisionRect.setPosition(mPositon);
	FeildofView.setPosition(mPositon);
	
}
void Abductor::Draw(sf::RenderWindow & window)
{
	window.draw(mSprite);
	window.draw(collisionRect);
	window.draw(FeildofView);
	sf::CircleShape tempcirc(10);



}

sf::Vector2f Abductor::getVelocity()
{
	return velocity;
}

sf::Vector2f Abductor::getPosition()
{
	return mPositon;
}

sf::RectangleShape Abductor::getRect()
{
	return collisionRect;
}

sf::RectangleShape Abductor::getFOVRect()
{
	return FeildofView;
}

sf::Vector2f Abductor::getseekPoint()
{
	return seekPoint;
}

void Abductor::setseekPoint(sf::Vector2f point)
{
	seekPoint = point;
}

bool Abductor::getLeader()
{
	return leader;
}


