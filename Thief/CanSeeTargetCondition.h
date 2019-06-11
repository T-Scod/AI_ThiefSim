#pragma once
#include "Behaviour.h"
#include "TimeoutDecorator.h"
#include "TimerDecorator.h"
#include "Shadow.h"

class CanSeeTargetCondition : public Behaviour
{
public:
	CanSeeTargetCondition(GameObject* target, TimeoutDecorator* timeout, TimerDecorator* timer, Shadow* shadow);
	~CanSeeTargetCondition();

	// checks if the object can see the target and resets the timer if not
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

private:
	// the object that is being targeted
	GameObject * m_target;
	// the timerout timer that will be reset
	TimeoutDecorator* m_timeout;
	// the timer that will be reset
	TimerDecorator* m_timer;
	// the afterimage that appears if the object loses sight of the target
	Shadow* m_after;
};