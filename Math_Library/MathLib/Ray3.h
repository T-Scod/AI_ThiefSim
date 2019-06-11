#pragma once
#include "Shape.h"
#include "Vector3.h"
#include <math.h>
#include "AABB3.h"
#include "Sphere.h"
#include "Plane3.h"

class Ray3 : public Shape
{
public:
	//sets the variables to 0
	Ray3();
	//allows specific values to be passed in for the properties
	Ray3(const Vector3& start, const Vector3& dir, const float& l = INFINITY);
	//allows specific values to be passed in for the properties
	Ray3(const float& sX, const float& sY, const float& sZ, const float& dX, const float& dY, const float& dZ, const float& l = INFINITY);
	~Ray3();

	//the starting point of the ray
	Vector3 origin;
	//the direction of the ray, usually normalised
	Vector3 direction;
	//the magnitude of the direction
	float length;

	//returns the minimum between 2 floats
	float min(const float& a, const float& b) const;
	//returns the maximum between 2 floats
	float max(const float& a, const float& b) const;
	//ensures that a specified value is within the min and max
	float clamp(const float& t, const float& a, const float& b) const;

	//projects an arbitrary point onto the ray
	Vector3 closestPoint(const Vector3& point) const;
	//determines if a sphere intersects with the ray
	//I stores the intersection point and R stores the reflection penetration
	bool intersects(const Sphere& sphere, Vector3* I = nullptr, Vector3* R = nullptr) const;
	//determines if a plane intersects with the ray
	//I stores the intersection point and R stores the reflection penetration
	bool intersects(const Plane3& plane, Vector3* I = nullptr, Vector3* R = nullptr) const;
	//determines if a cube intersects with the ray
	//I stores the intersection point and R stores the reflection penetration
	bool intersects(const AABB3& aabb, Vector3* I = nullptr, Vector3* R = nullptr) const;
};