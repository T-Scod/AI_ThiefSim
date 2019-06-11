#include "Sphere.h"

//sets the center and radius to 0
Sphere::Sphere()
{
	center = 0.0f;
	radius = 0.0f;
}
//allows for manual insertion of center and radius
Sphere::Sphere(const Vector3 & p, float r)
{
	center = p;
	radius = r;
}
Sphere::~Sphere()
{
}

//initialises the sphere's properties based on the points given
void Sphere::fit(const Vector3 * points, const unsigned int count)
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
		if (center.distanceSqr(*points) >(radius * radius))
		{
			//if the distance is greater then the distance becomes the radius
			radius = center.distance(*points);
		}
	}
}
//initialises the sphere's properties based on the points given
void Sphere::fit(const std::vector<Vector3>& points)
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

//tests if a point us within the radius of a sphere
bool Sphere::overlaps(const Vector3 & p) const
{
	//returns true if the distance between the point and the center is less than the radius
	//efficiency is improved by not using the square root function in the calculations
	return center.distanceSqr(p) <= (radius * radius);
}
//tests if two spheres overlap
bool Sphere::overlaps(const Sphere & other) const
{
	//the largest possible distance between the spheres where they overlap
	float r = radius + other.radius;
	//returns true if the distance between the centers are less than the sum of the radii
	//efficiency is improved by not using the square root function in the calculations
	return center.distanceSqr(other.center) <= (r * r);
}
//tests if a sphere overlaps an AABB
bool Sphere::overlaps(const AABB3 & aabb) const
{
	//the distance between the center of the sphere and the closest point to the sphere within the AABB is compared to the radius
	return center.distanceSqr(aabb.closestPoint(center)) <= (radius * radius);
}

//finds the closest point to a sphere from another point
Vector3 Sphere::closestPoint(const Vector3 & p) const
{
	//distance from center
	Vector3 toPoint = p - center;

	//if outside range of radius bring it back to the radius
	if (toPoint.magnitudeSqr() > (radius * radius))
	{
		//normalising the vector will give the direction that the point is from the center
		//additionally it allows the vector to be scaled by the sphere
		toPoint.normalise();
		//moves the vector to the face of the sphere
		toPoint *= radius;
	}

	//translates the point from the center
	return center + toPoint;
}