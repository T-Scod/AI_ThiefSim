#pragma once
#include "Shape.h"
#include "Vector3.h"
#include <vector>
#include <math.h>

//Axis-Aligned Bounding Box
class AABB3 : public Shape
{
public:
	//initialises all elements to 0
	AABB3();
	//allows individual manual setting of elements
	AABB3(const float& minX, const float& minY = 0.0f, const float& minZ = 0.0f, const float& maxX = 0.0f, const float& maxY = 0.0f, const float& maxZ = 0.0f);
	//allows manual setting of max and min
	AABB3(const Vector3& min, const Vector3& max = 0.0f);
	~AABB3();

	//allows the sharing of memory between the vectors and the arrays
	union
	{
		struct
		{
			//contains the min value
			Vector3 minimum;
			//contains the max value
			Vector3 maximum;
		};
		//contains both max and min
		Vector3 axis[2];
		//contains elements of both max and min
		float data[2][3];
	};

	// assigns another AABB to this one
	AABB3& operator = (const AABB3& other);

	//returns the minimum between 2 floats
	float min(const float& a, const float& b) const;
	//returns the maximum between 2 floats
	float max(const float& a, const float& b) const;
	//returns a vector3 comprised of the smallest components of 2 vector3s
	Vector3 min(const Vector3& a, const Vector3& b) const;
	//returns a vector3 comprised of the largest components of 2 vector3s
	Vector3 max(const Vector3& a, const Vector3& b) const;

	//ensures that a specified value is within the min and max
	float clamp(const float& t, const float& a, const float& b) const;
	//ensures that a specified vector2 is within the min and max
	Vector3 clamp(const Vector3& t, const Vector3& a, const Vector3& b) const;

	//retruns the center of the box
	Vector3 center() const;
	//returns the half extents
	Vector3 extents() const;
	//returns the 4 corners of the box
	std::vector<Vector3> corners() const;
	//finds the closest point on the surface of an AABB to an arbitrary point
	Vector3 closestPoint(const Vector3& p) const;

	//alters the boundries of the box to allow for specific points to fit
	void fit(const Vector3* points, const unsigned int count);
	//alters the boundries of the box to allow for specific points to fit
	void fit(const std::vector<Vector3>& points);

	//tests if a point is contained within the AABB
	bool overlaps(const Vector3& p) const;
	//tests if two AABBs overlap each other
	bool overlaps(const AABB3& other) const;
};