#pragma once
#include "Behaviour.h"

class ClearPathAction : public Behaviour
{
public:
	ClearPathAction() {}
	
	// clears the object's path
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);
};