#pragma once
#include "Shape.h"
#include "Vector2.h"
#include "Circle.h"
#include "AABB2.h"

//defines the sides of the plane
enum ePlaneResult : int
{
	FRONT = 1,
	BACK = -1,
	INTERSECTS = 0
};

class Plane2 : public Shape
{
public:
	//sets all variables to 0
	Plane2();
	//allows values to be set directly
	Plane2(const float& x, const float& y, const float& offset);
	Plane2(const Vector2& n, const float& offset);
	//takes in two positions and calculates the normal and offset
	Plane2(const Vector2& p1, const Vector2& p2);
	~Plane2();

	//normal to the plane
	Vector2 N;
	//offset
	float d;

	//calculates how far a point is from the surface of the plane
	float distanceTo(const Vector2& p) const;
	//finds the closest point on the plane to an arbitrary point
	Vector2 closestPoint(const Vector2& p) const;

	//determines which side of the plane a point is on
	ePlaneResult testSide(const Vector2& p) const;
	//determines which side of the plane a circle is on
	ePlaneResult testSide(const Circle& circle) const;
	//determines which side of the plane a box is on
	ePlaneResult testSide(const AABB2& aabb) const;
};