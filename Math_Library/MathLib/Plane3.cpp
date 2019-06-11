#include "Plane3.h"

//sets all variables to 0
Plane3::Plane3()
{
}
//allows values to be set directly
Plane3::Plane3(const float & x, const float & y, const float & z, const float & offset)
{
	N.x = x;
	N.y = y;
	N.z = z;
	d = offset;
}
Plane3::Plane3(const Vector3 & n, const float & offset)
{
	N = n;
	d = offset;
}
Plane3::Plane3(const Vector3 & p1, const Vector3 & p2, const Vector3 & p3)
{
	//calculates edge vectors
	auto v1 = p2 - p1;
	v1.normalise();
	auto v2 = p3 - p1;
	v2.normalise();

	//calculate normal
	N = v1.cross(v2);

	//calculate d
	d = -p1.dot(N);
}
Plane3::~Plane3()
{
}

//calculates how far a point is from the surface of the plane
float Plane3::distanceTo(const Vector3 & p) const
{
	//the returned value will be positive if in front of the plane
	//negative if behind
	//0 if it is on the plane
	return p.dot(N) + d;
}
//finds the closest point on the plane to an arbitrary point
Vector3 Plane3::closestPoint(const Vector3 & p) const
{
	//the distance between the point and the plane is found
	//the distance is then subtracted and multiplied by the normal to result in a position on the plane 
	return p - N * distanceTo(p);
}

//determines which side of the plane a point is on
ePlaneResult Plane3::testSide(const Vector3 & p) const
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
//determines which side of the plane a sphere is on
ePlaneResult Plane3::testSide(const Sphere & sphere) const
{
	//measures the distance of the sphere's center point from the plane
	float t = distanceTo(sphere.center);

	//if the distance is greater than the radius then the sphere is completely in front of the plane
	if (t > sphere.radius)
	{
		return ePlaneResult::FRONT;
	}
	//if the distance is less than the radius inverted then the sphere is completely behind the plane
	else if (t < -sphere.radius)
	{
		return ePlaneResult::BACK;
	}
	//otherwise the sphere intersects with the plane
	else
	{
		return ePlaneResult::INTERSECTS;
	}
}
//determines which side of the plane a cube is on
ePlaneResult Plane3::testSide(const AABB3 & aabb) const
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