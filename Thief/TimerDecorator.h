#pragma once
#include "Behaviour.h"
#include "Thief.h"

class TimerDecorator : public Behaviour
{
public:
	TimerDecorator(Behaviour* child, float duration, Thief* target);
	~TimerDecorator();

	// resets the timer
	void reset();

	// runs the child behaviour until the time is up
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

private:
	// the behaviour that has to wait for the timeout
	Behaviour * m_child;
	// the timer
	float m_timer;
	// the duration of the timeout
	float m_duration;
	// the object that is being targeted
	Thief* m_target;
};