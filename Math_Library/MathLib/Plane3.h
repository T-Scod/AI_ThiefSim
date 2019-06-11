#pragma once
#include "Shape.h"
#include "Vector3.h"
#include "Sphere.h"
#include "AABB3.h"

//defines the sides of the plane
enum ePlaneResult : int
{
	FRONT = 1,
	BACK = -1,
	INTERSECTS = 0
};

class Plane3 : public Shape
{
public:
	//sets all variables to 0
	Plane3();
	//allows values to be set directly
	Plane3(const float& x, const float& y, const float& z, const float& offset);
	Plane3(const Vector3& n, const float& offset);
	//takes in two positions and calculates the normal and offset
	Plane3(const Vector3& p1, const Vector3& p2, const Vector3& p3);
	~Plane3();

	//normal to the plane
	Vector3 N;
	//offset
	float d;

	//calculates how far a point is from the surface of the plane
	float distanceTo(const Vector3& p) const;
	//finds the closest point on the plane to an arbitrary point
	Vector3 closestPoint(const Vector3& p) const;

	//determines which side of the plane a point is on
	ePlaneResult testSide(const Vector3& p) const;
	//determines which side of the plane a sphere is on
	ePlaneResult testSide(const Sphere& sphere) const;
	//determines which side of the plane a cube is on
	ePlaneResult testSide(const AABB3& aabb) const;
};