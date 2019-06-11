#include "ReturnAction.h"

ReturnAction::ReturnAction(GameObject* target, NavMesh * navMesh)
{
	m_target = target;
	m_navMesh = navMesh;
}
ReturnAction::~ReturnAction()
{
	m_target = nullptr;
	delete m_target;
	m_navMesh = nullptr;
	delete m_navMesh;
}

// determines the path from the object to the target
eBehaviourResult ReturnAction::execute(GameObject * gameObject, float deltaTime)
{
	// finds the closest node to the object
	auto first = m_navMesh->findClosest(gameObject->getPosition().x, gameObject->getPosition().y);
	// finds the closest node to the target
	auto end = m_navMesh->findClosest(m_target->getPosition().x, m_target->getPosition().y);

	// determines the shortest path using A* pathfinding
	// stores the found path into the object's path
	gameObject->path = m_navMesh->aStar(first, end);
	// removes the first node because the object is already there
	gameObject->path.pop_front();

	// smooths the path
	NavMesh::smoothPath(gameObject->path, gameObject->smoothPath);

	return SUCCESS;
}