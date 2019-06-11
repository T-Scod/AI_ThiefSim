#include "PatrolAction.h"

PatrolAction::PatrolAction(GameObject* target)
{
	m_target = target;
}
PatrolAction::~PatrolAction()
{
	m_target = nullptr;
	delete m_target;
}

// moves around the target in a triangle
eBehaviourResult PatrolAction::execute(GameObject * gameObject, float deltaTime)
{
	// ensures that the object can move
	gameObject->setLock(false);

	// target position
	Vector2 targPos = { m_target->getPosition().x, m_target->getPosition().y };
	// point north of target
	Vector2 targPoint1 = { 0.0f, m_target->getBubble().radius };
	// point south-west of target
	Vector2 targPoint2 = { targPoint1.x * cosf(2.0944f) - targPoint1.y * sinf(2.0944f), targPoint1.x * sinf(2.0944f) + targPoint1.y * cosf(2.0944f) };
	// point south-east of target
	Vector2 targPoint3 = { targPoint1.x * cosf(-2.0944f) - targPoint1.y * sinf(-2.0944f), targPoint1.x * sinf(-2.0944f) + targPoint1.y * cosf(-2.0944f) };
	// position of this object
	Vector2 objPos = { gameObject->getPosition().x, gameObject->getPosition().y };

	// checks which point to seek towards
	switch (m_point)
	{
	case 0:
		// sets the target for the force
		m_force.setTargetPosition(targPoint1 + targPos);
		// checks if the object has reached the target
		if (objPos.distance(targPoint1 + targPos) <= 15.0f)
		{
			// changes the target
			m_point = 1;
		}
		break;
	case 1:
		// sets the target for the force
		m_force.setTargetPosition(targPoint2 + targPos);
		// checks if the object has reached the target
		if (objPos.distance(targPoint2 + targPos) <= 15.0f)
		{
			// changes the target
			m_point = 2;
		}
		break;
	case 2:
		// sets the target for the force
		m_force.setTargetPosition(targPoint3 + targPos);
		// checks if the object has reached the target
		if (objPos.distance(targPoint3 + targPos) <= 15.0f)
		{
			// changes the target
			m_point = 0;
		}
		break;
	}

	// adds the seek force to the object
	gameObject->addForce(m_force.getForce(gameObject), deltaTime);
	return SUCCESS;
}