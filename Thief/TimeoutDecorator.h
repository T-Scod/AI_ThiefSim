#pragma once
#include "Behaviour.h"

class TimeoutDecorator : public Behaviour
{
public:
	TimeoutDecorator(Behaviour* child, float duration);
	~TimeoutDecorator();

	// resets the timer
	void reset();

	// runs the child behaviour when the timeout is finished
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

private:
	// the behaviour that has to wait for the timeout
	Behaviour * m_child;
	// the timer
	float m_timer;
	// the duration of the timeout
	float m_duration;
};