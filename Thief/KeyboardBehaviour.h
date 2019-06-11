#pragma once
#include <Input.h>
#include "Behaviour.h"
#include "SeekForce.h"
#include "FleeForce.h"

class KeyboardBehaviour : public Behaviour
{
public:
	KeyboardBehaviour() {}

	// moves the object based on the input
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

private:
	// used for moving towards a target
	SeekForce m_seek;
	// used for moving away from a target
	FleeForce m_flee;
};