#include "Circle.h"

//sets the center and radius to 0
Circle::Circle()
{
	center = 0.0f;
	radius = 0.0f;
}
//allows for manual insertion of center and radius
Circle::Circle(const Vector2 & p, float r)
{
	center = p;
	radius = r;
}
Circle::~Circle()
{
}

//initialises the circle's properties based on the points given
void Circle::fit(const Vector2 * points, const unsigned int count)
{
	//adds all of the points coordinate values to the center
	for (int i = 0; i < count; i++, ++points)
	{
		center += *points;
	}
	//divides the center by the amount of points to get an average point
	center /= count;

	//compares the distance between the center and each point
	for (int i = 0; i < count; i++, ++points)
	{
		//checks if the distance squared is greater than the radius squared
		//the distance is not square rooted for efficiency
		if (center.distanceSqr(*points) > (radius * radius))
		{
			//if the distance is greater then the distance becomes the radius
			radius = center.distance(*points);
		}
	}
}
//initialises the circle's properties based on the points given
void Circle::fit(const std::vector<Vector2>& points)
{
	//adds all of the points coordinate values to the center
	for (auto& p : points)
	{
		center += p;
	}
	//divides the center by the amount of points to get an average point
	center /= points.size();

	//compares the distance between the center and each point
	for (auto& p : points)
	{
		//checks if the distance squared is greater than the radius squared
		//the distance is not square rooted for efficiency
		if (center.distanceSqr(p) >(radius * radius))
		{
			//if the distance is greater then the distance becomes the radius
			radius = center.distance(p);
		}
	}
}

//tests if a point us within the radius of a circle
bool Circle::overlaps(const Vector2 & p) const
{
	//returns true if the distance between the point and the center is less than the radius
	//efficiency is improved by not using the square root function in the calculations
	return center.distanceSqr(p) <= (radius * radius);
}
//tests if two circles overlap
bool Circle::overlaps(const Circle & other) const
{
	//the largest possible distance between the circles where they overlap
	float r = radius + other.radius;
	//returns true if the distance between the centers are less than the sum of the radii
	//efficiency is improved by not using the square root function in the calculations
	return center.distanceSqr(other.center) <= (r * r);
}
//tests if a circle overlaps a box
bool Circle::overlaps(const AABB2 & aabb) const
{
	//the distance between the center of the circle and the closest point to the circle within the AABB is compared to the radius
	return center.distanceSqr(aabb.closestPoint(center)) <= (radius * radius);
}

//finds the closest point to a circle from another point
Vector2 Circle::closestPoint(const Vector2 & p) const
{
	//distance from center
	Vector2 toPoint = p - center;

	//if outside range of radius bring it back to the radius
	if (toPoint.magnitudeSqr() > (radius * radius))
	{
		//normalising the vector will give the direction that the point is from the center
		//additionally it allows the vector to be scaled by the circle
		toPoint.normalise();
		//moves the vector to the edge of the circle
		toPoint	*= radius;
	}

	//translates the point from the center
	return center + toPoint;
}