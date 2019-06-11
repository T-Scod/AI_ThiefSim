#pragma once
#include "Behaviour.h"
#include "Thief.h"

class AttackAction : public Behaviour
{
public:
	AttackAction(Thief* target, unsigned int damage);
	~AttackAction();

	// applys the damage to the target
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

private:
	// the object that is being targeted
	Thief * m_target;
	// the amount of damage applied every attack
	unsigned int m_damage;
};

