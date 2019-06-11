#include "TimeoutDecorator.h"

TimeoutDecorator::TimeoutDecorator(Behaviour * child, float duration)
{
	m_child = child;
	m_duration = duration;
	m_timer = m_duration;
}
TimeoutDecorator::~TimeoutDecorator()
{
	m_child = nullptr;
	delete m_child;
}

// resets the timer
void TimeoutDecorator::reset()
{
	m_timer = m_duration;
}

// runs the child behaviour when the timeout is finished
eBehaviourResult TimeoutDecorator::execute(GameObject * gameObject, float deltaTime)
{
	// decrements the timer
	m_timer -= deltaTime;
	// checks if the timer has run out
	if (m_timer <= 0.0f)
	{
		// resets the timer
		reset();
		// runs the child behaviour
		return m_child->execute(gameObject, deltaTime);
	}
	else
	{
		// if there is still time left to wait then return failure
		return FAILURE;
	}
}