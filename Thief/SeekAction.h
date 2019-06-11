#pragma once
#include "Behaviour.h"
#include "SeekForce.h"

class SeekAction : public Behaviour
{
public:
	SeekAction(GameObject* target);
	~SeekAction();

	// applies a seek force on the object towards the first node in its path
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

private:
	// the force used to move the object
	SeekForce m_force;
	// the object that is being targeted
	GameObject* m_target;
};