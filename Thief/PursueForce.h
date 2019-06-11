#pragma once
#include "SteeringForce.h"

class PursueForce : public SteeringForce
{
public:
	PursueForce();

	// sets the target position
	// should be the sum of the position of the target object and the target's velocity
	void setTargetPosition(Vector2 pos);

	// calculates a force that moves the velocity towards the target's velocity
	virtual Vector2 getForce(GameObject* gameObject);

private:
	Vector2 m_targPos;
};