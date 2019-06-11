#include "KeyboardBehaviour.h"

// moves the object based on the input
eBehaviourResult KeyboardBehaviour::execute(GameObject * gameObject, float deltaTime)
{
	// checks if there is a valid object to move
	if (gameObject == nullptr)
	{
		return eBehaviourResult::FAILURE;
	}

	aie::Input* input = aie::Input::getInstance();

	//contains the mouse position
	Vector3 mousePos = { (float)input->getMouseX(), (float)input->getMouseY(), 0.0f };
	Vector3 offset = { mousePos - gameObject->getPosition() };
	//angle between the offset and initial rotation
	float angle = offset.angleBetween({ 0.0f, 1.0f, 0.0f });
	//set the rotation of the object
	gameObject->setRotation(-angle);

	// if w is pressed then seek towards the mouse
	if (input->isKeyDown(aie::INPUT_KEY_W))
	{
		// sets the target of the seek to the mouse
		m_seek.setTargetPosition({ mousePos.x, mousePos.y });
		// adds the seek force to the object
		gameObject->addForce(m_seek.getForce(gameObject), deltaTime);
	}
	else if (input->isKeyUp(aie::INPUT_KEY_W))
	{
		gameObject->setVelocity(gameObject->getVelocity() * 0.99f);
	}
	// if s is pressed then flee from the mouse
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		// sets the target of the flee to the mouse
		m_flee.setTargetPosition({ mousePos.x, mousePos.y });
		// adds the flee force to the object
		gameObject->addForce(m_flee.getForce(gameObject), deltaTime);
	}
	else if (input->isKeyUp(aie::INPUT_KEY_S))
	{
		gameObject->setVelocity(gameObject->getVelocity() * 0.99f);
	}
	// if a is pressed then seek clockwise in a circle around the mouse
	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		// going to become the rotated mouse position
		Vector3 rotMouse = offset;
		// 90 degrees
		angle = asinf(1.0f);
		// rotates the vector by 90 degrees
		rotMouse = { rotMouse.x * cosf(angle) - rotMouse.y * sinf(angle), rotMouse.x * sinf(angle) + rotMouse.y * cosf(angle) };
		// moves the offset relative to the object
		rotMouse += gameObject->getPosition();
		// sets the target of the seek to the perpendicular offset of the mouse
		m_seek.setTargetPosition({ rotMouse.x, rotMouse.y });
		// adds the seek force to the object
		gameObject->addForce(m_seek.getForce(gameObject), deltaTime);
	}
	// if d is pressed then seek anti-clockwise in a circle around the mouse
	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		// going to become the rotated mouse position
		Vector3 rotMouse = offset;
		// 90 degrees
		angle = asinf(1.0f);
		// rotates the vector by 90 degrees
		rotMouse = { rotMouse.x * cosf(-angle) - rotMouse.y * sinf(-angle), rotMouse.x * sinf(-angle) + rotMouse.y * cosf(-angle) };
		// moves the offset relative to the object
		rotMouse += gameObject->getPosition();
		// sets the target of the seek to the perpendicular offset of the mouse
		m_seek.setTargetPosition({ rotMouse.x, rotMouse.y });
		// adds the seek force to the object
		gameObject->addForce(m_seek.getForce(gameObject), deltaTime);
	}

	return eBehaviourResult::SUCCESS;
}