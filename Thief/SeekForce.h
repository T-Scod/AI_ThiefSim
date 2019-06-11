#pragma once
#include "SteeringForce.h"

class SeekForce : public SteeringForce
{
public:
	SeekForce();

	// sets the target position
	void setTargetPosition(Vector2 pos);

	// calculates a force that moves the velocity towards the target
	virtual Vector2 getForce(GameObject* gameObject);

private:
	Vector2 m_targPos;
};