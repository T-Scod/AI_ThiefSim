#pragma once
#include "Behaviour.h"
#include "Thief.h"
#include "Shadow.h"

class RecentlyChasedCondition : public Behaviour
{
public:
	RecentlyChasedCondition(Thief* target, Shadow* shadow);
	~RecentlyChasedCondition();

	// checks if the target was recently chased
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

private:
	// the object that is being targeted
	Thief * m_target;
	// the afterimage that appears if the object loses sight of the target
	Shadow* m_after;
};