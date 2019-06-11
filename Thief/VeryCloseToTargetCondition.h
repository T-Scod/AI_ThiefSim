#pragma once
#include "Behaviour.h"

class VeryCloseToTargetCondition : public Behaviour
{
public:
	VeryCloseToTargetCondition(GameObject* target, float range);
	~VeryCloseToTargetCondition();

	// checks if the object is within the range and resets a timer
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

private:
	// the distance that is being checked against
	float m_range;
	// the object that is being targeted
	GameObject* m_target;
};