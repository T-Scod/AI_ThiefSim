#pragma once
#include "Behaviour.h"

class CloseToTargetCondition : public Behaviour
{
public:
	CloseToTargetCondition(GameObject* target, float range);
	~CloseToTargetCondition();

	// checks if the object is within the range
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

private:
	// the distance that is being checked against
	float m_range;
	// the object that is being targeted
	GameObject* m_target;
};