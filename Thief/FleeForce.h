#pragma once
#include "SteeringForce.h"

class FleeForce : public SteeringForce
{
public:
	FleeForce();

	// sets the target position
	void setTargetPosition(Vector2 pos);

	// calculates a force that moves the velocity away from the target
	virtual Vector2 getForce(GameObject* gameObject);

private:
	Vector2 m_targPos;
};