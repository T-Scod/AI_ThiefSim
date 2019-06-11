#include "FleeForce.h"
#include "GameObject.h"

FleeForce::FleeForce()
{
	m_targPos = 0.0f;
}

// sets the target position
void FleeForce::setTargetPosition(Vector2 pos)
{
	m_targPos = pos;
}

// calculates a force that moves the velocity away from the target
Vector2 FleeForce::getForce(GameObject * gameObject)
{
	// the position of the object
	Vector2 objPos = { gameObject->getPosition().x, gameObject->getPosition().y };
	// the current velocity of the object
	Vector2 currentVelocity = gameObject->getVelocity();
	
	// sets the max speed of the object
	gameObject->setMaxVelocity(50.0f);
	float maxSpeed = gameObject->getMaxVelocity();

	// the velocity vector between the object and the target in the opposite direction
	Vector2 direction = objPos - m_targPos;
	direction.normalise();
	direction *= maxSpeed;

	// the force required to be added to the current velocity to result in the desired direction vector
	Vector2 force = direction - currentVelocity;

	return force;
}