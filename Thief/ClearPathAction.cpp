#include "ClearPathAction.h"

// clears the object's path
eBehaviourResult ClearPathAction::execute(GameObject * gameObject, float deltaTime)
{
	gameObject->path.clear();
	gameObject->smoothPath.clear();
	return SUCCESS;
}