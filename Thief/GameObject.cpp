#include "GameObject.h"
#include "Behaviour.h"

GameObject::GameObject(const char* filename)
{
	m_velocity = 0.0f;
	m_maxVelocity = 1.0f;
	m_maxForce = 1.0f;
	m_lock = false;
	m_chased = false;

	m_texture = new aie::Texture(filename);

	m_ahead = Ray2();
	m_angle = 0.0f;
}
GameObject::~GameObject()
{
	for (auto child : m_behaviours)
	{
		child = nullptr;
		delete child;
	}
	for (auto node : path)
	{
		node = nullptr;
		delete node;
	}
	m_texture = nullptr;
	delete m_texture;
}

// sets the scale
void GameObject::setScale(const float & width, const float & height)
{
	m_obj[0] = { width, height, 0.0f };
}
// modifies an existing scale
void GameObject::scale(const float & width, const float & height)
{
	m_obj.scale(width, height, 0.0f);
}

// sets a rotation
void GameObject::setRotation(const float & radians)
{
	Matrix3 transform = m_obj;
	transform.setRotateZ(radians);

	m_obj[0] = transform[0];
	m_obj[1] = transform[1];
}
// modifies an existing rotation
void GameObject::rotate(const float & radians)
{
	m_obj.rotateZ(radians);
}

// sets the position of the object to the parameters
void GameObject::setPosition(const float& x, const float& y)
{
	m_obj[2] = { x, y, 1.0f };
	// sets the range's position to be wherever the object's is
	m_range.center = { m_obj[2].x, m_obj[2].y };
	// sets the bubble's position to be wherever the object's is
	m_bubble.center = { m_obj[2].x, m_obj[2].y };
}
// increments the current position of the object by the parameters
void GameObject::translate(const float& x, const float& y)
{
	m_obj.translate(x, y);
	// sets the bubbles position to be wherever the player is
	m_bubble.center = { m_obj[2].x, m_obj[2].y };
}

// sets the velocity of the object to the parameters
void GameObject::setVelocity(Vector2 v)
{
	m_velocity = v;
}
// sets the maximum velocity of the object
void GameObject::setMaxVelocity(float max)
{
	m_maxVelocity = max;
}

// sets the lock status
void GameObject::setLock(bool lock)
{
	m_lock = lock;
}

// sets the identity of this game object
void GameObject::setIdentity(int id)
{
	m_id = id;
}

// sets the chased status
void GameObject::setChased(bool chase)
{
	m_chased = chase;
}

// add a behaviour
void GameObject::addBehaviour(Behaviour * behaviour)
{
	m_behaviours.push_back(behaviour);
}

//update game object and execute behaviours
void GameObject::update(float deltaTime)
{
	for (auto b : m_behaviours)
	{
		b->execute(this, deltaTime);
	}

	// ensures that the velocity is within the maximum
	if (m_velocity.magnitude() > m_maxVelocity)
	{
		m_velocity.normalise();
		m_velocity *= m_maxVelocity;
	}

	// only moves the object if the lock is not on
	if (!m_lock)
	{
		// moves the object in the direction of the velocity
		translate(100.0f * m_velocity.x * deltaTime, 100.0f * m_velocity.y * deltaTime);
	}

	// moves the object out of objects
	collision();

	// sets the rotation of the object to match the direction of the velocity
	Vector3 rot = { m_velocity.x, m_velocity.y, 0.0f };
	if (rot.magnitude() > 0.0f)
	{
		float angle = rot.angleBetween({ 0.0f, 1.0f, 0.0f });
		setRotation(-angle);
	}

	// sets the ray's properties to match the object
	m_ahead.origin = { m_obj[2].x, m_obj[2].y };
	if (m_velocity.magnitude() > 0.0f)
	{
		m_ahead.direction = m_velocity;
		m_ahead.direction.normalise();
	}
	else
	{
		m_ahead.direction = { m_obj[1].x, m_obj[1].y };
		m_ahead.direction.normalise();
	}

	// used to determine the rotated line of sight
	Vector2 sight = m_ahead.direction;
	// rotates the vector to the right by the angle
	sight = { sight.x * cosf(-m_angle) - sight.y * sinf(-m_angle), sight.x * sinf(-m_angle) + sight.y * cosf(-m_angle) };
	sight.normalise();
	// the reach of the sight
	m_right.reach = m_ahead.origin + sight * m_ahead.length;
	// sets up the plane based on the line of sight
	m_right.plane = Plane2(m_ahead.origin, m_right.reach);
	// resets the line of sight so that it can be rotated to the left
	sight = m_ahead.direction;
	// rotates the vector to the left by the angle
	sight = { sight.x * cosf(m_angle) - sight.y * sinf(m_angle), sight.x * sinf(m_angle) + sight.y * cosf(m_angle) };
	sight.normalise();
	// the reach of the sight
	m_left.reach = m_ahead.origin + sight * m_ahead.length;
	// sets up the plane based on the line of sight
	m_left.plane = Plane2(m_left.reach, m_ahead.origin);

	// sets the range's position to be wherever the object is
	m_range.center = { m_obj[2].x, m_obj[2].y };
	// sets the bubble's position to be wherever the object is
	m_bubble.center = { m_obj[2].x, m_obj[2].y };
}

