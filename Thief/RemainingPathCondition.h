#pragma once
#include "Behaviour.h"
#include "Shadow.h"
#include "Thief.h"

class RemainingPathCondition : public Behaviour
{
public:
	RemainingPathCondition(Thief* m_target, Shadow* shadow);
	~RemainingPathCondition();

	// checks if the object has a path
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

private:
	// the afterimage that appears if the object loses sight of the target
	Shadow * m_after;
	// the object being targeted
	Thief* m_target;
};