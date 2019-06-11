#include "AttackAction.h"

AttackAction::AttackAction(Thief * target, unsigned int damage)
{
	m_target = target;
	m_damage = damage;
}
AttackAction::~AttackAction()
{
	m_target = nullptr;
	delete m_target;
}

// applys the damage to the target
eBehaviourResult AttackAction::execute(GameObject * gameObject, float deltaTime)
{
	// reduces the target's health by the damage
	m_target->attack(m_damage);
	// removes a piece of treasure from the target
	m_target->removeTreasure();
	return SUCCESS;
}