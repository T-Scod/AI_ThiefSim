#include "TimerDecorator.h"

TimerDecorator::TimerDecorator(Behaviour * child, float duration, Thief* target)
{
	m_child = child;
	m_duration = duration;
	m_timer = 0.0f;
	m_target = target;
}
TimerDecorator::~TimerDecorator()
{
	m_child = nullptr;
	delete m_child;
	m_target = nullptr;
	delete m_target;
}

// resets the timer
void TimerDecorator::reset()
{
	m_timer = 0.0f;
}

// runs the child behaviour until the time is up
eBehaviourResult TimerDecorator::execute(GameObject * gameObject, float deltaTime)
{
	// increments the timer
	m_timer += deltaTime;
	// checks if the timer has run out
	if (m_timer <= m_duration)
	{
		// runs the child behaviour
		return m_child->execute(gameObject, deltaTime);
	}
	else
	{
		// resets the timer if it goes above the duration
		reset();
		// sets the target to not being chased
		gameObject->setChased(false);
		// ensures that the object can move
		gameObject->setLock(false);
		return FAILURE;
	}
}