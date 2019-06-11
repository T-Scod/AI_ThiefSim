#pragma once
#include "Composite.h"

// AND node for running a list of behaviours consecutively until one fails
class Sequence : public Composite
{
public:
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime)
	{
		// iterates through all child behaviours
		for (auto child : childBehaviours)
		{
			// if any of the child behaviours are unsuccessful then return failure
			if (child->execute(gameObject, deltaTime) == eBehaviourResult::FAILURE)
			{
				return eBehaviourResult::FAILURE;
			}
		}
		// if none of the child behaviours are unsuccessful then return success
		return eBehaviourResult::SUCCESS;
	}
};