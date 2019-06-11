#include "PursueForce.h"
#include "GameObject.h"

PursueForce::PursueForce()
{
	m_targPos = 0.0f;
}

// sets the target position
// should be the sum of the position of the target object and the target's velocity
void PursueForce::setTargetPosition(Vector2 pos)
{
	m_targPos = pos;
}

// calculates a force that moves the velocity towards the target's velocity
Vector2 PursueForce::getForce(GameObject * gameObject)
{
	// the position of the object
	Vector2 objPos = { gameObject->getPosition().x, gameObject->getPosition().y };
	// the current velocity of the object
	Vector2 currentVelocity = gameObject->getVelocity();

	// sets the max speed of the object
	gameObject->setMaxVelocity(1.0f);
	float maxSpeed = gameObject->getMaxVelocity();

	// the velocity vector between the object and where the target is heading
	Vector2 direction = m_targPos - objPos;
	direction.normalise();
	direction *= maxSpeed;

	// the force required to be added to the current velocity to result in the desired direction vector
	Vector2 force = direction - currentVelocity;

	return force;
}