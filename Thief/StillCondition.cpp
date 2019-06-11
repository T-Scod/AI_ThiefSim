#include "StillCondition.h"

StillCondition::StillCondition()
{
	m_timer = 0.0f;
	m_pos = 0.0f;
}

// checks if the object has been relatively stationary for too long
eBehaviourResult StillCondition::execute(GameObject * gameObject, float deltaTime)
{
	// checks if the difference in position per frame is less than 0.5
	if (gameObject->getPosition().distance(m_pos) < 0.5f)
	{
		// sets the previous position to the current position
		m_pos = gameObject->getPosition();
		// checks if the object has been there long
		if (m_timer <= 5.0f)
		{
			// increments the ammount of time the object has been still
			m_timer += deltaTime;
			return FAILURE;
		}
		else
		{
			// resets the timer
			m_timer = 0.0f;
			// the object is not moving
			return SUCCESS;
		}
	}
	else
	{
		// resets the timer because the object is moving
		m_timer = 0.0f;
		// sets the previous position to the current position
		m_pos = gameObject->getPosition();
		return FAILURE;
	}
}