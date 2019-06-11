#include "AABB2.h"

//initialises all elements to 0
AABB2::AABB2()
{
	for (int i = 0; i < 2; i++)
	{
		axis[i] = 0.0f;
	}
}
//allows individual manual setting of elements
AABB2::AABB2(const float & minX, const float & minY, const float & maxX, const float & maxY)
{
	minimum.x = minX;
	minimum.y = minY;
	maximum.x = maxX;
	maximum.y = maxY;
}
//allows manual setting of max and min
AABB2::AABB2(const Vector2 & min, const Vector2 & max)
{
	minimum = min;
	maximum = max;
}
AABB2::~AABB2()
{
}

// assigns another AABB to this one
AABB2 & AABB2::operator=(const AABB2 & other)
{
	minimum = other.minimum;
	maximum = other.maximum;
	return *this;
}

//returns the minimum between 2 floats
float AABB2::min(const float & a, const float & b) const
{
	return (a < b) ? a : b;
}
//returns the maximum between 2 floats
float AABB2::max(const float & a, const float & b) const
{
	return (a > b) ? a : b;
}
//returns a vector2 comprised of the smallest components of 2 vector2s
Vector2 AABB2::min(const Vector2 & a, const Vector2 & b) const
{
	return { min(a.x, b.x), min(a.y, b.y) };
}
//returns a vector2 comprised of the largest components of 2 vector2s
Vector2 AABB2::max(const Vector2 & a, const Vector2 & b) const
{
	return { max(a.x, b.x), max(a.y, b.y) };
}

//ensures that a specified value is within the min and max
float AABB2::clamp(const float & t, const float & a, const float & b) const
{
	return max(a, min(b, t));
}
//ensures that a specified vector2 is within the min and max
Vector2 AABB2::clamp(const Vector2 & t, const Vector2 & a, const Vector2 & b) const
{
	return max(a, min(b, t));
}

//retruns the center of the box
Vector2 AABB2::center() const
{
	return (minimum + maximum) * 0.5f;
}
//returns the half extents
Vector2 AABB2::extents() const
{
	return { abs(maximum.x - minimum.x) * 0.5f, abs(maximum.y - minimum.y) * 0.5f };
}
std::vector<Vector2> AABB2::corners() const
{
	std::vector<Vector2> corners(4);
	//bottom left
	corners[0] = minimum;
	//top left
	corners[1] = { minimum.x, maximum.y };
	//top right
	corners[2] = maximum;
	//bottom right
	corners[3] = { maximum.x, minimum.y };
	return corners;
}
//finds the closest point on the surface of an AABB to an arbitrary point
Vector2 AABB2::closestPoint(const Vector2 & p) const
{
	return clamp(p, minimum, maximum);
}

//alters the boundries of the box to allow for specific points to fit
void AABB2::fit(const Vector2 * points, const unsigned int count)
{
	//sets the minimum to start at the largest possible minimum
	minimum = { FLT_MAX, FLT_MAX };
	//sets the maximum to start at the smallest possible maximum
	maximum = { FLT_MIN, FLT_MIN };

	//find the minimum and maximum of the points
	for (unsigned int i = 0; i < count; i++, ++points)
	{
		minimum = min(minimum, *points);
		maximum = max(maximum, *points);
	}
}
//alters the boundries of the box to allow for specific points to fit
void AABB2::fit(const std::vector<Vector2>& points)
{
	//sets the minimum to start at the largest possible minimum
	minimum = { FLT_MAX, FLT_MAX };
	//sets the maximum to start at the smallest possible maximum
	maximum = { FLT_MIN, FLT_MIN };

	//find the minimum and maximum of the points
	for (auto& p : points)
	{
		minimum = min(minimum, p);
		maximum = max(maximum, p);
	}
}

//tests if a point is contained within the AABB
bool AABB2::overlaps(const Vector2 & p) const
{
	//checks if the point is within the range of the min and max
	//tests for not overlapped because it exits faster
	return !(p.x < minimum.x ||
			 p.y < minimum.y ||
			 p.x > maximum.x ||
			 p.y > maximum.y);
}
//tests if two AABBs overlap each other
bool AABB2::overlaps(const AABB2 & other) const
{
	//compares the min and max points of the two AABBs
	//tests for not overlapped because it exits faster
	return !(minimum.x > other.maximum.x ||
			 minimum.y > other.maximum.y ||
			 maximum.x < other.minimum.x ||
			 maximum.y < other.minimum.y);
}