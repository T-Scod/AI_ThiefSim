#include "Thief.h"
#include "Behaviour.h"

Thief::Thief(const char * filename)
{
	m_texture = new aie::Texture(filename);
	m_health = 50;
	m_score = 0;
}
Thief::~Thief()
{
	for (auto item : m_inventory)
	{
		item = nullptr;
		delete item;
	}
	for (auto t : m_treasure)
	{
		t = nullptr;
		delete t;
	}
}

// reduces health
void Thief::attack(unsigned int damage)
{
	m_health -= damage;
}

// gives the thief knowledge of the items
void Thief::setTreasure(std::vector<Shadow*> treasure)
{
	m_treasure = treasure;
}
// adds the treasure into the inventory
void Thief::addTreasure(Shadow * treasure)
{
	m_inventory.push_back(treasure);
}
// removes the treasure from the inventory
void Thief::removeTreasure()
{
	if (m_inventory.empty())
	{
		return;
	}
	m_inventory.back()->setVisible(true);
	m_inventory.pop_back();
}

// sets the location of the exit
void Thief::setLocation(AABB2 exit)
{
	m_exit = exit;
}

// update game object and execute behaviours
void Thief::update(float deltaTime)
{
	for (auto b : m_behaviours)
	{
		b->execute(this, deltaTime);
	}
	
	// ensures that the velocity is within the maximum
	if (m_velocity.magnitude() > m_maxVelocity)
	{
		m_velocity.normalise();
		m_velocity *= m_maxVelocity;
	}

	// moves the object in the direction of the velocity
	translate(100.0f * m_velocity.x * deltaTime, 100.0f * m_velocity.y * deltaTime);

	// moves the player out of objects
	collision();

	// sets the bubbles position to be wherever the player is
	m_bubble.center = { m_obj[2].x, m_obj[2].y };

	Vector2 pos = { m_obj[2].x, m_obj[2].y };

	// checks if the thief is able to steal any of the treasure
	for (auto t : m_treasure)
	{
		// checks if the treasure is available and close
		if (pos.distance({ t->getPosition().x, t->getPosition().y }) < 20.0f && t->getVisible() == true)
		{
			// adds the treasure to the inventory
			t->setVisible(false);
			addTreasure(t);
		}
	}

	// checks if the thief has reached the exit
	if (m_bubble.overlaps(m_exit))
	{
		// adds a score for every item in the inventory
		m_score += (unsigned int)m_inventory.size();
		// removes all items from the inventory
		m_inventory.clear();
	}
}