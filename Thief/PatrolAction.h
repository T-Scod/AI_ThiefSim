#pragma once
#include "Behaviour.h"
#include "SeekForce.h"
#include "Shadow.h"

class PatrolAction : public Behaviour
{
public:
	PatrolAction(GameObject* target);
	~PatrolAction();

	// moves around the target in a triangle
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

private:
	// the object that will be patrolled
	GameObject * m_target;
	// used to seek towards the waypoints
	SeekForce m_force;
	//  used to determine which point to seek towards
	int m_point = 0;
};