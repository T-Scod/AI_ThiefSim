#include "Plane2.h"

//sets all variables to 0
Plane2::Plane2()
{
}
//allows values to be set directly
Plane2::Plane2(const float & x, const float & y, const float & offset)
{
	N.x = x;
	N.y = y;
	d = offset;
}
Plane2::Plane2(const Vector2 & n, const float & offset)
{
	N = n;
	d = offset;
}
Plane2::Plane2(const Vector2 & p1, const Vector2 & p2)
{
	//calculates normalised vector from p1 to p2
	auto v = p2 - p1;
	v.normalise();

	//set normal perpendicular to the vector
	N.x = -v.y;
	N.y = v.x;

	//calculate d
	d = -p1.dot(N);
}
Plane2::~Plane2()
{
}

//calculates how far a point is from the surface of the plane
float Plane2::distanceTo(const Vector2 & p) const
{
	//the returned value will be positive if in front of the plane
	//negative if behind
	//0 if it is on the plane
	return p.dot(N) + d;
}
//finds the closest point on the plane to an arbitrary point
Vector2 Plane2::closestPoint(const Vector2 & p) const
{
	//the distance between the point and the plane is found
	//the distance is then subtracted and multiplied by the normal to result in a position on the plane 
	return p - N * distanceTo(p);
}

//determines which side of the plane a point is on
ePlaneResult Plane2::testSide(const Vector2 & p) const
{
	//determines which side the point is on based on its distance from the plane
	float t = distanceTo(p);

	if (t < 0)
	{
		return ePlaneResult::BACK;
	}
	else if (t > 0)
	{
		return ePlaneResult::FRONT;
	}
	else
	{
		return ePlaneResult::INTERSECTS;
	}
}
//determines which side of the plane a circle is on
ePlaneResult Plane2::testSide(const Circle & circle) const
{
	//measures the distance of the circle's center point from the plane
	float t = distanceTo(circle.center);

	//if the distance is greater than the radius then the circle is completely in front of the plane
	if (t > circle.radius)
	{
		return ePlaneResult::FRONT;
	}
	//if the distance is less than the radius inverted then the circle is completely behind the plane
	else if (t < -circle.radius)
	{
		return ePlaneResult::BACK;
	}
	//otherwise the circle intersects with the plane
	else
	{
		return ePlaneResult::INTERSECTS;
	}
}
//determines which side of the plane a box is on
ePlaneResult Plane2::testSide(const AABB2 & aabb) const
{
	//tag if a corner is found on each side
	bool side[2] = { false, false };

	//compare each corner
	for (auto c : aabb.corners())
	{
		//tests where the corner is
		auto result = testSide(c);
		if (result == ePlaneResult::FRONT)
		{
			side[0] = true;
		}
		else if (result == ePlaneResult::BACK)
		{
			side[1] = true;
		}
	}

	//if front but not back
	if (side[0] && !side[1])
	{
		return ePlaneResult::FRONT;
	}
	//if back but not front
	else if (side[1] && !side[0])
	{
		return ePlaneResult::BACK;
	}
	//else overlapping
	else
	{
		return ePlaneResult::INTERSECTS;
	}
}