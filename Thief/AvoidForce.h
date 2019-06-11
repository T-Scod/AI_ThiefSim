#pragma once
#include "SteeringForce.h"
#include <Circle.h>

class AvoidForce : public SteeringForce
{
public:
	AvoidForce();

	// sets the obstacle
	void setObstacle(Circle* circle);
	
	// calculates the force that will move the object away from the obstacle
	virtual Vector2 getForce(GameObject* gameObject);

private:
	Circle * m_obstacle;
};

