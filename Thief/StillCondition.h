#pragma once
#include "Behaviour.h"

class StillCondition : public Behaviour
{
public:
	StillCondition();

	// checks if the object has been relatively stationary for too long
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

private:
	// used to check how long an object has been still for
	float m_timer;
	// stores the previous position
	Vector3 m_pos;
};