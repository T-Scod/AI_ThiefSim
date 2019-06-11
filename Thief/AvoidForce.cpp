#include "AvoidForce.h"
#include "GameObject.h"

AvoidForce::AvoidForce()
{
	m_obstacle = nullptr;
}

// sets the obstacle
void AvoidForce::setObstacle(Circle* circle)
{
	m_obstacle = circle;
}

// calculates the force that will move the object away from the obstacle
Vector2 AvoidForce::getForce(GameObject * gameObject)
{
	// the point at the end of the ray
	Vector2 ahead = gameObject->getRay().direction + gameObject->getRay().origin;
	// the vector between the center of the circle and the ahead point
	Vector2 avoidForce = ahead - m_obstacle->center;

	return avoidForce;
}