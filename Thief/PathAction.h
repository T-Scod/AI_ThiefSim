#pragma once
#include "Behaviour.h"
#include "Thief.h"
#include "NavMesh.h"

class PathAction : public Behaviour
{
public:
	PathAction(Thief* target, NavMesh* navMesh);
	~PathAction();

	// determines the path from the object to the target
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

private:
	// the object that is being targeted
	Thief * m_target;
	// the navigational mesh that will be used to determine where the object can go
	NavMesh* m_navMesh;
};