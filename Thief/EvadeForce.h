#pragma once
#include "SteeringForce.h"

class EvadeForce : public SteeringForce
{
public:
	EvadeForce();

	// sets the target position
	// should be the sum of the position of the target object and the target's velocity
	void setTargetPosition(Vector2 pos);

	// calculates a force that moves the velocity away from where the target is heading
	virtual Vector2 getForce(GameObject* gameObject);

private:
	Vector2 m_targPos;
};