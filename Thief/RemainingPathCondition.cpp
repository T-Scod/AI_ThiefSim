#include "RemainingPathCondition.h"

RemainingPathCondition::RemainingPathCondition(Thief* target, Shadow * shadow)
{
	m_after = shadow;
	m_target = target;
}
RemainingPathCondition::~RemainingPathCondition()
{
	m_after = nullptr;
	delete m_after;
	m_target = nullptr;
	delete m_target;
}

// checks if the object has a path
eBehaviourResult RemainingPathCondition::execute(GameObject * gameObject, float deltaTime)
{
	if (gameObject->smoothPath.empty())
	{
		return FAILURE;
	}
	else
	{
		if (!m_after->getVisible())
		{
			// makes the shadow visible and sets its properties to the target's
			m_after->setVisible(true);
			m_after->setTransform(m_target->getTransform());
		}
		return SUCCESS;
	}
}