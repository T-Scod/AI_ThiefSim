#include "Ray2.h"
#include <typeinfo>

Ray2::Ray2()
{
	origin = 0.0f;
	direction = 0.0f;
	length = 0.0f;
}
//allows specific values to be passed in for the properties
Ray2::Ray2(const Vector2 & start, const Vector2 & dir, const float & l)
{
	origin = start;
	direction = dir;
	direction.normalise();
	length = l;
}
//allows specific values to be passed in for the properties
Ray2::Ray2(const float & sX, const float & sY, const float & dX, const float & dY, const float & l)
{
	origin.x = sX;
	origin.y = sY;
	direction.x = dX;
	direction.y = dY;
	direction.normalise();
	length = l;
}
Ray2::~Ray2()
{
}

//returns the minimum between 2 floats
float Ray2::min(const float & a, const float & b) const
{
	return (a < b) ? a : b;
}
//returns the maximum between 2 floats
float Ray2::max(const float & a, const float & b) const
{
	return (a > b) ? a : b;
}
//ensures that a specified value is within the min and max
float Ray2::clamp(const float & t, const float & a, const float & b) const
{
	return max(a, min(b, t));
}

//projects an arbitrary point onto the ray
Vector2 Ray2::closestPoint(const Vector2 & point) const
{
	//ray origin to arbitrary point
	auto p = point - origin;
	
	//project the point onto the ray and clamp by length
	float t = clamp(p.dot(direction), 0, length);

	//return position in direction of the ray
	return origin + direction * t;
}

// redirects the function to the appropriate shape
bool Ray2::intersects(const Shape & shape, Vector2 * I, Vector2 * R) const
{
	bool result = false;
	if (typeid(shape) == typeid(Circle))
	{
		result = intersects(shape, I, R);
	}
	else if (typeid(shape) == typeid(Plane2))
	{
		result = intersects(shape, I, R);
	}
	else if (typeid(shape) == typeid(AABB2))
	{
		result = intersects(shape, I, R);
	}
	return result;
}

//determines if a circle intersects with the ray
//I stores the intersection point and R stores the reflection penetration
bool Ray2::intersects(const Circle & circle, Vector2 * I, Vector2 * R) const
{
	//ray origin to circle center
	auto L = circle.center - origin;

	// checks if the origin is within the circle
	if (L.magnitude() < circle.radius)
	{
		//store intersection point if requested
		if (I != nullptr)
		{
			*I = origin;
		}
		return true;
	}

	//project circle center onto the ray
	float t = L.dot(direction);

	//get square distance from circle center to ray
	float dd = L.dot(L) - t * t;

	//subtract penetration amount from projected distance
	t -= sqrt(circle.radius * circle.radius - dd);

	//it intersects if within ray length
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
			//get surface normal at intersection point
			auto N = ((origin + direction * t) - circle.center);
			N /= circle.radius;

			//get penetration vector
			auto P = direction * (length - t);

			//get penetration amount
			float p = P.dot(N);

			//get reflected vector
			*R = N * -2 * p + P;
		}

		return true;
	}

	//default no intersection
	return false;
}
//determines if a plane intersects with the ray
//I stores the intersection point and R stores the reflection penetration
bool Ray2::intersects(const Plane2 & plane, Vector2 * I, Vector2 * R) const
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
//determines if a box intersects with the ray
//I stores the intersection point and R stores the reflection penetration
bool Ray2::intersects(const AABB2 & aabb, Vector2 * I, Vector2 * R) const
{
	//get distances to each axis of the box
	float xMin, xMax, yMin, yMax;

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

	//ensure that there is an intersection
	if (xMin > yMax || yMin > xMax)
	{
		return false;
	}

	//the first contact is the largest of the two min
	float t = max(xMin, yMin);

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
			Vector2 N = {};
			if (t == xMin)
			{
				//horizontal normal
				if (direction.x < 0.0f)
				{
					//right side
					N = { 1.0f, 0.0f };
				}
				else
				{
					//left side
					N = { -1.0f, 0.0f };
				}
			}
			else
			{
				//vertical normal
				if (direction.y < 0.0f)
				{
					//top
					N = { 0.0f, 1.0f };
				}
				else
				{
					//bottom
					N = { 0.0f, -1.0f };
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