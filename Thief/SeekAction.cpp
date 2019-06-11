#include "SeekAction.h"
#include "NavMesh.h"

SeekAction::SeekAction(GameObject * target)
{
	m_target = target;
}
SeekAction::~SeekAction()
{
	m_target = nullptr;
	delete m_target;
}

// applies a seek force on the object towards the first node in its path
eBehaviourResult SeekAction::execute(GameObject * gameObject, float deltaTime)
{
	// ensures that the object can move
	gameObject->setLock(false);

	// checks if there are any more nodes to travel towards
	if (gameObject->smoothPath.empty())
	{
		return FAILURE;
	}

	// object position
	Vector2 objPos = { gameObject->getPosition().x, gameObject->getPosition().y };
	// target position
	Vector2 targPos = { m_target->getPosition().x, m_target->getPosition().y };

	if (objPos.distance(gameObject->smoothPath.front()) > 15.0f)
	{
		// sets the target of the force to the first node in the path
		m_force.setTargetPosition(gameObject->smoothPath.front());
		// if the object is close to the end destination then reduce the amount of force applied
		if (objPos.distance(targPos) <= 50.0f)
		{
			// adds a seek force to the object based on its distance to the destination
			gameObject->addForce(m_force.getForce(gameObject) * (objPos.distance(targPos) / 50.0f), deltaTime);
		}
		else
		{
			// adds the seek force to the object
			gameObject->addForce(m_force.getForce(gameObject), deltaTime);
		}
	}
	else
	{
		// removes the node because it has been reached
		gameObject->smoothPath.pop_front();
	}

	return SUCCESS;
}