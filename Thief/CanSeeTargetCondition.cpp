#include "CanSeeTargetCondition.h"

CanSeeTargetCondition::CanSeeTargetCondition(GameObject* target, TimeoutDecorator* timeout, TimerDecorator* timer, Shadow* shadow)
{
	m_target = target;
	m_timeout = timeout;
	m_timer = timer;
	m_after = shadow;
}
CanSeeTargetCondition::~CanSeeTargetCondition()
{
	m_target = nullptr;
	delete m_target;
	m_timeout = nullptr;
	delete m_timeout;
	m_timer = nullptr;
	delete m_timer;
	m_after = nullptr;
	delete m_after;
}

// checks if the object can see the target
eBehaviourResult CanSeeTargetCondition::execute(GameObject * gameObject, float deltaTime)
{
	// checks if the object's line of sight collides with the target
	if (gameObject->see(m_target) == true)
	{
		// resets the timer
		m_timer->reset();
		// ensures that the object can move
		gameObject->setLock(false);
		// sets the status of the object to chasing
		gameObject->setChased(true);
		// makes the shadow invisible
		m_after->setVisible(false);
		// if it is then return success
		return SUCCESS;
	}

	//resets the timer
	m_timeout->reset();
	// if not then return failure
	return FAILURE;
}