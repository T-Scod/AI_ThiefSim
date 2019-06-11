#include "RecentlyChasedCondition.h"

RecentlyChasedCondition::RecentlyChasedCondition(Thief * target, Shadow* shadow)
{
	m_target = target;
	m_after = shadow;
}
RecentlyChasedCondition::~RecentlyChasedCondition()
{
	m_target = nullptr;
	delete m_target;
	m_after = nullptr;
	delete m_after;
}

// checks if the target was recently chased
eBehaviourResult RecentlyChasedCondition::execute(GameObject * gameObject, float deltaTime)
{
	if (gameObject->getChased())
	{
		// sets the shadow to be invisible
		m_after->setVisible(false);
		// target was chased
		return SUCCESS;
	}

	// target was not chased
	return FAILURE;
}