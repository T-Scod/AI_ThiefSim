#include "AABB3.h"

//initialises all elements to 0
AABB3::AABB3()
{
	for (int i = 0; i < 2; i++)
	{
		axis[i] = 0.0f;
	}
}
//allows individual manual setting of elements
AABB3::AABB3(const float & minX, const float & minY, const float& minZ, const float & maxX, const float & maxY, const float& maxZ)
{
	minimum.x = minX;
	minimum.y = minY;
	minimum.z = minZ;
	maximum.x = maxX;
	maximum.y = maxY;
	maximum.z = maxZ;
}
//allows manual setting of max and min
AABB3::AABB3(const Vector3 & min, const Vector3 & max)
{
	minimum = min;
	maximum = max;
}
AABB3::~AABB3()
{
}

// assigns another AABB to this one
AABB3 & AABB3::operator=(const AABB3 & other)
{
	minimum = other.minimum;
	maximum = other.maximum;
	return *this;
}

//returns the minimum between 2 floats
float AABB3::min(const float & a, const float & b) const
{
	return (a < b) ? a : b;
}
//returns the maximum between 2 floats
float AABB3::max(const float & a, const float & b) const
{
	return (a > b) ? a : b;
}
//returns a vector3 comprised of the smallest components of 2 vector3s
Vector3 AABB3::min(const Vector3 & a, const Vector3 & b) const
{
	return { min(a.x, b.x), min(a.y, b.y), min(a.z, b.z) };
}
//returns a vector3 comprised of the largest components of 2 vector3s
Vector3 AABB3::max(const Vector3 & a, const Vector3 & b) const
{
	return { max(a.x, b.x), max(a.y, b.y), max(a.z, b.z) };
}

//ensures that a specified value is within the min and max
float AABB3::clamp(const float & t, const float & a, const float & b) const
{
	return max(a, min(b, t));
}
//ensures that a specified vector2 is within the min and max
Vector3 AABB3::clamp(const Vector3 & t, const Vector3 & a, const Vector3 & b) const
{
	return max(a, min(b, t));
}

//retruns the center of the box
Vector3 AABB3::center() const
{
	return (minimum + maximum) * 0.5f;
}
//returns the half extents
Vector3 AABB3::extents() const
{
	return { abs(maximum.x - minimum.x) * 0.5f, abs(maximum.y - minimum.y) * 0.5f, abs(maximum.z - minimum.z) * 0.5f };
}
std::vector<Vector3> AABB3::corners() const
{
	std::vector<Vector3> corners(8);
	//back bottom left
	corners[0] = minimum;
	//back top left
	corners[1] = { minimum.x, maximum.y, minimum.z };
	//back top right
	corners[2] = { maximum.x, maximum.y, minimum.z };
	//back bottom right
	corners[3] = { maximum.x, minimum.y, minimum.z };
	//front bottom left
	corners[4] = { minimum.x, minimum.y, maximum.z };
	//front top left
	corners[5] = { minimum.x, maximum.y, maximum.z };
	//front top right
	corners[6] = maximum;
	//front bottom right
	corners[7] = { maximum.x, minimum.y, maximum.z };
	return corners;
}
//finds the closest point on the surface of an AABB to an arbitrary point
Vector3 AABB3::closestPoint(const Vector3 & p) const
{
	return clamp(p, minimum, maximum);
}

//alters the boundries of the box to allow for specific points to fit
void AABB3::fit(const Vector3 * points, const unsigned int count)
{
	//sets the minimum to start at the largest possible minimum
	minimum = { FLT_MAX, FLT_MAX, FLT_MAX };
	//sets the maximum to start at the smallest possible maximum
	maximum = { FLT_MIN, FLT_MIN, FLT_MIN };

	//find the minimum and maximum of the points
	for (unsigned int i = 0; i < count; i++, ++points)
	{
		minimum = min(minimum, *points);
		maximum = max(maximum, *points);
	}
}
//alters the boundries of the box to allow for specific points to fit
void AABB3::fit(const std::vector<Vector3>& points)
{
	//sets the minimum to start at the largest possible minimum
	minimum = { FLT_MAX, FLT_MAX, FLT_MAX };
	//sets the maximum to start at the smallest possible maximum
	maximum = { FLT_MIN, FLT_MIN, FLT_MIN };

	//find the minimum and maximum of the points
	for (auto& p : points)
	{
		minimum = min(minimum, p);
		maximum = max(maximum, p);
	}
}

//tests if a point is contained within the AABB
bool AABB3::overlaps(const Vector3 & p) const
{
	//checks if the point is within the range of the min and max
	//tests for not overlapped because it exits faster
	return !(p.x < minimum.x || p.x > maximum.x ||
			 p.y < minimum.y || p.y > maximum.y ||
			 p.z < minimum.z || p.z > maximum.z); 
}
//tests if two AABBs overlap each other
bool AABB3::overlaps(const AABB3 & other) const
{
	//compares the min and max points of the two AABBs
	//tests for not overlapped because it exits faster
	return !(minimum.x > other.maximum.x || maximum.x < other.minimum.x ||
			 minimum.y > other.maximum.y || maximum.y < other.minimum.y ||
			 minimum.z > other.maximum.z || maximum.z < other.minimum.z);
}