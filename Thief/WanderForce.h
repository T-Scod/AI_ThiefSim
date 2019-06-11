#pragma once
#include "SteeringForce.h"
#include <Circle.h>
#define PI (asinf(1) * 2)

class WanderForce : public SteeringForce
{
public:
	WanderForce();
	WanderForce(Circle circle, float dist, int jitter);

	// calculates a force that moves the velocity by a displacement around a circle
	virtual Vector2 getForce(GameObject* gameObject);

private:
	// calculates the angle of the displacement and randomises the wander angle
	Vector2 setAngle();

private:
	// a circle that will be positioned in front of the object
	Circle m_circle;
	// the distance between the object and the circle
	float m_distance;
	// the variation in the choosing of a random point on the circle (in degrees)
	int m_jitterAmount;
	// the angle that is randomly chosen
	float m_wanderAngle;
};

