#pragma once
#include "Behaviour.h"

class SwapVelocityAction : public Behaviour
{
public:
	SwapVelocityAction() {}
	
	// swaps the velocity
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);
};