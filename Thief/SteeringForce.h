#pragma once
#include <Vector2.h>
class GameObject;

// abstract class
class SteeringForce
{
public:
	// calculates the force
	virtual Vector2 getForce(GameObject* gameObject) = 0;
};