// adds a force to the current velocity to rotate the velocity
void GameObject::addForce(Vector2 force, float deltaTime)
{
	// ensures that the force is within the range
	if (force.magnitude() > m_maxForce)
	{
		force.normalise();
	}
	m_velocity += force * deltaTime;
}

// sets the length of the ray
void GameObject::setLength(const float & length)
{
	m_ahead.length = length;
}
// sets the angle between the side rays and the ahead ray
void GameObject::setAngle(const float & radians)
{
	m_angle = radians;
}
// sets the radius of the range circle
void GameObject::setRangeSize(const float & rad)
{
	m_range.radius = rad;
}

// sets the radius of the bubble
void GameObject::setBubbleSize(const float & rad)
{
	m_bubble.radius = rad;
}

// sets the collection of obstacles
void GameObject::setObstacles(std::vector<AABB2> obs)
{
	m_obstacles = obs;
}
// moves the player away from obsticals
void GameObject::collision()
{
	for (auto o : m_obstacles)
	{
		if (m_bubble.overlaps(o))
		{
			// the player's position
			Vector2 pos = { m_obj[2].x, m_obj[2].y };

			// checks if the player intersects with the bottom left corner
			if (pos.x < o.minimum.x && pos.x + m_bubble.radius > o.minimum.x && pos.y < o.minimum.y && pos.y + m_bubble.radius > o.minimum.y)
			{
				// bottom left corner
				Vector2 corner = { o.minimum.x, o.minimum.y };
				// vector between corner and player
				corner -= pos;
				setPosition(o.minimum.x - corner.x * 1.1f, o.minimum.y - corner.y * 1.1f);
			}
			// checks if the player intersects with the top left corner
			else if (pos.x < o.minimum.x && pos.x + m_bubble.radius > o.minimum.x && pos.y > o.maximum.y && pos.y - m_bubble.radius < o.maximum.y)
			{
				// top left corner
				Vector2 corner = { o.minimum.x, o.maximum.y };
				// vector between corner and player
				corner -= pos;
				setPosition(o.minimum.x - corner.x * 1.1f, o.maximum.y - corner.y * 1.1f);
			}
			// checks if the player intersects with the bottom right corner
			else if (pos.x > o.maximum.x && pos.x - m_bubble.radius < o.maximum.x && pos.y < o.minimum.y && pos.y + m_bubble.radius > o.minimum.y)
			{
				// bottom right corner
				Vector2 corner = { o.maximum.x, o.minimum.y };
				// vector between corner and player
				corner -= pos;
				setPosition(o.maximum.x - corner.x * 1.1f, o.minimum.y - corner.y * 1.1f);
			}
			// checks if the player intersects with the top right corner
			else if (pos.x > o.maximum.x && pos.x - m_bubble.radius < o.maximum.x && pos.y > o.maximum.y && pos.y - m_bubble.radius < o.maximum.y)
			{
				// top right corner
				Vector2 corner = { o.maximum.x, o.maximum.y };
				// vector between corner and player
				corner -= pos;
				setPosition(o.maximum.x - corner.x * 1.1f, o.maximum.y - corner.y * 1.1f);
			}
			// checks if the player intersects with the left side of the AABB
			else if (pos.x < o.minimum.x && pos.x + m_bubble.radius > o.minimum.x)
			{
				setPosition(o.minimum.x - m_bubble.radius - 0.1f, pos.y);
			}
			// checks if the player intersects with the right side of the AABB
			else if (pos.x > o.maximum.x && pos.x - m_bubble.radius < o.maximum.x)
			{
				setPosition(o.maximum.x + m_bubble.radius + 0.1f, pos.y);
			}
			// checks if the player intersects with the bottom side of the AABB
			else if (pos.y < o.minimum.y && pos.y + m_bubble.radius > o.minimum.y)
			{
				setPosition(pos.x, o.minimum.y - m_bubble.radius - 0.1f);
			}
			// checks if the player intersects with the top side of the AABB
			else if (pos.y > o.maximum.y && pos.y - m_bubble.radius < o.maximum.y)
			{
				setPosition(pos.x, o.maximum.y + m_bubble.radius + 0.1f);
			}
		}
	}
}

// checks if the object is between the planes
bool GameObject::see(GameObject * gameObject)
{
	// contains the object's bubble
	Circle obj = gameObject->getBubble();

	// checks if the object overlaps the range and is on the front side of the planes
	if (m_range.overlaps(obj) == true && m_right.plane.testSide(obj) == 1 && m_left.plane.testSide(obj) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}