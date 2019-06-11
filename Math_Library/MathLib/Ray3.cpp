#include "Ray3.h"

Ray3::Ray3()
{
	origin = 0.0f;
	direction = 0.0f;
	length = 0.0f;
}
//allows specific values to be passed in for the properties
Ray3::Ray3(const Vector3 & start, const Vector3 & dir, const float & l)
{
	origin = start;
	direction = dir;
	direction.normalise();
	length = l;
}
//allows specific values to be passed in for the properties
Ray3::Ray3(const float & sX, const float & sY, const float & sZ, const float & dX, const float & dY, const float & dZ, const float & l)
{
	origin.x = sX;
	origin.y = sY;
	origin.z = sZ;
	direction.x = dX;
	direction.y = dY;
	direction.z = dZ;
	direction.normalise();
	length = l;
}
Ray3::~Ray3()
{
}

//returns the minimum between 2 floats
float Ray3::min(const float & a, const float & b) const
{
	return (a < b) ? a : b;
}
//returns the maximum between 2 floats
float Ray3::max(const float & a, const float & b) const
{
	return (a > b) ? a : b;
}
//ensures that a specified value is within the min and max
float Ray3::clamp(const float & t, const float & a, const float & b) const
{
	return max(a, min(b, t));
}

//projects an arbitrary point onto the ray
Vector3 Ray3::closestPoint(const Vector3 & point) const
{
	//ray origin to arbitrary point
	auto p = point - origin;

	//project the point onto the ray and clamp by length
	float t = clamp(p.dot(direction), 0, length);

	//return position in direction of the ray
	return origin + direction * t;
}
//determines if a sphere intersects with the ray
//I stores the intersection point and R stores the reflection penetration
bool Ray3::intersects(const Sphere & sphere, Vector3 * I, Vector3 * R) const
{
	//ray origin to sphere center
	auto L = sphere.center - origin;

	//project sphere center onto the ray
	float t = L.dot(direction);

	//get square distance from sphere center to ray
	float dd = L.dot(L) - t * t;

	//subtract penetration amount from projected distance
	t -= sqrt(sphere.radius * sphere.radius - dd);

	//it intersects if within ray length
	if (t >= 0.0f && t <= length)
	{
		//store intersection point if requested
		if (I != nullptr)
		{
			*I = origin + direction * t;
		}
		return true;
	}

	//stores the reflection
	if (R != nullptr)
	{
		//get surface normal at intersection point
		auto N = ((origin + direction * t) - sphere.center);
		N /= sphere.radius;

		//get penetration vector
		auto P = direction * (length - t);

		//get penetration amount
		float p = P.dot(N);

		//get reflected vector
		*R = N * -2 * p + P;
	}

	//default no intersection
	return false;
}
//determines if a plane intersects with the ray
//I stores the intersection point and R stores the reflection penetration
bool Ray3::intersects(const Plane3 & plane, Vector3 * I, Vector3 * R) const
{
	//project ray direction onto plane normal to test if the ray is facing the plane
	//this should give a value between -1 and 1
	float t = direction.dot(plane.N);

	//must face the plane
	if (t > 0.0f)
	{
		return false;
	}

	//get distance of ray origin to the plane
	float d = origin.dot(plane.N) + plane.d;

	//check if ray is parallel with the plane
	//no intersection if parallel and not touching
	if (t == 0.0f && d != 0.0f)
	{
		return false;
	}

	//calculate distance along ray to plane
	t = d == 0.0f ? 0.0f : -(d / t);

	//intersects if within range
	if (t >= 0.0f && t <= length)
	{
		//store intersection point if requested
		if (I != nullptr)
		{
			*I = origin + direction * t;
		}

		//stores the reflection
		if (R != nullptr)
		{
			//get penetration vector
			auto P = direction * (length - t);
			//get penetration amount
			float p = P.dot(plane.N);
			//get reflected vector
			*R = plane.N * -2 * p + P;
		}

		return true;
	}

	//default no intersection
	return false;
}
//determines if a cube intersects with the ray
//I stores the intersection point and R stores the reflection penetration
bool Ray3::intersects(const AABB3 & aabb, Vector3 * I, Vector3 * R) const
{
	//get distances to each axis of the cube
	float xMin, xMax, yMin, yMax, zMin, zMax;

	//get min and max in the x-axis
	//check if the ray direction's x is facing the negative direction
	if (direction.x < 0.0f)
	{
		xMin = (aabb.maximum.x - origin.x) / direction.x;
		xMax = (aabb.minimum.x - origin.x) / direction.x;
	}
	else
	{
		xMin = (aabb.minimum.x - origin.x) / direction.x;
		xMax = (aabb.maximum.x - origin.x) / direction.x;
	}
	//get min and max in the y-axis
	//check if the ray direction's y is facing the negative direction
	if (direction.y < 0.0f)
	{
		yMin = (aabb.maximum.y - origin.x) / direction.y;
		yMax = (aabb.minimum.y - origin.x) / direction.y;
	}
	else
	{
		yMin = (aabb.minimum.y - origin.y) / direction.y;
		yMax = (aabb.maximum.y - origin.y) / direction.y;
	}
	//get min and max in the z-axis
	//check if the ray direction's z is facing the negative direction
	if (direction.z < 0.0f)
	{
		zMin = (aabb.maximum.z - origin.z) / direction.z;
		zMax = (aabb.minimum.z - origin.z) / direction.z;
	}
	else
	{
		zMin = (aabb.minimum.z - origin.z) / direction.z;
		zMax = (aabb.maximum.z - origin.z) / direction.z;
	}

	//ensure that there is an intersection
	if (xMin > yMax || xMin > zMax ||
		yMin > xMax || yMin > zMax ||
		zMin > xMax || zMin > yMax)
	{
		return false;
	}

	//the first contact is the largest of the mins
	float t = max(zMin, max(xMin, yMin));

	//intersects if within the range
	if (t >= 0.0f && t <= length)
	{
		//store intersection point if requested
		if (I != nullptr)
		{
			*I = origin + direction * t;
		}

		//stores the reflection
		if (R != nullptr)
		{
			//need to determine box side hit
			Vector3 N = {};
			if (t == xMin)
			{
				//horizontal normal
				if (direction.x < 0.0f)
				{
					//right side
					N = { 1.0f, 0.0f, 0.0f };
				}
				else
				{
					//left side
					N = { -1.0f, 0.0f, 0.0f };
				}
			}
			else if (t == yMin)
			{
				//vertical normal
				if (direction.y < 0.0f)
				{
					//top
					N = { 0.0f, 1.0f, 0.0f };
				}
				else
				{
					//bottom
					N = { 0.0f, -1.0f, 0.0f };
				}
			}
			else
			{
				//depth normal
				if (direction.z < 0.0f)
				{
					//front
					N = { 0.0f, 0.0f, 1.0f };
				}
				else
				{
					//back
					N = { 0.0f, 0.0f, -1.0f };
				}
			}

			//get penetration vector
			auto P = direction * (length - t);
			//get penetration amount
			float p = P.dot(N);
			//get reflected vector
			*R = N * -2 * p + P;
		}

		return true;
	}

	//not within the ray's range
	return false;
}