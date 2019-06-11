#include "CloseToTargetCondition.h"

CloseToTargetCondition::CloseToTargetCondition(GameObject* target, float range)
{
	m_target = target;
	m_range = range;
}
CloseToTargetCondition::~CloseToTargetCondition()
{
	m_target = nullptr;
	delete m_target;
}

// checks if the target is within the range of this object
eBehaviourResult CloseToTargetCondition::execute(GameObject * gameObject, float deltaTime)
{
	// the position of the object
	Vector2 objPos = { gameObject->getPosition().x, gameObject->getPosition().y };
	// the position of the target
	Vector2 targPos = { m_target->getPosition().x, m_target->getPosition().y };

	// checks if the distance between the target and the object is less than the range
	if (objPos.distance(targPos) <= m_range)
	{
		// the target is within range
		return SUCCESS;
	}
	// the target is not in range
	return FAILURE;
}