#pragma once
#include "Shape.h"
#include "Vector2.h"
#include <vector>
#include "AABB2.h"

class Circle : public Shape
{
public:
	//sets the center and radius to 0
	Circle();
	//allows for manual insertion of center and radius
	Circle(const Vector2& p, float r);
	~Circle();

	//coordinates to the middle of the circle
	Vector2 center;
	//distance between the center and the edge of the circle
	float radius;

	//initialises the circle's properties based on the points given
	void fit(const Vector2* points, const unsigned int count);
	//initialises the circle's properties based on the points given
	void fit(const std::vector<Vector2>& points);

	//tests if a point us within the radius of a circle
	bool overlaps(const Vector2& p) const;
	//tests if two circles overlap
	bool overlaps(const Circle& other) const;
	//tests if a circle overlaps a box
	bool overlaps(const AABB2& aabb) const;

	//finds the closest point to a circle from another point
	Vector2 closestPoint(const Vector2& p) const;
};