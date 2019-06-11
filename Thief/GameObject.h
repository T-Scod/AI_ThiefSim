#pragma once
#include <vector>
#include <Matrix3.h>
#include <Ray2.h>
#include <Plane2.h>
#include <Circle.h>
#include <list>
#include <Texture.h>

class Behaviour;
class Node;

class GameObject
{
public:
	GameObject() {}
	GameObject(const char* filename);
	virtual ~GameObject();

	// returns the texture
	aie::Texture* getTexture() { return m_texture; }
	// returns the matrix
	Matrix3 getTransform() { return m_obj; }

	// scale functions
	void setScale(const float& width, const float& height);
	void scale(const float& width, const float& height);
	Vector3 getScale() { return m_obj[0]; }
	// rotation functions
	void setRotation(const float& radians);
	void rotate(const float& radians);
	Vector3 getRotation() { return m_obj[1]; }
	// position functions
	void setPosition(const float& x, const float& y);
	void translate(const float& x, const float& y);
	Vector3 getPosition() { return m_obj[2]; }

	// velocity functions
	void setVelocity(Vector2 v);
	Vector2 getVelocity() { return m_velocity; }
	void setMaxVelocity(float max);
	float getMaxVelocity() { return m_maxVelocity; }

	// sets the lock status
	void setLock(bool lock);
	// sets the identity of this game object
	void setIdentity(int id);
	// returns the identity of this game object]
	int getIdentity() { return m_id; }
	// sets the chased status
	void setChased(bool chase);
	// returns the chase status
	bool getChased() { return m_chased; }

	// add a behaviour
	void addBehaviour(Behaviour* behaviour);

	// update game object and execute behaviours
	virtual void update(float deltaTime);

	// adds a force to the current velocity to rotate the velocity
	void addForce(Vector2 force, float deltaTime);

public: /* used for collision */
	// contains the plane and the point where it stops
	struct Sight
	{
		Plane2 plane;
		Vector2 reach;
	};

	// returns the ray
	Ray2 getRay() { return m_ahead; }
	// sets the length of the ray
	void setLength(const float& length);
	// sets the angle between the side rays and the ahead ray
	void setAngle(const float& radians);
	// returns the right plane
	Sight getRight() { return m_right; }
	// returns the left plane
	Sight getLeft() { return m_left; }
	// returns the range circle
	Circle getRange() { return m_range; }
	// sets the radius of the range circle
	void setRangeSize(const float& rad);

	// returns the bubble
	Circle getBubble() { return m_bubble; }
	// sets the radius of the bubble
	void setBubbleSize(const float& rad);
	// sets the collection of obstacles
	void setObstacles(std::vector<AABB2> obs);
	// moves the player away from obsticals
	void collision();

	// checks if the object is between the planes
	bool see(GameObject* gameObject);

public: /* used for nav mesh */
	// these are used by the NavMesh behaviours
	std::list<Vector2> smoothPath;
	std::list<Node*> path;

protected:
	// the direction that the object translates each update
	Vector2 m_velocity;
	// the maximum magnitude of velocity
	float m_maxVelocity;
	// the maximum magnitude of force
	float m_maxForce;

	// prevents the object from moving
	bool m_lock;
	// used to help identify which game object this is
	int m_id;
	// used to determine if the object recently chased something
	bool m_chased;

	// will be used for the scale, rotation and position of the object
	Matrix3 m_obj = Matrix3::identity;
	// texture of the object
	aie::Texture* m_texture;

	// contains all of the behaviours assigned to the object
	std::vector<Behaviour*> m_behaviours;

protected: /* used for collision */
	// used to check for collision
	Ray2 m_ahead;
	// the angle between the side rays and the ahead ray
	float m_angle;
	
	// used to check if an object is within sight
	Sight m_right;
	// used to check if an object is within sight
	Sight m_left;
	// used to check the area between the two sights
	Circle m_range;

	// the object's personal space
	Circle m_bubble;
	// a collection of obstacles from the nav mesh
	std::vector<AABB2> m_obstacles;
};