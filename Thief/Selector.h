#pragma once
#include "Composite.h"

// OR node for running a list of behaviours consecutively until one succeeds
class Selector : public Composite
{
public:
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime)
	{
		// iterates through all child behaviours
		for (auto child : childBehaviours)
		{
			// if any of the child behaviours are successful then return success
			if (child->execute(gameObject, deltaTime) == eBehaviourResult::SUCCESS)
			{
				return eBehaviourResult::SUCCESS;
			}
		}
		// if none of the child behaviours are successful then return failure
		return eBehaviourResult::FAILURE;
	}
};