#pragma once
#include "Behaviour.h"
#include "NavMesh.h"
#include "Shadow.h"

class ReturnAction : public Behaviour
{
public:
	ReturnAction(GameObject* target, NavMesh* navMesh);
	~ReturnAction();

	// determines the path from the object to the target
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

private:
	// the object that is being targeted
	GameObject * m_target;
	// the navigational mesh that will be used to determine where the object can go
	NavMesh* m_navMesh;
};