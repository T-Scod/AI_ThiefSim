#pragma once
#include "GameObject.h"
#include <AABB2.h>
#include "Shadow.h"

class Thief : public GameObject
{
public:
	Thief(const char* filename);
	~Thief();

	// reduces health
	void attack(unsigned int damage);

	// returns the amount of health
	int getHealth() { return m_health; }

	// gives the thief knowledge of the items
	void setTreasure(std::vector<Shadow*> treasure);
	// adds the treasure into the inventory
	void addTreasure(Shadow* treasure);
	// removes the treasure from the inventory
	void removeTreasure();
	// returns the collection of treasure
	std::vector<Shadow*> getTreasure() { return m_inventory; }

	// sets the location of the exit
	void setLocation(AABB2 exit);
	// returns the score
	unsigned int getScore() { return m_score; }

	// update game object and execute behaviours
	void update(float deltaTime) override;

private:
	// the amount of health of the thief
	int m_health;
	// the items that are being stolen
	std::vector<Shadow*> m_treasure;
	// the thief's collection of stollen items
	std::vector<Shadow*> m_inventory;
	// the location of the exit
	AABB2 m_exit;
	// the talley of how many pieces of treasure the thief has delivered
	unsigned int m_score;
};