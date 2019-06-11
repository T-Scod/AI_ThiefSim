#include "WanderAction.h"

WanderAction::WanderAction()
{
	m_force = WanderForce();
}

// applies a wander force to the object without changing its position
eBehaviourResult WanderAction::execute(GameObject * gameObject, float deltaTime)
{
	// stores the object's position
	Vector3 objPos = gameObject->getPosition();

	// applies the wander force to the object
	gameObject->addForce(m_force.getForce(gameObject), deltaTime);
	// ensures that the object does not move
	gameObject->setLock(true);
	// the object's velocity
	Vector2 vel = gameObject->getVelocity();
	vel.normalise();
	gameObject->setVelocity(vel);

	return SUCCESS;
}