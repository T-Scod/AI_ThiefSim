#pragma once
#include "Shape.h"
#include "Vector2.h"
#include <vector>
#include <math.h>

//Axis-Aligned Bounding Box
class AABB2 : public Shape
{
public:
	//initialises all elements to 0
	AABB2();
	//allows individual manual setting of elements
	AABB2(const float& minX, const float& minY = 0.0f, const float& maxX = 0.0f, const float& maxY = 0.0f);
	//allows manual setting of max and min
	AABB2(const Vector2& min, const Vector2& max = 0.0f);
	~AABB2();

	//allows the sharing of memory between the vectors and the arrays
	union
	{
		struct
		{
			//contains the min value
			Vector2 minimum;
			//contains the max value
			Vector2 maximum;
		};
		//contains both max and min
		Vector2 axis[2];
		//contains elements of both max and min
		float data[2][2];
	};

	// assigns another AABB to this one
	AABB2& operator = (const AABB2& other);

	//returns the minimum between 2 floats
	float min(const float& a, const float& b) const;
	//returns the maximum between 2 floats
	float max(const float& a, const float& b) const;
	//returns a vector2 comprised of the smallest components of 2 vector2s
	Vector2 min(const Vector2& a, const Vector2& b) const;
	//returns a vector2 comprised of the largest components of 2 vector2s
	Vector2 max(const Vector2& a, const Vector2& b) const;

	//ensures that a specified value is within the min and max
	float clamp(const float& t, const float& a, const float& b) const;
	//ensures that a specified vector2 is within the min and max
	Vector2 clamp(const Vector2& t, const Vector2& a, const Vector2& b) const;

	//retruns the center of the box
	Vector2 center() const;
	//returns the half extents
	Vector2 extents() const;
	//returns the 4 corners of the box
	std::vector<Vector2> corners() const;
	//finds the closest point on the surface of an AABB to an arbitrary point
	Vector2 closestPoint(const Vector2& p) const;

	//alters the boundries of the box to allow for specific points to fit
	void fit(const Vector2* points, const unsigned int count);
	//alters the boundries of the box to allow for specific points to fit
	void fit(const std::vector<Vector2>& points);

	//tests if a point is contained within the AABB
	bool overlaps(const Vector2& p) const;
	//tests if two AABBs overlap each other
	bool overlaps(const AABB2& other) const;
};