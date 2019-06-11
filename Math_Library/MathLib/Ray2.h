#pragma once
#include "Shape.h"
#include "Vector2.h"
#include <math.h>
#include "AABB2.h"
#include "Circle.h"
#include "Plane2.h"

class Ray2 : public Shape
{
public:
	//sets the variables to 0
	Ray2();
	//allows specific values to be passed in for the properties
	Ray2(const Vector2& start, const Vector2& dir, const float& l = INFINITY);
	//allows specific values to be passed in for the properties
	Ray2(const float& sX, const float& sY, const float& dX, const float& dY, const float& l = INFINITY);
	~Ray2();

	//the starting point of the ray
	Vector2 origin;
	//the direction of the ray, usually normalised
	Vector2 direction;
	//the magnitude of the direction
	float length;

	//returns the minimum between 2 floats
	float min(const float& a, const float& b) const;
	//returns the maximum between 2 floats
	float max(const float& a, const float& b) const;
	//ensures that a specified value is within the min and max
	float clamp(const float& t, const float& a, const float& b) const;

	//projects an arbitrary point onto the ray
	Vector2 closestPoint(const Vector2& point) const;

	// redirects the function to the appropriate shape
	bool intersects(const Shape& shape, Vector2* I = nullptr, Vector2* R = nullptr) const;

	//determines if a circle intersects with the ray
	//I stores the intersection point and R stores the reflection penetration
	bool intersects(const Circle& circle, Vector2* I = nullptr, Vector2* R = nullptr) const;
	//determines if a plane intersects with the ray
	//I stores the intersection point and R stores the reflection penetration
	bool intersects(const Plane2& plane, Vector2* I = nullptr, Vector2* R = nullptr) const;
	//determines if a box intersects with the ray
	//I stores the intersection point and R stores the reflection penetration
	bool intersects(const AABB2& aabb, Vector2* I = nullptr, Vector2* R = nullptr) const;
};