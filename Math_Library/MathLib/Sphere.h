#pragma once
#include "Shape.h"
#include "Vector3.h"
#include <vector>
#include "AABB3.h"

class Sphere : public Shape
{
public:
	//sets the center and radius to 0
	Sphere();
	//allows for manual insertion of center and radius
	Sphere(const Vector3& p, float r);
	~Sphere();

	//coordinates to the middle of the sphere
	Vector3 center;
	//distance between the center and the face of the sphere
	float radius;

	//initialises the sphere's properties based on the points given
	void fit(const Vector3* points, const unsigned int count);
	//initialises the sphere's properties based on the points given
	void fit(const std::vector<Vector3>& points);

	//tests if a point us within the radius of a sphere
	bool overlaps(const Vector3& p) const;
	//tests if two sphere overlap
	bool overlaps(const Sphere& other) const;
	//tests if a sphere overlaps an cube
	bool overlaps(const AABB3& aabb) const;

	//finds the closest point to a sphere from another point
	Vector3 closestPoint(const Vector3& p) const;
};