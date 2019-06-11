#include "SwapVelocityAction.h"

// swaps the velocity
eBehaviourResult SwapVelocityAction::execute(GameObject * gameObject, float deltaTime)
{
	// sets the velocity to the inverse of the current velocity
	gameObject->setVelocity(-gameObject->getVelocity());
	return SUCCESS;
}