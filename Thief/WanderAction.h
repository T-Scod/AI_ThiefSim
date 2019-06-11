#pragma once
#include "Behaviour.h"
#include "WanderForce.h"

class WanderAction : public Behaviour
{
public:
	WanderAction();

	// applies a wander force to the object without changing its position
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

private:
	WanderForce m_force;
};