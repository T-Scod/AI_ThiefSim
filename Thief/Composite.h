#pragma once
#include "Behaviour.h"

// abstract base class for sequence and selector nodes
class Composite : public Behaviour
{
public:
	~Composite()
	{
		for (auto child : childBehaviours)
		{
			child = nullptr;
			delete child;
		}
	}

	// collection of all the nodes that are children of the composite node
	std::vector<Behaviour*> childBehaviours;

	// adds a behaviour to the tree
	virtual void addChild(Behaviour* child)
	{
		childBehaviours.push_back(child);
	}
	// removes a behaviour from the tree
	virtual void removeChild(Behaviour* child)
	{
		// iterates through the children to find the behaviour
		for (unsigned int i = 0; i < childBehaviours.size(); i++)
		{
			// if the child is found then move all the nodes
			if (childBehaviours[i] == child)
			{
				// iterates from the child node onwards not including the last item as it will be removed
				for (int j = i; j < childBehaviours.size() - 1; j++)
				{
					// moves the next item into the current position
					childBehaviours[j] = childBehaviours[j + 1];
				}
				// stops looking for the node
				break;
			}
		}
	}

	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime) = 0;
};