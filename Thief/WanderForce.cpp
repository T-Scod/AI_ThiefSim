#include "WanderForce.h"
#include "GameObject.h"
#include <random>

WanderForce::WanderForce()
{
	m_distance = 1.0f;
	m_circle = Circle({ 1.0f, 1.0f }, 1.0f);
	m_jitterAmount = (asinf(1.0f) * 15.0f);
	m_wanderAngle = 0.0f;
}
WanderForce::WanderForce(Circle circle, float dist, int jitter)
{
	m_circle = circle;
	m_distance = dist;
	m_jitterAmount = jitter;
	m_wanderAngle = 0.0f;
}

// calculates a force that moves the velocity by a displacement around a circle
Vector2 WanderForce::getForce(GameObject * gameObject)
{
	// gets the position of the object
	Vector2 objPos = { gameObject->getPosition().x, gameObject->getPosition().y };
	// gets the velocity of the object
	Vector2 objVel = gameObject->getVelocity();
	// adding the velocity to the position gives the facing direction of the object and location
	Vector2 facing = objPos + objVel;
	facing.normalise();
	// multiplying that vector by the desired distance clamps it to the distance
	facing *= m_distance;

	// the facing vector helps calculate the position of the circle's center
	m_circle.center = facing;

	// the displacement vector from the circle's radius
	Vector2 displacement = setAngle() + m_circle.center;

	// displacement is also the vector that transforms the velocity into the wander velocity
	return displacement;
}

// calculates the angle of the displacement and randomises the wander angle
Vector2 WanderForce::setAngle()
{
	// converts the angle to degrees so that modulus can be used
	m_wanderAngle *= (180.0f / PI);
	// randomises the wander angle and clamps it to the jitter amount
	m_wanderAngle += -m_jitterAmount + (rand() % (m_jitterAmount - -m_jitterAmount + 1));
	// converts the angle back to radians
	m_wanderAngle *= (PI / 180.0f);

	// displacement vector
	return { cosf(m_wanderAngle) * m_circle.radius, sinf(m_wanderAngle) * m_circle.radius };
}